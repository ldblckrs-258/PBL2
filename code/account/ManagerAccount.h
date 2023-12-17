#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "./Account.h"

class ManagerAccount : public Account
{
private:
public:
    ManagerAccount();
    void readLine(const std::string &str) override;
    std::string writeLine() override;
    void ShowInfo(int except = -1) override;
    void UpdateInfo();
};

#endif // MANAGERACCOUNT_H
