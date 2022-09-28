-------DROP AND CREATE TABLESPACE---------

--Drop gc_test_tbs tablespace.
BEGIN
      EXECUTE IMMEDIATE 'DROP TABLESPACE gc_tbs02 INCLUDING CONTENTS AND DATAFILES';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /
--Create Tablespace
create tablespace gc_tbs02 datafile '/u01/app/oracle/oradata/XE/gc_tbs02.dbf' size 100m FORCE LOGGING;
--Create user
BEGIN
		EXECUTE IMMEDIATE 'DROP USER gc_user CASCADE';
	EXCEPTION
		WHEN OTHERS THEN NULL;
	END;
/

create user gc_user identified by gc_user;
--Grant privileges to user
grant create session, resource to gc_user;
alter user gc_user quota unlimited on gc_tbs02;


--Connecting to the DB with following credentials
connect gc_user/gc_user



---------DROPS----------------

--Drop gc_blocked_table.
BEGIN
      EXECUTE IMMEDIATE 'DROP TABLE gc_blocked_table';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /

--Drop gc_userGroup_table.
BEGIN
      EXECUTE IMMEDIATE 'DROP TABLE gc_userGroup_table';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /


--Drop gc_group_table.
BEGIN
      EXECUTE IMMEDIATE 'DROP TABLE gc_group_table';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /


--Drop gc_user_table.
BEGIN
      EXECUTE IMMEDIATE 'DROP TABLE gc_user_table';
  EXCEPTION
    WHEN OTHERS THEN NULL;
  END;
  /



--Drop gc_persistence_table and then generates new one.
BEGIN
      EXECUTE IMMEDIATE 'DROP TABLE gc_persistence_table';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /



------CREATE TABLES-------------------

--Generate gc_user_table
CREATE TABLE gc_user_table (USERID NUMBER(10) PRIMARY KEY,EMAIL VARCHAR2(30) UNIQUE NOT NULL, NAME VARCHAR2(20) NOT NULL, MOBILE VARCHAR2(10) NOT NULL, HASH VARCHAR2(64) NOT NULL, SALT VARCHAR2(30) NOT NULL);

--Generate gc_group_table
CREATE TABLE gc_group_table (GROUPID NUMBER(5) PRIMARY KEY,GROUPNAME VARCHAR2(30) UNIQUE NOT NULL);

--Generate gc_userGroup_table
CREATE TABLE gc_userGroup_table (EMAIL VARCHAR2(30),GROUPID NUMBER(5),PRIMARY KEY (EMAIL,GROUPID), FOREIGN KEY (EMAIL) REFERENCES gc_user_table(EMAIL) ON DELETE CASCADE,FOREIGN KEY (GROUPID) REFERENCES gc_group_table(GROUPID) ON DELETE CASCADE);

--Generate gc_blocked_table
CREATE TABLE gc_blocked_table (BLOCKER VARCHAR2(30) NOT NULL,BLOCKEE VARCHAR2(30) NOT NULL,PRIMARY KEY (BLOCKER, BLOCKEE),FOREIGN KEY(BLOCKER) REFERENCES gc_user_table(EMAIL) ON DELETE CASCADE,FOREIGN KEY(BLOCKEE) REFERENCES gc_user_table(EMAIL) ON DELETE CASCADE);

--Generate gc_persistence_table
CREATE TABLE gc_persistence_table (MESSAGEID NUMBER(5),MESSAGEOBJ VARCHAR2(500),PRIMARY KEY (MESSAGEID,MESSAGEOBJ));


----SEQUENCES-----

/*
   Drop the sequence userid_seq and create new one.
   Generates a sequence which is used in auto incrementing 
   the USERID.
*/
BEGIN
      EXECUTE IMMEDIATE 'DROP SEQUENCE userid_seq';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /
CREATE SEQUENCE userid_seq
MINVALUE 1
MAXVALUE 1000000
START WITH 1
INCREMENT BY 1
ORDER;




/*
   Drop the sequence groupid_seq and create new one.
   Generates a sequence which is used in auto incrementing 
   the GROUPID.
*/
BEGIN
      EXECUTE IMMEDIATE 'DROP SEQUENCE groupid_seq';
  EXCEPTION
      WHEN OTHERS THEN NULL;
  END;
  /
CREATE SEQUENCE groupid_seq
MINVALUE 1
MAXVALUE 100000
START WITH 1
INCREMENT BY 1
ORDER;




----------TRIGGERS----------

/*
   If trigger exists drop it and then create new one.
   Generates a triggers which runs before a row is 
   inserted in the gc_user_table table.
*/
CREATE OR REPLACE TRIGGER user_trig
BEFORE INSERT ON gc_user_table
FOR EACH ROW
BEGIN
SELECT userid_seq.nextval
INTO :new.USERID
FROM dual;
END;
/



/*
   If trigger exists drop it and then create new one.
   Generates a triggers which runs before a row is 
   inserted in the gc_group_table table.
*/
CREATE OR REPLACE TRIGGER groupid_trig
BEFORE INSERT ON gc_group_table
FOR EACH ROW
BEGIN
SELECT groupid_seq.nextval
INTO :new.GROUPID
FROM dual;
END;
/



-------PROCEDURES---------

--Procedure for creating a new user.
CREATE OR REPLACE PROCEDURE sp_create(
	p_email IN gc_user_table.EMAIL%TYPE,
	p_name IN gc_user_table.NAME%TYPE,
	p_mobile IN gc_user_table.MOBILE%TYPE,
	p_hash IN gc_user_table.HASH%TYPE,
	p_salt IN gc_user_table.SALT%TYPE)

IS 
BEGIN

INSERT INTO gc_user_table (EMAIL,NAME,MOBILE,HASH,SALT) VALUES (p_email, p_name,p_mobile,p_hash,p_salt);

COMMIT;

END;

/

--Procedure for updating user details based on the email.
CREATE OR REPLACE PROCEDURE sp_update(
        p_email IN gc_user_table.EMAIL%TYPE,
        p_name IN gc_user_table.NAME%TYPE,
        p_mobile IN gc_user_table.MOBILE%TYPE,
        p_hash IN gc_user_table.HASH%TYPE,
        p_salt IN gc_user_table.SALT%TYPE)

IS
BEGIN

UPDATE gc_user_table SET NAME = p_name,MOBILE = p_mobile,HASH = p_hash,SALT = p_salt where EMAIL = p_email;

COMMIT;

END;

/


--Procedure for deleting a user based on the email.
CREATE OR REPLACE PROCEDURE sp_delete(
        p_email IN gc_user_table.EMAIL%TYPE)

IS
BEGIN

DELETE FROM gc_user_table WHERE EMAIL = p_email;

COMMIT;

END;

/



--Procedure for checking if user1 is blocked by user2
CREATE OR REPLACE PROCEDURE sp_isBlocked(
	p_blocker IN gc_blocked_table.BLOCKER%TYPE,
	p_blockee IN gc_blocked_table.BLOCKEE%TYPE,
	o_count OUT NUMBER)	
IS
BEGIN
	SELECT count(*) INTO o_count FROM gc_blocked_table WHERE (blocker, blockee) IN ((p_blocker,p_blockee),(p_blockee,p_blocker));
	COMMIT;
END;
/

--Procedure for blocking a user by other user
CREATE OR REPLACE PROCEDURE sp_blockUser(
       p_blocker_mail IN gc_blocked_table.BLOCKER%TYPE,
       p_blockee_mail IN gc_blocked_table.BLOCKEE%TYPE)
IS
var number:=0;
BEGIN 
	sp_isBlocked(p_blocker_mail,p_blockee_mail,var);
		if var<1 then
			INSERT INTO gc_blocked_table VALUES (p_blocker_mail,p_blockee_mail);
		end if;	
	COMMIT;
END;
/


--Procedure for unblocking a user by other user
CREATE OR REPLACE PROCEDURE sp_unblockUser(
	p_blocker IN gc_blocked_table.BLOCKER%TYPE,
	p_blockee IN gc_blocked_table.BLOCKEE%TYPE)
IS
BEGIN

	DELETE FROM gc_blocked_table WHERE (blocker, blockee) IN ((p_blocker, p_blockee));
	
	COMMIT;
END;
/

--Procedure for creating a new group.
CREATE OR REPLACE PROCEDURE sp_createGroup(
	p_email IN gc_usergroup_table.EMAIL%TYPE,
        p_groupName IN gc_group_table.GROUPNAME%TYPE)

IS 
var_gid NUMBER;
BEGIN
INSERT INTO gc_group_table (GROUPNAME) VALUES (p_groupName);
SELECT GROUPID INTO var_gid FROM gc_group_table WHERE GROUPNAME = p_groupName;
INSERT INTO gc_usergroup_table values (p_email,var_gid);
COMMIT;
END;
/


--Procedure for updating group name corresponding to the groupid.
CREATE OR REPLACE PROCEDURE sp_updateGroupName(
        p_groupName IN gc_group_table.GROUPNAME%TYPE,
	p_NewgroupName IN gc_group_table.GROUPNAME%TYPE)

IS
BEGIN

UPDATE gc_group_table SET GROUPNAME = p_NewgroupName where GROUPNAME = p_groupName;

COMMIT;

END;

/


--SQL Procedure to add user to an existing group
CREATE OR REPLACE PROCEDURE sp_addUserToGroup(
	p_email IN gc_usergroup_table.EMAIL%TYPE,
	p_groupName IN gc_group_table.GROUPNAME%TYPE)
IS
var_gid NUMBER;
BEGIN
	SELECT GROUPID INTO var_gid FROM gc_group_table WHERE GROUPNAME = p_groupName;
	INSERT INTO gc_usergroup_table values (p_email,var_gid); 
	
	COMMIT;
END;
/


-- SQL procedure to remove user from an existing group
CREATE OR REPLACE PROCEDURE sp_removeUserFromGroup(
    p_email IN gc_usergroup_table.EMAIL%TYPE,
    p_groupName IN gc_group_table.GROUPNAME%TYPE)
IS
    no NUMBER;
    var_gid NUMBER;	
BEGIN
    	SELECT GROUPID INTO var_gid FROM gc_group_table WHERE GROUPNAME = p_groupName;
	SELECT count(*) INTO no FROM gc_usergroup_table WHERE GROUPID = var_gid;
   	DELETE FROM gc_usergroup_table where (EMAIL, GROUPID) IN ((p_email, var_gid)); 
    
    IF no=1 
    THEN
        DELETE FROM gc_group_table WHERE GROUPNAME = p_groupName;
    END IF;
    COMMIT;
END;
/

--Procedure for deleting a group

CREATE OR REPLACE PROCEDURE sp_deleteGroup(

       p_groupName IN gc_group_table.GROUPNAME%TYPE)

IS
BEGIN 
	DELETE FROM gc_group_table WHERE GROUPNAME = p_groupName;
	
COMMIT;

END;

/


--Procedure for inserting processed message object.

CREATE OR REPLACE PROCEDURE sp_insertObject(
	p_mid IN gc_persistence_table.MESSAGEID%TYPE,
        p_obj IN gc_persistence_table.MESSAGEOBJ%TYPE)

IS 
BEGIN
INSERT INTO gc_persistence_table VALUES (p_mid,p_obj);
COMMIT;
END;
/



--Procedure for deleting processed message object.

CREATE OR REPLACE PROCEDURE sp_deleteObject(
	p_mid IN gc_persistence_table.MESSAGEID%TYPE,
	p_obj IN gc_persistence_table.MESSAGEOBJ%TYPE)

IS 
BEGIN
DELETE FROM gc_persistence_table WHERE MESSAGEID = p_mid AND MESSAGEOBJ = p_obj; 
COMMIT;
END;
/

-- Add a manager account with the default password as password

CALL sp_create('manager@gc.com', 'Manager', '877766558', 'b57d5fae79ced594570e21254eb5fdea272eb8c4bedc1866d7aaa35af8a4fa', '5097099555745667079');


exit
/

