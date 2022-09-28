#include "OnlineUsers.h"
#include <cstdio>
#include <iostream>
namespace gc
{
    namespace entities
    {
        OnlineUsers *OnlineUsers::instance = nullptr;

        OnlineUsers::OnlineUsers() {}

        OnlineUsers *OnlineUsers::getInstance()
        {
            if (!instance)
            {
                instance = new OnlineUsers();
            }
            return instance;
        }

        std::pair<std::string, std::string> OnlineUsers::getAuth_IP(std::string email)
        {
            std::map<std::string, std::pair<std::string, std::string>>::iterator it;
            it = AuthIPmap.find(email);
            if (it != AuthIPmap.end())
                return it->second;
            /*else
                return; Edit and return some value*/
        }

        void OnlineUsers::setAuth_IP(std::string email, std::string authToken, std::string IP)
        {
            AuthIPmap[email] = std::make_pair(authToken, IP);
            return;
        }

        void OnlineUsers::logout(std::string email)
        {
            AuthIPmap.erase(email);
            return;
        }

        bool OnlineUsers::isOnline(std::string email)
        {
            std::map<std::string, std::pair<std::string, std::string>>::iterator it;
            it = AuthIPmap.find(email);
            if (it != AuthIPmap.end())
                return true;
            else
                return false;
        }
        bool OnlineUsers::isExists(std::pair<std::string, std::string> AU_IP)
        {
            for (auto it = AuthIPmap.begin(); it != AuthIPmap.end(); it++)
            {
                if (!(AU_IP.first.compare(it->second.first)) && !(AU_IP.second.compare(it->second.second)))
                {
                    return true;
                }
            }
            return false;
        }

        OnlineUsers::~OnlineUsers()
        {
            instance = nullptr;
        }

        std::string OnlineUsers::fetchEmail(std::pair<std::string, std::string> AU_IP)
        {
            for (auto it = AuthIPmap.begin(); it != AuthIPmap.end(); it++)
            {
                if (!(AU_IP.first.compare(it->second.first)) && !(AU_IP.second.compare(it->second.second)))
                {
                    return it->first;
                }
            }
            return "";
        }
    } // namespace entities
} // namespace gc
