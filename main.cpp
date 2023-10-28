#include <iostream>
#include "FuncLib.h"
#include "Info.h"
#include "Account.h"
#include "EmployeeAccount.h"
#include "ManagerAccount.h"
#include "MyDefine.h"
using namespace std;

bool LogIO(EmployeeAccount &User) {
    int choice;
    do {
        system("cls");
        printFile(string(Folder) + "source\\MenuDraw.txt");
        choice = pickMenu();
        system("cls");
        switch(choice) {
            case 1:
                User.Login();
                if (User.check()) {
                    User.loadFull();
                    return User.check();}
                break;
            case 2:
                User.Signin();
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
            cout << "1. Return to menu" << endl;
            cout << "0. Exit program" << endl;
            cin >> choice;
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
