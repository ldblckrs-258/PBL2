#ifndef EMPLOYEEACCOUNT_H
#define EMPLOYEEACCOUNT_H

#include "./Account.h"

class EmployeeAccount : public Account {
private:
    int salary;
    LinkedList <std::string, std::string> Schedule;

public:
    EmployeeAccount(int s = 0);
    void ShowInfo();
    void saveFull();
    void saveSalary();
    void loadFull();
    void UpdateInfo();
};

#endif // EMPLOYEEACCOUNT_H
