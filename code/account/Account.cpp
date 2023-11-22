#include "./Account.h"
#include <iostream>
#include "../mylib/FuncLib.h"
#include <fstream>
#include "../mylib/LinkedList.cpp"
#include <sstream>
#include "../mylib/Cursor.h"

Account::Account(std::string ID, std::string pwd) : ID(ID), password(pwd), manager(false) {}

bool Account::checkPwd(std::string value) {
    return value == password;
}

std::string Account::getID() const{
    return ID;
}

std::string Account::getName() const{
    return details.getName();
}

std::string Account::getPosition() const{
    return details.getPosition();
}

std::string Account::getContact() const{
    return details.getContact();
}

std::string Account::getPwd() const{
    return password;
}

void Account::setID(std::string input) {
    ID = input;
}

void Account::setPwd(std::string input) {
    password = input;
}

bool Account::isManager() const{
    return manager;
}
bool Account::ChangePwd() {
    int choice;
    std::string cp, np, cnp;
    LinkedList<std::string> inputList;
    inputList.push_back("CHANGE PASSWORD");
    inputList.push_back("Current Password");
    inputList.push_back("New Password");
    inputList.push_back("Confirm Password");
    do {
        system("cls");
        printInputBox(inputList, 2);
        gotoXY(73,3); 
        cp = safeInput();
        gotoXY(0,10);
        if (cp != password){
            std::cout << "Current password you entered is incorrect, press 1 to re-enter, 0 to escape!";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    }   while (1);

    do {
        system("cls");
        printInputBox(inputList, 1);
        gotoXY(73,3); 
        drawLine('*', cp.length());
        gotoXY(73,5);
        np = safeInput();
        gotoXY(0,10);
        if (np.length() < 6 || np.length() > 15) {
            std::cout << "Password length must be of 6-15 characters, press 1 to re-enter, 0 to escape!";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    }   while (1);

    do {
        system("cls");
        printInputBox(inputList, 1);
        gotoXY(73,3); 
        drawLine('*', cp.length());
        gotoXY(73,5);
        drawLine('*', np.length());
        gotoXY(73,7); 
        cnp = safeInput();
        gotoXY(0,10);
        if (cnp != np){
            std::cout << "Unable to confirm new password, press 1 to re-enter, 0 to escape!";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    }   while (1);
    password = np;
    return true;
}

