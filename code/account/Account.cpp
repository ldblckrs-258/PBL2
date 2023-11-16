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

std::string Account::getID() {
    return ID;
}

std::string Account::getPwd() {
    return password;
}

void Account::setPwd(std::string input) {
    password = input;
}

bool Account::ChangePwd() {
    int choice;
    std::string cp, np, cnp;
    do {
        system("cls");
        printFile(getFolder() + "source\\ChangePwd.txt");
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
        printFile(getFolder() + "source\\ChangePwd.txt");
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
        printFile(getFolder() + "source\\ChangePwd.txt");
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
    UpdateAcc();
    return true;
}

void Account::saveAcc() {
    std::fstream file;
    file.open(getFolder() + "database\\account\\" + ((manager) ? "managers" : "allacc") +".txt", std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return;
    }
    file << ID << ":" << password << "\n";
    file.close();
}

void Account::UpdateAcc(){
    std::string filename = getFolder() + "database\\account\\" + ((manager) ? "managers" : "allacc") +".txt";
    std::ifstream inFile(filename);
    LinkedList<std::string> lines;

    if (!inFile) {
        std::cerr << "Could not open " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    bool found = false;
    Node<std::string>* cLine = lines.begin();
    while (cLine) {
        std::istringstream iss(cLine->data);
        std::string cID, cPassword;

        if (std::getline(iss, cID, ':') && std::getline(iss, cPassword)) {
            if (cID == ID) {
                cLine->data = ID + ":" + password;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        lines.push_back(ID + ":" + password);
    }

    std::ofstream outFile(filename);
    cLine = lines.begin();
    while (cLine) {
        outFile << cLine->data << '\n';
    }

    outFile.close();
}

bool Account::Login() {
    std::fstream file;
    std::string filename = getFolder() + "database\\account\\" + ((manager) ? "managers" : "allacc");
    filename += ".txt";
    file.open(filename, std::ios::in );
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return false;
    }
    int choice;

    do {
        std::string iID;
        system("cls");
        printFile(getFolder() + "source\\LoginBox.txt");
        gotoXY(67,3); 
        iID = safeInput(30, false);
        gotoXY(0,8);

        bool userFound = false;
        std::string line;

        while (getline(file, line)) {
            size_t pos = line.find(":");
            std::string savedID = line.substr(0, pos);
            if (savedID == iID) {
                userFound = true;
                password = line.substr(pos + 1);
                break;
            }
        }

        if (!userFound) {
            std::cout << "ID does not exist, press 1 to re-enter, 0 to exit" ;
            choice = pickMenu();
            if (choice != 1) return false;
            else {
                file.close();
                file.open(filename, std::ios::in);
            }
        }
        else {
            ID = iID;
            break;
        }
    }   while(1);

    file.close();
    
    do {
        std::string iPwd;
        system("cls");
        printFile(getFolder() + "source\\LoginBox.txt");
        gotoXY(67,3); 
        std::cout << ID;
        gotoXY(67,5);
        iPwd = safeInput();
        gotoXY(0,8);
        holdString("Login your account...", 1);
        if (!checkPwd(iPwd)) {
            std::cout << "Password incorrect, press 1 to re-enter, 0 to exit" ;
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
        } while (1);

    std::cout << "Login in successfully!" << std::endl;
    return true;

}

bool Account::Signin() {
    std::fstream file;
    std::string filename = getFolder() + "database\\account\\" + ((manager) ? "managers" : "allacc");
    filename += ".txt";
    file.open(filename, std::ios::in );

    int choice;
    std::string line;
    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        bool userFound = false;

        gotoXY(73,3); 
        ID = safeInput(30, false);
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
            std::cout << "ID already exists, press 1 to re-enter, 0 to exit" ;
            choice = pickMenu();
            if (choice != 1) return false;
            else {
                file.close();
                file.open(filename, std::ios::in );
            }
        }
        else break;
    } while (1);
        
    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3);
        std::cout << ID;
        gotoXY(73,5);
        password = safeInput();
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
        repwd = safeInput();
        gotoXY(0,10);
        if (repwd != password) {
            std::cout << "Incorrect, press 1 to re-enter, 0 to exit.";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    } while(1);


    saveAcc();
    holdString("New account registered successfully!", 0.5);
    holdString("Login your account...", 0.5);
    return true;
}

void Account:: saveFull(){
    std::string fileName = getFolder() + "database\\account\\"+ ((manager) ? "manager" : "employee") + "\\" + ID + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::out );

    if (!file.is_open()) {
        std::cerr << "Error opening file to save account information." << std::endl;
        return;
    }
    
    file << details.getName() << std::endl;
    file << details.getDoBirth() << std::endl;
    file << details.getPosition() << std::endl;
    file << details.getContact() << std::endl;
    file.close();
}

void Account:: loadFull(){
    std::string fileName = getFolder() + "database\\account\\"+ ((manager) ? "manager" : "employee") + "\\" + ID + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::in );

    if (!file.is_open()) {
        std::cerr << "Error opening file to load account information." << std::endl;
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
