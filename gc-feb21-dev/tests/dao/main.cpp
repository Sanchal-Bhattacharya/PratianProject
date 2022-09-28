#include <iostream>
#include "UserServiceDAO.h"
#include "GroupServiceDAO.h"
#include "MessageServiceDAO.h"
#include "DAOManager.h"
#include <vector>
#include "../entities/OnlineUsers.h"
using namespace gc;
using namespace std;
int main()
{
	
	IUserServiceDAO* us = DAOManager::getUserServiceDAO();
	IGroupServiceDAO* gs = DAOManager::getGroupServiceDAO();
	IMessageServiceDAO* ms = DAOManager::getMessageServiceDAO();

	entities::User *user = new entities::User("Hemant","yy@x.com","9900112233","sjkadhjgdkhasgdh","asjkfhjsvfhsvd");
    entities::User *user1 = new entities::User("Abc","abc@x.com","1236723423","mnbvcxzlkjhgfdsa","qwertyuiopasdfghjkl");
    entities::Group *group = new entities::Group("xyz","abc@x.com");

	entities::Message *msg = new entities::Message(1,"yy@x.com","abc@x.com","asdavsdhagdv",1,0);
	entities::Message *msg1 = new entities::Message(2,"yy@x.com","abc@x.com","fdgbdgdbfjgb",1,0);
	us->createUser(user1);
    	//std::vector<string> a=group->getEmailList();
	
	//for(auto i = a.begin();i!=a.end();i++)
	//	cout<<*i<<endl;
	// gs->createGroup(group);
	
	us->createUser(user);
	// us->blockconnection("abc@x.com","yy@x.com");
	// cout<<us->isBlocked("abc@x.com","yy@x.com")<<"\n\n";
	// cout<<us->isBlocked("yy@x.com","abc@x.com")<<"\n\n";
	// gs->addMember("xyz","yy@x.com");

	// std::vector<string> g = gs->getAllGroups();
	// for(auto i = g.begin();i!=g.end();i++)
    //             cout<<*i<<endl;

	// gs->updateGroup("xyz","G1");
	// std::vector<string> a = gs->getAllUsers("G1");

	// for(auto i = a.begin();i!=a.end();i++)
    //             cout<<*i<<endl;

	//  g = gs->getAllGroups();
	// for(auto i = g.begin();i!=g.end();i++)
    //             cout<<*i<<endl;
	// //gs->removeUser("G1","abc@x.com");
    //     a = gs->getAllUsers("G1");

    //     for(auto i = a.begin();i!=a.end();i++)
    //             cout<<*i<<endl;
	
	// gs->deleteGroup("G1");
	// // g = gs->getAllGroups();
	// // for(auto i = g.begin();i!=g.end();i++)
    // //             cout<<*i<<endl;
	
	cout<<"enteringAddMessagetoDB\n";
	 ms->addMessageDB(msg);
	 cout<<"returning from AddMessagetoDB\n";
	
	ms->addMessageDB(msg1);

	cout<<"enteringRestore\n";
	std::vector<entities::Message*> m = ms->restore();
	cout<<"returnedRestore\n";
	for(auto i = m.begin();i!=m.end();i++)
         cout<<(*i)->getMessage()<<endl;


	 cout<<"enteringdeletemessageDB\n";
	 ms->deleteMessageDB(msg);
	 cout<<"deleted\n";
	// entities::OnlineUsers* a=entities::OnlineUsers::getInstance();
    // a->setAuth_IP("xyz","dsfsdf","asdas");
    // std::pair<string,string> xy=a->getAuth_IP("xyz");
    // cout << xy.first <<" "<<xy.second<<"\n";
    // a->logout("xyz");
   // us->blockconnection("xyz","abc");
	//us->blockconnection("xyz","sdgfydsf");
	//us->unblockconnection("abc","xyz");
	//us->unblockconnection("xyz","abc");
	//us->isBlocked("xyz","sdgfydsf");
    // if(a->isExists(xy)==true)
    //     cout<<"Works"<<endl;
    // cout<<a->isOnline("xyz")<<endl;
        
	 //us->createUser(user1);	
	// us->createUser(user1);
	// user->setName("Abhay");
	// // //user->setEmail("hsagdv@ashd");
	// user->setMobileNumber("98348762");
	// user->setPassword("jhvdd");
	// user->setSalt("asvdh");
	// //us->createUser(user);
	// //std::pair<string,string> x=us->login("hemantbaid9396@anurag.com");
	// //cout<<x.first<<endl;
	// //cout<<x.second<<endl;*/
	// us->updateUser(user);
	//us->deleteUser("hemantbaid9396@anurag.com");
	/*
	entities::User *user1 = new entities::User("Hemant1","hemantbaid19396@anurag.com","9100112233");
	entities::User *user2 = new entities::User("Hemant2","hemantbaid29396@anurag.com","9200112233");
	entities::User *user3 = new entities::User("Hemant3","hemantbaid39396@anurag.com","9300112233");
	std::vector<entities::User *> users;
	
	users.push_back(user1);
	users.push_back(user2);
    users.push_back(user3);
    
    us->createUserFromList(users);*/
    
	//entities::User *user3 = new entities::User("Doggy","hemantbaid39396@anurag.com","9310112233");    
	//us->updateUser(user3);
	
	/*entities::User *user = us->getUser("hemantbaid39396@anurag.com");
	cout<<user->getName()<<" "<<user->getEmail()<<" "<<user->getMobileNumber()<<endl;
	std::vector<entities::User *> userlist = us->getAllUsers();
	for(int i=0;i<userlist.size();i++)
	{
		cout<<userlist[i]->getName()<<" "<<userlist[i]->getEmail()<<" "<<userlist[i]->getMobileNumber()<<endl;
		delete userlist[i];
	}
	delete user;*/
	delete us;	
}
