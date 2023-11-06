#include <iostream>
#include "./code/mylib/FuncLib.h"
#include "./code/PSMenu.cpp"
#include "./code/ASMenu.cpp"
#include "./code/account/EmployeeAccount.h"
#include "./code/account/ManagerAccount.h"

bool ELogged(EmployeeAccount &EUser){
    int choice;
    bool logout = false;
    do {
        system("cls");
        printFile(".\\source\\EMenu.txt");
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

int LogIO(EmployeeAccount &EUser, ManagerAccount &MUser) {
    int choice;
    do {
        system("cls");
        printFile(".\\source\\MainMenu.txt");
        choice = pickMenu();
        switch(choice) {
            case 1:
                EUser.Login();
                if (EUser.check()) {
                    EUser.loadFull();
                    return 1;}
                break;
            case 2:
                if (!EUser.Signin()) break;
                if (EUser.check()) return 1;
                break;
            case 3:
                MUser.Login();
                if (MUser.check()) {
                    MUser.loadFull();
                    return 2;}
                break;
            default: 
                std::cout << "Exiting ..." << std::endl;
                return 0;
                break;
        }
            system("cls");
            printFile(".\\source\\MenuOrExit.txt");
            choice = pickMenu();
            if (!choice) return 0;
    } while(1);
}   // return 1: Employee Account Logged
    // return 2: Manager Account Logged
    // return .: Login Failed

int main() {
    int choice, mode;
    bool login = false;
    EmployeeAccount EUser;
    ManagerAccount MUser;
    do {
        mode = LogIO(EUser, MUser);
        login = mode;
        switch (mode)
        {
            case 1:
                if (ELogged(EUser))
                    login = false;
                break;
            
            default:
                break;
        }
    } while(!login);
}
