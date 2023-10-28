#include "Account.h"
#include <iostream>
#include "FuncLib.h"
#include <fstream>
#include "MyDefine.h"
using namespace std;
Account::Account(string ID, string pwd) : ID(ID), password(pwd) {
    if (ID == "account" && password == "000000")
        status = false;
    else
        status = true;
}

bool Account::checkPwd(string check) {
    return check == password;
}

string Account::getID() {
    return ID;
}

string Account::getPwd() {
    return password;
}

void Account::setPwd(string input) {
    password = input;
}

bool Account::check() {
    return status;
}

bool Account::ChangePwd() {
    string old;
    Start:
    cout << "Enter your OLD password: ";
    cin >> old;
    if (old == "0")
        return false;
    else if (!checkPwd(old)) {
        cout << "The old password is incorrect, please re-enter (or Enter 0 to exit) " << endl;
        goto Start;
    }

    cout << "Enter your NEW password: ";
    cin >> password;
    cout << "Password Changed!";
    return true;
}

void Account::saveAcc() {
    fstream file;
    file.open(string(Folder) + "database\\account\\allacc.txt", ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    file << ID << ":" << password << "\n";
    file.close();
}

void Account::Login() {
    fstream file;
    file.open(string(Folder) +"database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    cout << "Enter your user ID: ";
    cin >> ID;
    bool userFound = false;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        string savedID = line.substr(0, pos);
        password = line.substr(pos + 1);
        if (savedID == ID) {
            userFound = true;
            break;
        }
    }
    file.close();
    if (userFound) {
        string inputPwd;
        cout << "Enter your password: ";
        inputPwd = hideInput();
        holdString("Login your account...", 1);
        if (checkPwd(inputPwd)) {
            cout << "Logged in successfully!" << endl;
            status = true;
            return;
        }
        cout << "Login failed. Incorrect password." << endl;
    } else
        cout << "User not found. Please register a new account." << endl;
    return;
}

void Account::Signin() {
    fstream file;
    file.open(string(Folder) + "database\\account\\allacc.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    bool userFound = false;
    do {
        if (userFound) {
            cout << "ID already exists, please enter another !" << endl;;
        }
        userFound = false;
        cout << "Enter a new user ID: ";
        cin >> ID;
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(":");
            string savedID = line.substr(0, pos);
            password = line.substr(pos + 1);
            if (savedID == ID) {
                userFound = true;
                break;
            }
        }
        if (ID == "account")
            userFound = true;
    } while (userFound);
    file.close();

    cout << "Enter a new password: ";
    password = hideInput();
    while (password.length() < 6 || password.length() > 15) {
        cout << "Password length must be of 6-15 characters: ";
        password = hideInput();
    }
    string repwd;
    do {
        cout << "Re-enter password: ";
        repwd = hideInput();
        if (repwd != password) {
            cout << "Incorrect, please confirm again! " << endl;
        } else
            break;
    } while (1);
    saveAcc();
    status = true;
    holdString("New account registered successfully!", 0.5);
    holdString("Login your account...", 1);
}

void Account:: saveFull(){
    string fileName = string(Folder) + "database\\account\\employee\\" + ID + ".txt";
    fstream file;
    file.open(fileName, ios::out );

    if (!file.is_open()) {
        cerr << "Error opening file to save employee information." << endl;
        return;
    }
    
    file << details.getName() << endl;
    file << details.getDoBirth() << endl;
    file << details.getPosition() << endl;
    file << details.getContact() << endl;
    file.close();
}

void Account:: loadFull(){
    string fileName = string(Folder) + "database\\account\\employee\\" + ID + ".txt";
    fstream file;
    file.open(fileName, ios::in );

    if (!file.is_open()) {
        cerr << "Error opening file to load employee information." << endl;
        return;
    }

    string line;
    if (getline(file, line)) details.setName(line);
    if (getline(file, line)) details.setDoBirth(line);
    if (getline(file, line)) details.setPosition(line);
    if (getline(file, line)) details.setContact(line);

    file.close();
}

void Account::UpdateInfo(){
    details.UpdateInfo();
    saveFull();}
