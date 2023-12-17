#ifndef ACCOUNT_BRANCH
#define ACCOUNT_BRANCH

#include "../account/EmployeeAccount.h"
#include "../account/ManagerAccount.h"
extern LinkedList<EmployeeAccount> EAList;
extern LinkedList<ManagerAccount> MAList;

void getEAList();
void saveEAList();
void getMAList();
void saveMAList();
template <typename T>
int Login(LinkedList<T> &accList);
template <typename T>
int Signin(LinkedList<T> &acclist);
void EditExistAccount();
void ViewAllEmployee();
#endif