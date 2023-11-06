#include <iostream>
#include "./mylib/FuncLib.h"
#include "./account/EmployeeAccount.h"
#include "./account/ManagerAccount.h"


bool ASMenu(EmployeeAccount &EA){
    int choice;
    do {
        system("cls");
        printFile(".\\source\\EAS.txt");
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                EA.ShowInfo();
                holdString("");
                break;
            case 2:
                EA.UpdateInfo();
                break;
            case 3:
                EA.ChangePwd();
                break;
            case 4:
                return true;
                break;        
            default:
                return false;
        }
    } while (1);
    return false;
}