#include <iostream>
#include "./code/mylib/FuncLib.h"
#include "./code/PSMenu.cpp"
#include "./code/ASMenu.cpp"
#include "./code/account/EmployeeAccount.h"
#include "./code/account/ManagerAccount.h"
#include "./code/AccountBranch.cpp"
LinkedList<Species> SpeciesList;
LinkedList<CustomerPet> CPetsList;
LinkedList<ShopPet> SPetsList;
LinkedList<ManagerAccount> MAList;
LinkedList<EmployeeAccount> EAList;

template<typename T>
bool Logged(T &Acc){
    int choice;
    bool logout = false;
    LinkedList<std::string> menuList;
    menuList.push_back("MAIN MENU");
    menuList.push_back("1. Pets & Species");
    menuList.push_back("2. Goods & Service");
    menuList.push_back("3. Invoices & Transactions");
    menuList.push_back("4. Account settings");
    if (Acc.isManager()) menuList.push_back("5. Employees Management");
    menuList.push_back("0. Exit");
    do {
        system("cls");
        printOptions(menuList, 1);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PSMenu(Acc.isManager());
                break;
            case 2:
                // GSMenu();
                break;
            case 3:
                // ITMenu();
                break;
            case 4:
                logout = ASMenu(Acc);
                if (logout) return true;
                break;        
            default:
                return false;
        }
    } while (1);
}

LinkedList<int> LogIO() {
    int choice;
    LinkedList<int> output;
    output.push_back(-1);
    output.push_back(-1);
    do {
        system("cls");
        printFile(".\\source\\MainMenu.txt");
        choice = pickMenu();
        switch(choice) {
            case 1:
                output[0] = login(EAList);
                if (output[0] != -1) {
                    output[1] = 1;
                    return output;
                }
                break;
            case 2:
                output[0] = signin(EAList);
                if (output[0] != -1) {
                    output[1] = 1;
                    saveEAList();
                    return output;
                }
                break;
            case 3:
                output[0] = login(MAList);
                if (output[0] != -1) {
                    output[1] = 2;
                    return output;
                }
                break;
            default: 
                std::cout << "Exiting ..." << std::endl;
                output[1] = 0;
                return output;
                break;
        }
    } while(1);
} 



int main() {
    int choice;
    bool reLogin;
    LinkedList<int> LogInfo;
    getSpeciesList();
    getCPList();
    getSPList();
    getEAList();
    getMAList();

    do {
        reLogin = false;
        LogInfo = LogIO();
        if (LogInfo[1] == 0) break;
        if  (LogInfo[0] != -1){
            if (LogInfo[1] == 1)
                reLogin = Logged(EAList[LogInfo[0]]);
            else if (LogInfo[1] == 2)
                reLogin = Logged(MAList[LogInfo[0]]);
            else break;
        }
    } while(reLogin);
}
