#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "./Info.h"
#include <string>

class Account {
    protected:
        std::string ID;
        std::string password;
        Info details;
        bool manager;

    public:
        Account(std::string ID = "account", std::string pwd = "000000");
        bool checkPwd(std::string);
        std::string getID() const;
        std::string getPwd() const;
        bool isManager() const;
        void setID(std::string);
        void setPwd(std::string);
        bool ChangePwd();
        void UpdateInfo();
};

#endif // ACCOUNT_H
