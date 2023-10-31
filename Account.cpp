#include "Account.h"
#include <iostream>
#include "FuncLib.h"
#include <fstream>
#include "Cursor.h"
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
    file.open(getFolder() + "database\\account\\allacc.txt", ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    file << ID << ":" << password << "\n";
    file.close();
}

bool Account::Login() {
    fstream file;
    file.open(getFolder() +"database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return false;
    }
    system("cls");
    printFile(getFolder() + "source\\LoginBox.txt");
    int choice;
    // cout << "Enter your user ID: ";
    gotoXY(67,3); 
    getline(cin, ID);
    gotoXY(0,8);
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
        // cout << "Enter your password: ";
        gotoXY(67,5);
        inputPwd = hideInput();
        gotoXY(0,8);
        holdString("Login your account...", 1);
        if (checkPwd(inputPwd)) {
            cout << "Logged in successfully!" << endl;
            status = true;
            return true;
        }
        holdString("Login failed. Incorrect password!");
        return false;
    } 
    else {
        holdString("User not found. Please register a new account!");
        return false;
    }
}

bool Account::Signin() {
    fstream file;
    file.open(getFolder() + "database\\account\\allacc.txt", ios::in);
    if (!file.is_open()) {
        holdString("Error opening file allacc.txt !");
        return false;
    }
    int choice;
    bool userFound = false;
    string line;
    system("cls");
    printFile(getFolder() + "source\\SigninBox.txt");
    gotoXY(73,3); 
    getline(cin, ID);
    gotoXY(0,10);
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
    if (userFound){
        holdString("ID already exists, please enter another !");
        return false;
    }

    gotoXY(73,5);
    password = hideInput();
    gotoXY(0,10);
    if (password.length() < 6 || password.length() > 15) {
        holdString("Password length must be of 6-15 characters!");
        return false;
    }

    string repwd;
    gotoXY(73,7);
    repwd = hideInput();
    gotoXY(0,10);
    if (repwd != password) {
        holdString("Incorrect, please confirm again!", 2);
        return false;
    }

    saveAcc();
    status = true;
    holdString("New account registered successfully!", 0.5);
    holdString("Login your account...", 1);
    return true;
}

void Account:: saveFull(){
    string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
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
    string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
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
