#ifndef CUSTOMER_BRANCH
#define CUSTOMER_BRANCH
#include "../others/Customer.h"

extern LinkedList<Customer> CustomerList;

void getCustomerList();
void saveCustomerList();
void ViewAllCustomers();
void CreateNewCustomer();
void OpenExistCustomer();
std::string getCustomerName(const std::string &);
#endif // !CUSTOMER_BRANCH