#ifndef MANAGERACCOUNT_H
#define MANAGERACCOUNT_H

#include "./Account.h"
#include <vector>
// CẦN VIẾT THƯ VIỆN LINKED LIST ĐỂ THAY THẾ VECTOR

class ManagerAccount : public Account {
private:
    static std::vector<std::string> EmployeeList;

public:
    static void getEL();
    ManagerAccount();
    void ShowInfo();
    void saveAcc();
    void loadFull();
};

#endif // MANAGERACCOUNT_H
