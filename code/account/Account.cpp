#include "./Account.h"
#include <iostream>
#include "../mylib/FuncLib.h"
#include <fstream>
#include "../mylib/Cursor.h"
Account::Account(std::string ID, std::string pwd) : ID(ID), password(pwd) {
    if (ID == "account" && password == "000000")
        status = false;
    else
        status = true;
}

bool Account::checkPwd(std::string check) {
    return check == password;
}

std::string Account::getID() {
    return ID;
}

std::string Account::getPwd() {
    return password;
}

void Account::setPwd(std::string input) {
    password = input;
}

bool Account::check() {
    return status;
}

bool Account::ChangePwd() {
    int choice;
    std::string cp, np, cnp;
    do {
        system("cls");
        printFile(getFolder() + "source\\ChangePwd.txt");
        gotoXY(73,3); 
        cp = hideInput();
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
        printFile(getFolder() + "source\\ChangePwd.txt");
        gotoXY(73,3); 
        drawLine('*', cp.length());
        gotoXY(73,5);
        np = hideInput();
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
        printFile(getFolder() + "source\\ChangePwd.txt");
        gotoXY(73,3); 
        drawLine('*', cp.length());
        gotoXY(73,5);
        drawLine('*', np.length());
        gotoXY(73,7); 
        cnp = hideInput();
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

void Account::saveAcc() {
    std::fstream file;
    file.open(getFolder() + "database\\account\\allacc.txt", std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return;
    }
    file << ID << ":" << password << "\n";
    file.close();
}

bool Account::Login() {
    std::fstream file;
    file.open(getFolder() +"database\\account\\allacc.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return false;
    }
    system("cls");
    printFile(getFolder() + "source\\LoginBox.txt");
    int choice;
    // std::cout << "Enter your user ID: ";
    gotoXY(67,3); 
    getline(std::cin, ID);
    gotoXY(0,8);
    bool userFound = false;
    std::string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        std::string savedID = line.substr(0, pos);
        password = line.substr(pos + 1);
        if (savedID == ID) {
            userFound = true;
            break;
        }
    }
    file.close();
    if (userFound) {
        std::string inputPwd;
        // std::cout << "Enter your password: ";
        gotoXY(67,5);
        inputPwd = hideInput();
        gotoXY(0,8);
        holdString("Login your account...", 1);
        if (checkPwd(inputPwd)) {
            std::cout << "Logged in successfully!" << std::endl;
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
    std::fstream file;
    file.open(getFolder() + "database\\account\\allacc.txt", std::ios::in);
    if (!file.is_open()) {
        holdString("Error opening file allacc.txt !");
        return false;
    }
    int choice;
    bool userFound = false;
    std::string line;
    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3); 
        getline(std::cin, ID);
        gotoXY(0,10);
        while (getline(file, line)) {
            size_t pos = line.find(":");
            std::string savedID = line.substr(0, pos);
            password = line.substr(pos + 1);
            if (savedID == ID) {
                userFound = true;
                break;
            }
        }
        file.close();
        if (userFound){
            holdString("ID already exists, press 1 to re-enter, 0 to exit.");
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    } while (1);
        
    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3);
        std::cout << ID;
        gotoXY(73,5);
        password = hideInput();
        gotoXY(0,10);
        if (password.length() < 6 || password.length() > 15) {
            std::cout << "Password length must be of 6-15 characters, press 1 to re-enter, 0 to exit.";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    } while(1);

    std::string repwd;

    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3);
        std::cout << ID;
        gotoXY(73,5);
        drawLine('*',password.length());
        gotoXY(73,7);
        repwd = hideInput();
        gotoXY(0,10);
        if (repwd != password) {
            std::cout << "Incorrect, press 1 to re-enter, 0 to exit.";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    } while(1);


    saveAcc();
    status = true;
    holdString("New account registered successfully!", 0.5);
    holdString("Login your account...", 1);
    return true;
}

void Account:: saveFull(){
    std::string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::out );

    if (!file.is_open()) {
        std::cerr << "Error opening file to save employee information." << std::endl;
        return;
    }
    
    file << details.getName() << std::endl;
    file << details.getDoBirth() << std::endl;
    file << details.getPosition() << std::endl;
    file << details.getContact() << std::endl;
    file.close();
}

void Account:: loadFull(){
    std::string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::in );

    if (!file.is_open()) {
        std::cerr << "Error opening file to load employee information." << std::endl;
        return;
    }

    std::string line;
    if (getline(file, line)) details.setName(line);
    if (getline(file, line)) details.setDoBirth(line);
    if (getline(file, line)) details.setPosition(line);
    if (getline(file, line)) details.setContact(line);

    file.close();
}

void Account::UpdateInfo(){
    details.UpdateInfo();
    saveFull();
}