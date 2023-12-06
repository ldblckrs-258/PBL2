#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include "../mylib/LinkedList.cpp"
#include "../mylib/Cursor.h"
#include "../mylib/FuncLib.h"
#include <vector>
class Customer
{
private:
    std::string ID;
    std::string Name;
    std::string Contact;

public:
    Customer(std::string id = "C1");
    std::string getID() const;
    std::string getName() const;
    std::string getContact() const;
    void SetNextID();
    std::string writeLine();
    void readLine(const std::string &str);
    void ShowDetails(int except = -1);
    void EditInfo();
};

#endif // !CUSTOMER_H