#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "./Info.h"
#include <string>
#include "../mylib/FuncLib.h"
#include "../mylib/LinkedList.cpp"
#include "../mylib/Cursor.h"
class Account
{
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
    bool ChangePwd();

    virtual void readLine(const std::string &) = 0; // Đọc một chuỗi string thành dữ liệu của đối tượng
    virtual std::string writeLine() = 0;            // Chuyển dữ liệu đối tượng thành một chuỗi string
    virtual void ShowInfo(int) = 0;                 // In ra thông tin đối tượng
};

#endif // ACCOUNT_H
