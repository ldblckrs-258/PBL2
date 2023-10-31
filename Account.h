#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Info.h"
#include <string>
#include "linkedlist.cpp"

class Account {
    protected:
        string ID;
        string password;
        Info details;
        bool status;

    public:
        Account(string ID = "account", string pwd = "000000");
        bool checkPwd(string);
        string getID();
        string getPwd();
        void setPwd(string);
        bool check();
        bool ChangePwd();
        void saveAcc();
        bool Login();
        bool Signin();
        void UpdateInfo();
        void loadFull();
        void saveFull();
};

#endif // ACCOUNT_H
