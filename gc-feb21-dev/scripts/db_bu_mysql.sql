DROP TABLE IF EXISTS gc_persistence_table;

DROP TABLE IF EXISTS gc_blocked_table;

DROP TABLE IF EXISTS gc_userGroup_table;

DROP TABLE IF EXISTS gc_group_table;

DROP TABLE IF EXISTS gc_user_table;

CREATE TABLE gc_user_table (USERID INT(10) PRIMARY KEY AUTO_INCREMENT,EMAIL VARCHAR(30) UNIQUE NOT NULL, NAME VARCHAR(20) NOT NULL, MOBILE VARCHAR(10) NOT NULL, HASH VARCHAR(64) NOT NULL, SALT VARCHAR(30) NOT NULL);


CREATE TABLE gc_group_table (GROUPID INT(5) PRIMARY KEY AUTO_INCREMENT,GROUPNAME VARCHAR(30) UNIQUE NOT NULL);


CREATE TABLE gc_userGroup_table (EMAIL VARCHAR(30),GROUPID INT(5),PRIMARY KEY (EMAIL,GROUPID), FOREIGN KEY (EMAIL) REFERENCES gc_user_table(EMAIL) ON DELETE CASCADE,FOREIGN KEY (GROUPID) REFERENCES gc_group_table(GROUPID) ON DELETE CASCADE);


CREATE TABLE gc_blocked_table (BLOCKER VARCHAR(30) NOT NULL,BLOCKEE VARCHAR(30) NOT NULL,PRIMARY KEY (BLOCKER, BLOCKEE),FOREIGN KEY(BLOCKER) REFERENCES gc_user_table(EMAIL) ON DELETE CASCADE,FOREIGN KEY(BLOCKEE) REFERENCES gc_user_table(EMAIL) ON DELETE CASCADE);


CREATE TABLE gc_persistence_table (MESSAGEID INT(5),MESSAGEOBJ VARCHAR(500),PRIMARY KEY (MESSAGEID,MESSAGEOBJ));


DELIMITER //
DROP PROCEDURE IF EXISTS sp_create;
CREATE PROCEDURE sp_create(
        IN p_email varchar(30),
        IN p_name varchar(20),
        IN p_mobile varchar(10),
        IN p_hash varchar(64),
        IN p_salt varchar(30))

BEGIN
INSERT INTO gc_user_table (EMAIL,NAME,MOBILE,HASH,SALT) VALUES (p_email, p_name,p_mobile,p_hash,p_salt);
END //



DROP PROCEDURE IF EXISTS sp_update;
CREATE PROCEDURE sp_update(
	IN p_email varchar(30),
        IN p_name varchar(20),
        IN p_mobile varchar(10),
        IN p_hash varchar(64),
        IN p_salt varchar(30))
BEGIN
UPDATE gc_user_table SET NAME = p_name,MOBILE = p_mobile,HASH = p_hash,SALT = p_salt where EMAIL = p_email;
END //



DROP PROCEDURE IF EXISTS sp_delete;
CREATE PROCEDURE sp_delete(
        IN p_email varchar(30))
BEGIN
UPDATE gc_user_table SET NAME = p_name,MOBILE = p_mobile,HASH = p_hash,SALT = p_salt where EMAIL = p_email;
END //



DROP PROCEDURE IF EXISTS sp_isBlocked;
CREATE PROCEDURE sp_isBlocked(
        IN p_blocker varchar(30),
        IN p_blockee varchar(30),
        OUT o_count int)
BEGIN
SELECT count(*) INTO o_count FROM gc_blocked_table WHERE (blocker, blockee) IN ((p_blocker,p_blockee),(p_blockee,p_blocker));
END //



DROP PROCEDURE IF EXISTS sp_blockUser;
CREATE PROCEDURE sp_blockUser(
       IN p_blocker_mail varchar(30),
       IN p_blockee_mail varchar(30))
BEGIN
        CALL sp_isBlocked(p_blocker_mail,p_blockee_mail,@var);
                if var < 1 then
                        INSERT INTO gc_blocked_table VALUES (p_blocker_mail,p_blockee_mail);
                end if;
END //



DROP PROCEDURE IF EXISTS sp_unblockUser;
CREATE PROCEDURE sp_unblockUser(
        IN p_blocker varchar(30),
        IN p_blockee varchar(30))
BEGIN
        DELETE FROM gc_blocked_table WHERE (blocker, blockee) IN ((p_blocker, p_blockee));
END //



DROP PROCEDURE IF EXISTS sp_createGroup;
CREATE PROCEDURE sp_createGroup(
        IN p_email varchar(30),
        IN p_groupName varchar(30))
BEGIN
INSERT INTO gc_group_table (GROUPNAME) VALUES (p_groupName);
SELECT GROUPID INTO @var_gid FROM gc_group_table WHERE GROUPNAME = p_groupName;
INSERT INTO gc_userGroup_table values (p_email,var_gid);
END //




DROP PROCEDURE IF EXISTS sp_updateGroupName;
CREATE PROCEDURE sp_updateGroupName(
        IN p_groupName varchar(30),
        IN p_NewgroupName varchar(30))
BEGIN
UPDATE gc_group_table SET GROUPNAME = p_NewgroupName where GROUPNAME = p_groupName;
END //



DROP PROCEDURE IF EXISTS sp_addUserToGroup;
CREATE PROCEDURE sp_addUserToGroup(
        IN p_email varchar(30),
        IN p_groupName varchar(30))
BEGIN
        SELECT GROUPID INTO @var_gid FROM gc_group_table WHERE GROUPNAME = p_groupName;
        INSERT INTO gc_userGroup_table values (p_email,var_gid);
END //



DROP PROCEDURE IF EXISTS sp_removeUserFromGroup;
CREATE PROCEDURE sp_removeUserFromGroup(
	IN p_email varchar(30),
        IN p_groupName varchar(30))
BEGIN
        SELECT GROUPID INTO @var_gid FROM gc_group_table WHERE GROUPNAME = p_groupName;
        SELECT count(*) INTO @no FROM gc_usergroup_table WHERE GROUPID = var_gid;
        DELETE FROM gc_usergroup_table where (EMAIL, GROUPID) IN ((p_email, var_gid));

    IF no=1
    THEN
        DELETE FROM gc_group_table WHERE GROUPNAME = p_groupName;
    END IF;
END //

DROP PROCEDURE IF EXISTS sp_deleteGroup;
CREATE PROCEDURE sp_deleteGroup(
       	IN p_groupName varchar(30))
BEGIN
        DELETE FROM gc_group_table WHERE GROUPNAME = p_groupName;
END //




DROP PROCEDURE IF EXISTS sp_insertObject;
CREATE PROCEDURE sp_insertObject(
        IN p_mid int(5),
        IN p_obj varchar(500))
BEGIN
INSERT INTO gc_persistence_table VALUES (p_mid,p_obj);
END //




DROP PROCEDURE IF EXISTS sp_deleteObject;
CREATE PROCEDURE sp_deleteObject(
	IN p_mid int(5),
        IN p_obj varchar(500))
BEGIN
DELETE FROM gc_persistence_table WHERE MESSAGEID = p_mid AND MESSAGEOBJ = p_obj;
END //

DELIMITER ;
