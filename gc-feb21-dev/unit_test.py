import requests
from datetime import datetime, timedelta
import time
import json
import base64

URL = "http://localhost:9000/gc/"
USER_SERVICE = "userservice/"
MESSAGE_SERVICE = "messageservice/"

PAUSE_TIME = 0.08

#Delete the existing Users from Database
print "Deleting existing Users before Testing....................."
GET_USERS = "users/"

r = requests.get(url=URL+USER_SERVICE+GET_USERS)
print "Status Code: ", r.status_code
print "Existing Users: ", r.content
json_response = r.json()

for user in json_response:
	if not user["email"] == "a":
		print "deleting user: ", user["email"]
		r = requests.delete(url=URL+USER_SERVICE+GET_USERS+user["email"])		



#1. Create User Cases
CREATE_USER = "users/"
print "*****************Running Create User Test Cases*********************"
#1.1 Create 5 users with name, email, mobileNumber, password -- Valid Inputs
user_index = 0

user_index += 1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Varun", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

user_index+=1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Mubeen", "email":"mubeen@amadeus.com", "mobileNumber":"9871113781", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

user_index+=1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Koshy", "email":"koshy@amadeus.com", "mobileNumber":"9871113782", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

user_index+=1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Yohaan", "email":"yohaan@amadeus.com", "mobileNumber":"9871113783", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

user_index+=1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Abhishek", "email":"abhishek@amadeus.com", "mobileNumber":"9871113784", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)





#1.1.1 Creating New User with same email
print "Creating New User with existing Email"
PAYLOAD = '{"name": "VarunNarayanan", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.2 Wrong formatting of name
#1.2.1 Special Characters
print "Name with Special Characters"
PAYLOAD = '{"name": "V@run", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.2.2 Numbers in Name
print "Numbers in Name"
PAYLOAD = '{"name": "V23run", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.3 Wrong formatting of Email
#1.3.1 No @ Symbol
print "Wrong Email Formatting"
PAYLOAD = '{"name": "Varun", "email":"varun&amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.3.2 No . (dot)
print "No . in email id"
PAYLOAD = '{"name": "Varun", "email":"varun@amadeus&com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.3.3 More than 4 characters after . (dot)
print "More than 4 characters after ."
PAYLOAD = '{"name": "Varun", "email":"varun@amadeus.compass", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.4 Wrong formatting of mobileno
#1.4.1 Mobile Number not long enough
print "Mobile no having less digits than 10"
PAYLOAD = '{"name": "Varun", "email":"varun@amadeus.com", "mobileNumber":"98711137", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.4.2 Mobile Number having chracters and special characters
print "Mobile no having alphabets and special characters"
PAYLOAD = '{"name": "Varun", "email":"varun@amadeus.com", "mobileNumber":"98711137L$", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#1.5 Wrong formatting of password (at least 8 characters long)
print "Password < 8 characters long"
PAYLOAD = '{"name": "Varun", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"Batman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#2 Login Test Cases
print "****************Running Login Test Cases*******************"

LOGIN="login/"

user_index = 0

user_index += 1
print "Logging in user: ", user_index
PAYLOAD = '{"email": "varun@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
time.sleep(PAUSE_TIME)

user_index += 1
print "Logging in user: ", user_index
PAYLOAD = '{"email": "mubeen@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
time.sleep(PAUSE_TIME)

user_index += 1
print "Logging in user: ", user_index
PAYLOAD = '{"email": "koshy@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
time.sleep(PAUSE_TIME)

user_index += 1
print "Logging in user: ", user_index
PAYLOAD = '{"email": "yohaan@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
time.sleep(PAUSE_TIME)

user_index += 1
print "Logging in user: ", user_index
PAYLOAD = '{"email": "abhishek@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
time.sleep(PAUSE_TIME)

#2.2 Wrong credentials (E-Mail)
print "Login User with wrong email address"
PAYLOAD = '{"email": "batman@amadeus.com", "password": "IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)


#2.2 Wrong credentials (Password)
print "Login User with wrong Password"
PAYLOAD = '{"email": "abhishek@amadeus.com", "password": "IamNotBatman"}'
print "Payload is ", PAYLOAD
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#3 Update User Test Cases
print "*************** Running Update User Test Cases ****************"

#3.1 Updation of existing User
UPDATE_USER = 'users/'
print "Updating User user index: 1"
PAYLOAD = '{"name": "VarunNarayanan", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.post(url=URL+USER_SERVICE+UPDATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)


#3.2 Updation of User that doesn't exist
print "Updating User user index: 1"
PAYLOAD = '{"name": "VarunNarayanan", "email":"varunIsBatman@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.post(url=URL+USER_SERVICE+UPDATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)
'''
#Get all the Users
print "Getting all the Users"
print "No Payload"
r = requests.get(url=URL+USER_SERVICE+GET_USERS)
print "Status Code: ", r.status_code, "\n", r.content
'''

#3.3 Wrong Formatting
print "Validation in Update"
PAYLOAD = '{"name": "V@run", "email":"varun@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.post(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#4. GET User
GET_USER = 'users/'
#4.1 GET an existing User
print "Get an existing User"
EMAIL = "abhishek@amadeus.com"
print "URL is ", URL+USER_SERVICE+GET_USER+EMAIL
r = requests.get(URL+USER_SERVICE+GET_USER+EMAIL)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#4.2 GET a non Existant User
print "Get a non Existant User"
EMAIL = "batman@amadeus.com"
print "URL is ", URL+USER_SERVICE+GET_USER+EMAIL
r = requests.get(URL+USER_SERVICE+GET_USER+EMAIL)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#4.3 GET all the Users
print "Get all the Users"
print "URL is ", URL+USER_SERVICE+GET_USER
r = requests.get(URL+USER_SERVICE+GET_USER)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#4.4 DELETE an existing User
print "Delete an exiting User"
EMAIL = "abhishek@amadeus.com"
print "API is ", URL+USER_SERVICE+GET_USER+EMAIL
r = requests.delete(URL+USER_SERVICE+GET_USER+EMAIL)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#4.5 DELETE a non existant User
'''

'''
print "Delete a non existant User"
EMAIL = "batman@amadeus.com"
print "API is ",URL+USER_SERVICE+GET_USER+EMAIL
r = requests.delete(URL+USER_SERVICE+GET_USER+EMAIL)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)
'''

'''
#5 ------------------- MESSAGING ----------------------
print "************************Test Cases for Messaging***************************"

#5.1 Login two users
print "Logging in user: varun@amadeus.com"
PAYLOAD = '{"email": "varun@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code
auth_token1=''
auth_token2=''
if r.status_code == 200:
    #capture auth token
    auth_token1 = eval(r.content)["auth_token"]
    print "Auth Token Received: ", auth_token1
else:
    print "Request Failed"
time.sleep(PAUSE_TIME)

print "Logging in user: mubeen@amadeus.com"
PAYLOAD = '{"email": "mubeen@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    #capture auth_token
    auth_token2 = eval(r.content)["auth_token"]
    print "Auth Token Received: ", auth_token2
else:
    print "Request Failed"
time.sleep(PAUSE_TIME)



#5.2 Send a message from user 1 to user 2
MESSAGE = 'users/'
print "Sending a message from varun to mubeen"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"MsgId":1,"ToId":"mubeen@amadeus.com","FromId":"varun@amadeus.com","Msg":"hello","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
print "API is ",URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
print "Status Code: ",r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)


'''
#5.2 Retrieve a message for user 2
print "Retrieving all the messages for mubeen from queue"
isodate2 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token2+isodate2)
PAYLOAD = '{"encoded_string": "'+encoded_string+'"}'
print "API  is ", URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
EMAIL = "mubeen@amadeus.com"
r = requests.get(url=URL+MESSAGE_SERVICE+MESSAGE+EMAIL, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)
'''


#Sending to a user that doesnt exist
print "Sending a message from varun to someone that doesnt exist"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"MsgId":1,"ToId":"batman@amadeus.com","FromId":"varun@amadeus.com","Msg":"hello","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
print "API is ",URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
print "Status Code: ",r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#Sending from a user that doesnt exist
print "Sending a message from varun to someone that doesnt exist"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"MsgId":1,"ToId":"mubeen@amadeus.com","FromId":"batman@amadeus.com","Msg":"hello","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
print "API is ",URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
print "Status Code: ",r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#Using wrong Authentication token to send a message
print "Using wrong Authentication Token to send a message"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode("ABCDEFGHIJKLMNOPQR"+isodate1)
PAYLOAD = '{"MsgId":1,"ToId":"mubeen@amadeus.com","FromId":"batman@amadeus.com","Msg":"hello","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
print "API is ",URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
print "Status Code: ",r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)
'''
#Message sent 10 minutes before the server received it
print "Message sent 15 minutes before the server received it"
newtime = datetime.utcnow() - timedelta(minutes=datetime.utcnow().minute - 15)
encoded_string = base64.b64encode("ABCDEFGHIJKLMNOPQR"+newtime.isoformat())
PAYLOAD = '{"MsgId":1,"ToId":"mubeen@amadeus.com","FromId":"batman@amadeus.com","Msg":"hello","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
print "API is ",URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
print "Status Code: ",r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#Multiple Messages sent by user 1 to user 2
MESSAGE = 'users/'
msgidx = 0

print "Sending Multiple Messages from varun to mubeen"
for i in range (0,3):
    msgidx+=1
    print "Sending a message ", msgidx ,"from varun to mubeen"
    isodate1 = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token1+isodate1)
    PAYLOAD = '{"MsgId":1,"ToId":"mubeen@amadeus.com","FromId":"varun@amadeus.com","Msg":"message '+str(msgidx)+'","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
    print "API is ",URL+MESSAGE_SERVICE+MESSAGE
    print "Payload is ", PAYLOAD
    r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
    print "Status Code: ",r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

'''

#Retireve messages
print "Retrieving all the messages for mubeen from queue"
isodate2 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token2+isodate2)
PAYLOAD = '{"encoded_string": "'+encoded_string+'"}'
print "API  is ", URL+MESSAGE_SERVICE+MESSAGE
print "Payload is ", PAYLOAD
EMAIL = "mubeen@amadeus.com"
r = requests.get(url=URL+MESSAGE_SERVICE+MESSAGE+EMAIL, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)



