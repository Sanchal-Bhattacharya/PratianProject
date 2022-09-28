import requests
from datetime import datetime, timedelta
import time
import json
import base64

URL = "http://localhost:9000/gc/"
USER_SERVICE = "userservice/"
MESSAGE_SERVICE = "messageservice/"
GROUP_SERVICE = "groupservice/"
CREATE_GROUP = "groups/"
GROUP = "groups/"
PAUSE_TIME = 0.08
USER = "user/"
LOGIN="login/"
#create 3 users
CREATE_USER = "users/"

user_index = 0

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

user_index += 1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Varun", "email":"g1@amadeus.com", "mobileNumber":"9871113780", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

user_index+=1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Mubeen", "email":"g2@amadeus.com", "mobileNumber":"9871113781", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

user_index+=1
print "Creating user index: ", user_index
PAYLOAD = '{"name": "Koshy", "email":"g3@amadeus.com", "mobileNumber":"9871113782", "password":"IamBatman"}'
print "Payload is ", PAYLOAD
r = requests.put(url=URL+USER_SERVICE+CREATE_USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)



#login g1
print "Logging in user: g1"
PAYLOAD = '{"email": "g1@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
    #capture auth token
    auth_token1 = eval(r.content)["auth_token"]
    print "Auth Token Received: ", auth_token1
time.sleep(PAUSE_TIME)

#generate the encoded string
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)

#create a group
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD='{"name":"Group 1", "email":"g1@amadeus.com", "encoded_string":"'+encoded_string+'"}'
r = requests.put(url=URL+GROUP_SERVICE+CREATE_GROUP, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)


#add two users
print "Adding User 1"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"name":"Group 1", "email":"g2@amadeus.com", "encoded_string":"'+encoded_string+'"}'
r = requests.put(url=URL+GROUP_SERVICE+CREATE_GROUP+USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

print "Adding User 2"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"name":"Group 1", "email":"g3@amadeus.com", "encoded_string":"'+encoded_string+'"}'
r = requests.put(url=URL+GROUP_SERVICE+CREATE_GROUP+USER, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#messaging
print "User 1 sends a message to the group"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"MsgId":1, "ToId":"Group 1", "FromId":"g1@amadeus.com", "Msg":"Heleo", "type":1, "Ack": 0, "email":"g3@amadeus.com", "encoded_string":"'+encoded_string+'"}'
r = requests.post(url=URL+MESSAGE_SERVICE+GROUP, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

#login g2
print "Logging in g2"
PAYLOAD = '{"email": "g2@amadeus.com", "password": "IamBatman"}'
r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
if r.status_code == 200:
    print "Login: ", eval(PAYLOAD)["email"], " successfull"
    #capture auth token
    auth_token1 = eval(r.content)["auth_token"]
    print "Auth Token Received: ", auth_token1
time.sleep(PAUSE_TIME)

#retrieve for g2
print "Retrieve for g2"
isodate1 = datetime.utcnow().isoformat()
encoded_string = base64.b64encode(auth_token1+isodate1)
PAYLOAD = '{"email":"g2@amadeus.com", "encoded_string":"'+encoded_string+'"}'
r = requests.get(url=URL+MESSAGE_SERVICE+GROUP, data=PAYLOAD)
print "Status Code: ", r.status_code, "\n", r.content
time.sleep(PAUSE_TIME)

