#ifndef EMPLOYEEACCOUNT_H
#define EMPLOYEEACCOUNT_H

#include "./Account.h"

class EmployeeAccount : public Account {
private:
    int salary;


public:
    EmployeeAccount(int s = 0);
    void ShowInfo();
    std::string writeLine();
    void readLine(const std::string &str);
    void UpdateInfo();
};

#endif // EMPLOYEEACCOUNT_H
