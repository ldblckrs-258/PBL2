#include <iostream>
#include "./code/mylib/FuncLib.h"
#include "./code/account/Info.h"
#include "./code/account/Account.h"
#include "./code/account/EmployeeAccount.h"
#include "./code/account/ManagerAccount.h"

bool LogIO(EmployeeAccount &User) {
    int choice;
    bool check;
    do {
        system("cls");
        printFile(getFolder() + "source\\MenuDraw.txt");
        choice = pickMenu();
        switch(choice) {
            case 1:
                User.Login();
                if (User.check()) {
                    User.loadFull();
                    return User.check();}
                break;
            case 2:
                if (!User.Signin()) break;
                if (User.check()) return User.check();
                break;
            case 0:
                cout << "Exiting program." << endl;
                return false;
                break;  
            default: 
                cout << "Invalid choice. Exiting program." << endl;
                return false;
                break;
        }
            system("cls");
            printFile(getFolder() + "source\\MenuOrExit.txt");
            choice = pickMenu();
            if (!choice) return false;
    } while(1);
}

int main() {
    system("cls");
    EmployeeAccount User;
    if (LogIO(User)){
        system("cls");
        User.UpdateInfo();
        User.ShowInfo();
    }
    system("pause");
}
