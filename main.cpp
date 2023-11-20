#include <iostream>
#include "./code/mylib/FuncLib.h"
#include "./code/PSMenu.cpp"
#include "./code/ASMenu.cpp"
#include "./code/account/EmployeeAccount.h"
#include "./code/account/ManagerAccount.h"
LinkedList<Species> SpeciesList;
LinkedList<CustomerPet> CPetsList;
LinkedList<ShopPet> SPetsList;

bool ELogged(EmployeeAccount &EUser){
    int choice;
    bool logout = false;
    LinkedList<std::string> menuList;
    menuList.push_back("MAIN MENU");
    menuList.push_back("1. Pets & Species");
    menuList.push_back("2. Goods & Service");
    menuList.push_back("3. Invoices & Transactions");
    menuList.push_back("4. Account settings");
    menuList.push_back("0. Exit");
    do {
        system("cls");
        printOptions(menuList, 1);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PSMenu();
                break;
            case 2:
                // GSMenu();
                break;
            case 3:
                // ITMenu();
                break;
            case 4:
                logout = ASMenu(EUser);
                if (logout) return true;
                break;        
            default:
                return false;
        }
    } while (1);
}

bool MLogged(ManagerAccount &MUser){
    int choice;
    bool logout = false;
    LinkedList<std::string> menuList;
    menuList.push_back("MAIN MENU");
    menuList.push_back("1. Pets & Species");
    menuList.push_back("2. Goods & Service");
    menuList.push_back("3. Invoices & Transactions");
    menuList.push_back("4. Account settings");
    menuList.push_back("5. Employee management");
    menuList.push_back("0. Exit");
    do {
        system("cls");
        printOptions(menuList, 1);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PSMenu(true);
                break;
            case 2:
                // GSMenu();
                break;
            case 3:
                // ITMenu();
                break;
            case 4:
                logout = ASMenu(MUser);
                if (logout) return true;
                break; 
            case 5:
                // EMMenu();
                break;
            default:
                return false;
        }
    } while (1);
}

int LogIO(EmployeeAccount &EUser, ManagerAccount &MUser) {
    int choice;
    do {
        system("cls");
        printFile(".\\source\\MainMenu.txt");
        choice = pickMenu();
        switch(choice) {
            case 1:
                if(EUser.Login()){
                    EUser.loadFull();
                    return 1;
                }
                break;
            case 2:
                if (EUser.Signin()){
                    EUser.saveFull();
                    return 1;
                }
                break;
            case 3:
                if (MUser.Login()) {
                    MUser.loadFull();
                    return 2;}
                break;
            default: 
                std::cout << "Exiting ..." << std::endl;
                return 0;
                break;
        }
    } while(1);
} 



int main() {
    int choice, mode;
    bool login = false;
    EmployeeAccount EUser;
    ManagerAccount::getEL();
    ManagerAccount MUser;
    getSpeciesList();
    getCPList();
    getSPList();
    do {
        mode = LogIO(EUser, MUser);
        login = mode;
        switch (mode)
        {
            case 1:
                if (ELogged(EUser))
                    login = false;
                break;
            case 2:
                if (MLogged(MUser))
                    login = false;
                break;
            default:
                return 0;
        }
    } while(!login);
}
