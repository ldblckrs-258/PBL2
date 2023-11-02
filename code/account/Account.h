#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "./Info.h"
#include <string>
#include "../mylib/linkedlist.cpp"

class Account {
    protected:
        std::string ID;
        std::string password;
        Info details;
        bool status;

    public:
        Account(std::string ID = "account", std::string pwd = "000000");
        bool checkPwd(std::string);
        std::string getID();
        std::string getPwd();
        void setPwd(std::string);
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
