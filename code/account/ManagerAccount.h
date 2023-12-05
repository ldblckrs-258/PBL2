#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "./Account.h"
#include "../mylib/LinkedList.cpp"

class ManagerAccount : public Account
{
private:
public:
    ManagerAccount();
    void readLine(const std::string &str) override;
    std::string writeLine();
    void ShowInfo(int except = -1);
    void UpdateInfo();
};

#endif // MANAGERACCOUNT_H
