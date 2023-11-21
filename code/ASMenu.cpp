#include <iostream>
#include "./mylib/FuncLib.h"
#include "./account/EmployeeAccount.h"
#include "./account/ManagerAccount.h"
#include "./AccountBranch.cpp"

template <typename T>
bool ASMenu(T &Acc){
    int choice;
    LinkedList<std::string> list;
    list.push_back("ACCOUNT SETTING");
    list.push_back("1. My profile");
    list.push_back("2. Edit profile");
    list.push_back("3. Change password");
    list.push_back("4. Log out");
    list.push_back("0. Return to menu");
    do {
        system("cls");
        printOptions(list);
        choice = pickMenu();
        switch (choice){
            case 1:
                Acc.ShowInfo();
                holdString("");
                break;
            case 2:
                Acc.UpdateInfo();
                break;
            case 3:
                Acc.ChangePwd();
                break;
            case 4:
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