#include "./branch/InvoiceBranch.h"
#include "./branch/CustomerBranch.h"

void CIMenu()
{
    int choice;
    LinkedList<std::string> menuList;
    menuList.push_back("CUSTOMER & INVOICE MENU");
    menuList.push_back("1. Create new invoice");
    menuList.push_back("2. Open existing invoice");
    menuList.push_back("3. View all invoices");
    menuList.push_back("4. Create new customer profile");
    menuList.push_back("5. Open existing customer profile");
    menuList.push_back("6. View all customer profile");
    menuList.push_back("0. Exit");
    do
    {
        system("cls");
        printOptions(menuList, 3);
        choice = pickMenu();
        switch (choice)
        {
        case 1:
            CreateInvoice();
            break;
        case 2:
            OpenExistInvoice();
            break;
        case 3:
            ViewAllInvoices();
            break;
        case 4:
            CreateNewCustomer();
            break;
        case 5:
            OpenExistCustomer();
            break;
        case 6:
            ViewAllCustomers();
            break;
        default:
            return;
        }
    } while (1);
}