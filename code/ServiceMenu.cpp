#include "./branch/ServiceBranch.h"

void ServiceMenu(bool manager = false)
{ // Services options
    int choice;
    LinkedList<std::string> list;
    list.push_back("Service menu");
    list.push_back("1. View all service");
    list.push_back("2. Open a service");
    if (manager)
        list.push_back("3. Create new service");
    list.push_back("0. Return to menu");
    do
    {
        system("cls");
        printOptions(list, 3);
        choice = pickMenu();
        switch (choice)
        {
        case 1:
            ViewAllServices();
            break;
        case 2:
            OpenExistService(manager);
            break;
        case 3:
            if (manager)
                CreateNewService();
            else
                return;
            break;
        default:
            return;
        }
        saveServiceList();
    } while (1);
    return;
}