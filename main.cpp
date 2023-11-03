#include <iostream>
#include "./code/mylib/FuncLib.h"
#include "./code/menu1.cpp"

void ELogged(EmployeeAccount &EUser){
    int choice;
    do {
        system("cls");
        printFile(".\\source\\EMenu.txt");
        choice = pickMenu();
        switch (choice)
        {
        case 1:
            // PSMenu();
            break;
        case 2:
            // GSMenu();
            break;
        case 3:
            // ITMenu();
            break;
        case 4:
            // ASMenu();
            break;        
        default:
            system("pause");
            return;
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
                std::cout << "Exiting program." << std::endl;
                return 0;
                break;
        }
            system("cls");
            printFile(".\\source\\MenuOrExit.txt");
            choice = pickMenu();
            if (!choice) return false;
    } while(1);
}   // return 1: Employee Account Logged
    // return 2: Manager Account Logged
    // return .: Login Failed

int main() {
    int choice, mode;
    EmployeeAccount EUser;
    ManagerAccount MUser;
    mode = LogIO(EUser, MUser);
    switch (mode)
    {
    case 1:
        ELogged(EUser);
        break;
    
    default:
        break;
    }
    system("pause");
}
