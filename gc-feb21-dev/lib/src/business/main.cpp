#include "MessageManager.h"
#include <iostream>
#include "GroupService.h"
#include "GcBusinessManager.h"
#include <vector>
#include <iostream>
using namespace std;
using namespace gc::business;
using namespace gc::entities;




void printMsg( Message & msg )
{
	 cout << msg.getToId() << "  " << msg.getFromId() << "  " <<  msg.getMsgId() << "  " <<
	 	  msg.getMessage() << "  " <<  msg.getMessageType() << "  " <<  msg.getAckStatus() << endl;
}
int main()
{
	MessageManager m;
    gc::business::IGroupService *ig = gc::business::GcBusinessManager::getGroupService();
    ig->createGroup(new Group("Group1","abc@xyz.com"));
    ig->addMember("Group1","def@xyz.com");
    ig->addMember("Group1","ghi@xyz.com");
    ig->addMember("Group1","jkl@xyz.com");
    m.addMessageToGroup( new Message(2,"Group1","def@xyz.com","good morning"));
    vector<Message *> m1 = m.removeMessagesFromGroups("ghi@xyz.com");
    for(int i=0;i<m1.size();i++){
        printMsg(*m1[i]);
    }
    vector<Message *> m2 = m.removeMessagesFromGroups("jkl@xyz.com");
    for(int i=0;i<m2.size();i++){
        printMsg(*m2[i]);
    }
    cout << endl << "#########################################################" << endl;
    m1 = m.removeMessage("def@xyz.com");
    for(int i=0;i<m1.size();i++) {
        printMsg(*m1[i]);
    }
    cout << endl << "#########################################################" << endl;






    //g.createGroup(new Group("Group1","user1@xyz.com"));
	/*m.addMessage( new Message(1,"hemantbaid9396@anurag.com","DumDum@kranti.com","hello sir"));
	m.addMessage( new Message(2,"hemantbaid9396@anurag.com","DumDum@kranti.com","good morning"));
	m.addMessage( new Message(3,"DumDum@kranti.com","hemantbaid9396@anurag.com","good evening"));
	m.addMessage( new Message(4,"DumDum@kranti.com","xcd","Got a new laptop"));
	m.addMessage( new Message(5,"DumDum@kranti.com","Hemant","had Dinner?"));
	m.addMessage( new Message(6,"DumDum@kranti.com","hemantbaid9396@anurag.com","good night"));
	
	vector<Message * > messageVec2 = m.removeMessage( "hemantbaid9396@anurag.com" );

	for (int i = 0 ; i < messageVec2.size() ; i++ )
	{
		printMsg( *messageVec2[i] );
		delete messageVec2[i];
	}

	messageVec2 = m.removeMessage( "DumDum@kranti.com" );

	for (int i = 0 ; i < messageVec2.size() ; i++ )
	{
		printMsg( *messageVec2[i] );
		delete messageVec2[i];
	}
	
	m.addMessage( new Message(1,"DumDum@kranti.com","hemantbaid9396@anurag.com","",1,2));
	
	messageVec2 = m.removeMessage( "hemantbaid9396@anurag.com" );

	for (int i = 0 ; i < messageVec2.size() ; i++ )
	{
		printMsg( *messageVec2[i] );
		delete messageVec2[i];
	}
	
	messageVec2 = m.removeMessage( "hemantbaid9396@anurag.com" );*/

}
