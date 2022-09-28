# include "MessageManager.h"
# include <iostream>

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
	m.addMessage( new Message(1,"hemantbaid9396@anurag.com","DumDum@kranti.com","hello sir"));
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
	
	messageVec2 = m.removeMessage( "hemantbaid9396@anurag.com" );

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
	return 0;
}
