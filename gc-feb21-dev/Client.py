import requests
from datetime import datetime
import base64
import time
import sys
import threading

URL = "http://localhost:9000/gc/"
USER_SERVICE="userservice/"
LOGIN="login/"
MESSAGE_SERVICE="messageservice/"
MESSAGE="users/"
GROUP_SERVICE = "groupservice/"
GROUP = "groups/"
CREATE_GROUP = "groups/"
FORWARD_MESSAGE = "forwardmessage/"



def get_message_id():
    f = open("messageid.txt", "r")
    mid = int(f.read())
    f.close()
    f = open("messageid.txt", "w")
    f.write("%d" % (mid+1))
    return mid
    
def messageGroup(groupname,mid,message,auth_token):
    isodate1 = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate1)
    PAYLOAD = '{"MsgId":'+str(mid)+', "ToId":"'+groupname+'", "FromId":"'+email+'", "Msg":"'+message+'", "Type":1, "Ack": 0, "encoded_string":"'+encoded_string+'"}'
    r = requests.put(url=URL+MESSAGE_SERVICE+GROUP, data=PAYLOAD)
    print "Status Code: ", r.status_code, "\n", r.content

def login(email, password):
    PAYLOAD = '{"email": "'+email+'", "password": "'+password+'"}'
    r = requests.post(url = URL+USER_SERVICE+LOGIN, data=PAYLOAD)
    #print "Status Code: ", r.status_code, "\n", r.content
    auth_token=''
    if r.status_code == 200:
        #capture auth_token
            auth_token = eval(r.content)["auth_token"]
            #print "Auth Token Received: ", auth_token
    else:
        print "Request Failed"
    return auth_token

def retrieve_group_message(auth_token,email):
    isodate1 = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate1)
    PAYLOAD = '{"encoded_string":"'+encoded_string+'"}'
    r = requests.get(url=URL+MESSAGE_SERVICE+GROUP+email, data=PAYLOAD)
    #print "Status Code: ", r.status_code, "\n", r.content
    if len(eval(r.content)) > 0:
        print eval(r.content), "\n\n"

def retrieve_messages(auth_token, email):
    #print("Inside retrieve : ",email)
    isodate = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate)
    PAYLOAD = '{"encoded_string": "'+encoded_string+'"}'
    #print "API  is ", URL+MESSAGE_SERVICE+MESSAGE
    #print "Payload is ", PAYLOAD
    r = requests.get(url=URL+MESSAGE_SERVICE+MESSAGE+email, data=PAYLOAD)
    #print "Status Code: ", r.status_code, "\n", r.content
    if len(eval(r.content)) > 0:
        print eval(r.content),"\n\n"

def createGroup(groupname,owner,auth_token):
    isodate1 = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate1)
    PAYLOAD='{"name":"'+groupname+'", "email":"'+owner+'", "encoded_string":"'+encoded_string+'"}'
    r = requests.put(url=URL+GROUP_SERVICE+CREATE_GROUP, data=PAYLOAD)
    print "Status Code: ", r.status_code, "\n", r.content

def addMember(groupname,user_email,auth_token):
    isodate1 = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate1)
    PAYLOAD = '{"name":"'+groupname+'", "email":"'+user_email+'", "encoded_string":"'+encoded_string+'"}'
    print "PAYLOAD: ",PAYLOAD
    print "API: ",URL+GROUP_SERVICE+"addtogroup"
    r = requests.put(url=URL+GROUP_SERVICE+"addtogroup", data=PAYLOAD)
    print "Status Code: ", r.status_code, "\n", r.content

def send_message(auth_token, msg, fromId, toId, mid):
    print "Sending a message"
    isodate = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate)
    PAYLOAD = '{"MsgId":'+str(mid)+',"ToId":"'+toId+'","FromId":"'+fromId+'","Msg":"'+msg+'","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
    print "API is ",URL+MESSAGE_SERVICE+MESSAGE
    print "Payload is ", PAYLOAD
    #http://localhost:9000/gc/messageservice/users/
    r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE, data=PAYLOAD)
    print "Status Code: ",r.status_code, "\n", r.content

def forward_message(auth_token, msg_id, fromId, toId):
    print "Forwarding a message"
    isodate = datetime.utcnow().isoformat()
    encoded_string = base64.b64encode(auth_token+isodate)
    PAYLOAD = '{"MsgId":'+str(msg_id+',"ToId":"'+toId+'","FromId":"'+fromId+'","Msg":"'+msg+'","Ack":0,"Type":0,"encoded_string":"' + encoded_string +'"}'
    print "API is ",URL+MESSAGE_SERVICE+MESSAGE+FORWARD_MESSAGE
    print "Payload is ", PAYLOAD
    #http://localhost:9000/gc/messageservice/users/forwardmessage/
    r = requests.put(url=URL+MESSAGE_SERVICE+MESSAGE+FORWARD_MESSAGE, data=PAYLOAD)
    print "Status Code: ",r.status_code, "\n", r.content

def listen_to_messages(auth_token, email):
    while True:
        retrieve_messages(auth_token, email)
        retrieve_group_message(auth_token,email)
        time.sleep(3)

if __name__ == "__main__":


    print "------------------------------------------"
    print "Please Note following are valid commands:"
    print "\n1. Send Message: message(to_id,message)"
    print "\n2. Retrieve Message: retrieve()"
    print "\n8. Forward Message: forward_message(msd_id,to_id)"
    print "\n3. Create a Group: createGroup(groupname)"
    print "\n4. Add Member to Group: addMember(groupname,email)"
    print "\n5. Send Message to Group: messageGroup(groupname,message)"
    print "\n6. Retrieve Message from Groups : retrieveGroupMessage()"
    print "\n7. Quit the application: quit/Quit"
    print "------------------------------------------"

    if len(sys.argv) != 3:
        print "Usage: python client.py email password"
    else:
        email = sys.argv[1]
        password = sys.argv[2]

    auth_token = login (email, password)
    if auth_token == '':
        print "Login Failed, Exiting.............."
        exit()


    threading1 = threading.Thread(target=listen_to_messages, args=(auth_token, email))
    threading1.daemon = True
    threading1.start()

    while True:
        command = raw_input("\nEnter a command?\n")
        if command in ['quit','Quit']:
            sys.exit()

        cmd = command.split('(',1)
        if cmd[0]=='message':
            comma = cmd[1]
            comma = comma[:-1]
            contents = comma.split(',')
            send_message(auth_token,contents[1],email,contents[0],get_message_id())
            #send_message(auth_token, msg, fromId, toId, mid)
        
        elif cmd[0]=='forward_message':
            comma = cmd[1]
            comma = comma[:-1]
            contents = comma.split(',')
            forward_message(auth_token,contents[0],email,contents[1])
            #forward_message(auth_token, msg_id, fromId, toId)

        elif cmd[0]=='retrieve':
            retrieve_messages(auth_token,email)
        elif cmd[0]=='createGroup':
            comma = cmd[1]
            comma = comma[:-1]
            createGroup(comma,email,auth_token)
        elif cmd[0]=='addMember':
            comma = cmd[1]
            comma = comma[:-1]
            contents = comma.split(',')
            addMember(contents[0],contents[1],auth_token)
        elif cmd[0]=='messageGroup':
            comma = cmd[1]
            comma = comma[:-1]
            contents = comma.split(',')
            messageGroup(contents[0],get_message_id(),contents[1],auth_token)
        elif cmd[0]=='retrieveGroupMessage':
            retrieve_group_message(auth_token,email)
        else:
            print "Enter a valid command please"

