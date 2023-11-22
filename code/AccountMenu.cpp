#include "./branch/AccountBranch.h"

template <typename T>
bool ASMenu(T &Acc){ // Account settings
    int choice;
    LinkedList<std::string> list;
    list.push_back("ACCOUNT SETTINGS");
    list.push_back("1. My profile");
    list.push_back("2. Change password");
    list.push_back("3. Log out");
    list.push_back("0. Return to menu");
    do {
        system("cls");
        printOptions(list, 3);
        choice = pickMenu();
        switch (choice){
            case 1:
                Acc.UpdateInfo();
                break;
            case 2:
                Acc.ChangePwd();
                break;
            case 3:
                return true;
                break;        
            default:
                return false;
        }
        saveEAList();
        saveMAList();
    } while (1);
    return false;
}

void AMMenu(){  // Account management
    int choice;
    LinkedList<std::string> list;
    list.push_back("ACCOUNT MANAGEMENT");
    list.push_back("1. Manage employee account list");
    list.push_back("2. Edit employee information");
    list.push_back("3. Create management account");
    list.push_back("0. Return to menu");
    do {
        system("cls");
        printOptions(list, 3);
        choice = pickMenu();
        switch (choice){
            case 1:
                ViewAllEmployee();
                break;
            case 2:
                EditExistAccount();
                break;
            case 3:
                Signin(MAList);
                saveMAList();
                break;     
            default:
                return;
        }
    } while (1);
    return;
}