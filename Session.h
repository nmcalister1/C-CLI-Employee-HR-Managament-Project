#ifndef SESSION_H
#define SESSION_H
#include <string>
#include <iostream>
#include <ctime>
#include "Manager.h"
using namespace std; 

class Session{
    private: 
        string guid; 
        string user;
        time_t authTime; 
        time_t logoutTime; 
        string logString; 
    public: 
        Session(){
            user = ""; 
            authTime = time(nullptr);
            logoutTime = 0; 
            guid = to_string(rand());
            logString = "";
        }

        void logout(){ logoutTime = time(nullptr); }
        void addLog(string log){ logString += log + "\n"; }
        void setUser(string name){ user = name; }
        void setLogoutTime(time_t time){ logoutTime = time; }

        string getGuid() const { return guid; }
        string getUser() const { return user; }
        time_t getLoginTime() const { return authTime; }
        time_t getLogoutTime() const { return logoutTime; }

        void showSessionInfo() const {
            cout << "Session Data:" << endl; 
            cout << "GUID: " << guid << endl; 
            cout << "User: " << user << endl; 
            cout << "Authentication/Login Time: " << authTime << endl; 
            cout << "Changes Made: " << endl; 
            cout << logString << endl; 
        }

        string logSessionInfo() {
            return "\n\nSession Data:\nGUID: " + guid + "\nUser: " + user + "\nLogin Time: " + to_string(authTime) + "\nChanges Made: " + logString + "\n";
        }
};
#endif