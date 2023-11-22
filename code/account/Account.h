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
        std::string getID() const;
        std::string getPwd() const;
        std::string getName() const;
        std::string getPosition() const;
        std::string getContact() const;
        void setID(std::string);
        void setPwd(std::string);
        bool checkPwd(std::string);
        bool isManager() const;
        virtual void readLine(const std::string&) = 0;
        bool ChangePwd();
};

#endif // ACCOUNT_H
