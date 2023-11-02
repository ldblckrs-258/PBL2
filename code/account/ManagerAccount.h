#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "./Account.h"

class ManagerAccount : public Account {
private:
    LinkedList <std::string, std::string> EmployeeList;

public:
    void GetInfo();
    void UpdateInfo();
    void GetEL();
    void UpdateEL();
};

#endif // MANAGERACCOUNT_H
