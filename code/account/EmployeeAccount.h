#ifndef EMPLOYEEACCOUNT_H
#define EMPLOYEEACCOUNT_H

#include "./Account.h"
class EmployeeAccount : public Account {
private:
    int salary;
public:
    EmployeeAccount(int s = 0);
    int getSalary() const;
    std::string writeLine();
    void readLine(const std::string &str) override;
    void ShowInfo(int except = -1);
    void UpdateInfo(bool permission = false);
};

#endif // EMPLOYEEACCOUNT_H
