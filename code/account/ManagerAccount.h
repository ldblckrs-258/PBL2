#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "./Account.h"
#include "../mylib/LinkedList.cpp"

class ManagerAccount : public Account {
private:
    static LinkedList<std::string> EmployeeList;

public:     
    ManagerAccount();
    void ShowInfo();
    void readLine(const std::string &str);
    std::string writeLine();
};

#endif // MANAGERACCOUNT_H
