#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include "../mylib/LinkedList.cpp"
#include "../mylib/Cursor.h"
#include "../mylib/FuncLib.h"

class Service
{
private:
    std::string ID;
    std::string Name;
    int Price;

public:
    Service(const std::string &id = "S0", const std::string &n = "Service name", const int &pr = 0);

    std::string getID() const;
    std::string getName() const;
    int getPrice() const;

    void readLine(const std::string &);
    std::string writeLine();
    void showDetails(int except = -1);
    void editInfo();
    void setNextID();
};

#endif