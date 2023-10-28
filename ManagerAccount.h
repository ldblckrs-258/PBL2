#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "Account.h"

class ManagerAccount : public Account {
private:
    LinkedList <string, string> EmployeeList;

public:
    void GetInfo();
    void UpdateInfo();
    void GetEL();
    void UpdateEL();
};

#endif // MANAGERACCOUNT_H
