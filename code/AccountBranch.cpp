#ifndef ACCOUNT_BRANCH
#define ACCOUNT_BRANCH

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "./account/EmployeeAccount.h"
#include "./account/ManagerAccount.h"
#include "./mylib/FuncLib.h"
#include "./mylib/Cursor.h"
extern LinkedList<EmployeeAccount> EAList;

void getEAList(){
    std::ifstream DataFile(getFolder() + "database\\account\\employeeAccount.txt");
    if (!DataFile.is_open()) {
        std::cerr << "Cannot open employees data file" << std::endl;
        return ;
    }

    std::string line;
    DataFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(DataFile, line)){
        if (!line.empty() && line.length() > 10){
            EmployeeAccount profile;
            profile.readLine(line);
            EAList.push_back(profile);
        }
    }
    DataFile.close();
}

void saveEAList(){
    std::ofstream dataFile(getFolder() + "database\\account\\employeeAccount.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Cannot open employees data file" << std::endl;
        return ;
    }
    dataFile << "ID (Username)\tPassword\tManager?\tFull Name\tDate of birth\tPosition\tContact\tSalary\n";
    for (int i=0; i<EAList.getSize(); ++i){
        std::string line;
        line = EAList[i].writeLine();
        dataFile << line;
    }
    dataFile.close();
}

extern LinkedList<ManagerAccount> MAList;

void getMAList(){
    std::ifstream DataFile(getFolder() + "database\\account\\managerAccount.txt");
    if (!DataFile.is_open()) {
        std::cerr << "Cannot open managers data file" << std::endl;
        return ;
    }

    std::string line;
    DataFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(DataFile, line)){
        if (!line.empty() && line.length() > 10){
            ManagerAccount profile;
            profile.readLine(line);
            MAList.push_back(profile);
        }
    }
    DataFile.close();
}

void saveMAList(){
    std::ofstream dataFile(getFolder() + "database\\account\\managerAccount.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Cannot open managers data file" << std::endl;
        return ;
    }
    dataFile << "ID (Username)\tPassword\tManager?\tFull Name\tDate of birth\tPosition\tContact\n";
    for (int i=0; i<MAList.getSize(); ++i){
        std::string line;
        line = MAList[i].writeLine();
        dataFile << line;
    }
    dataFile.close();
}


template <typename T>
int login(LinkedList<T>& accList) {
    int choice, index;
    std::string iID;

    do {
        system("cls");
        printFile(getFolder() + "source\\LoginBox.txt");
        gotoXY(67,3); 
        iID = safeInput(30, false);
        gotoXY(0,8);

        index = accList.search(iID, &T::getID);
        if (index == -1) {
            std::cout << "ID does not exist, press 1 to re-enter, 0 to exit";
            choice = pickMenu();
            if (choice != 1) return -1;
        } else {
            break;
        }
    } while(1);

    do {
        std::string iPwd;
        system("cls");
        printFile(getFolder() + "source\\LoginBox.txt");
        gotoXY(67,3); 
        std::cout << iID;
        gotoXY(67,5);
        iPwd = safeInput();
        gotoXY(0,8);
        holdString("Login your account...", 0.3);

        if (iPwd != accList[index].getPwd()) {
            std::cout << "Password incorrect, press 1 to re-enter, 0 to exit";
            choice = pickMenu();
            if (choice != 1) return -1;
        } else {
            break;
        }
    } while (1);

    holdString(">> Login successfully !", 0.5);
    return index;
}

template<typename T>
int signin(LinkedList<T>& acclist){
    int choice;
    T newAcc;
    std::string iID, iPwd, rePwd;
    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3); 
        iID = safeInput(30, false);
        gotoXY(0,10);
        bool userFound = (acclist.search(iID, &T::getID) != -1);
        if (userFound){
            std::cout << "ID already exists, press 1 to re-enter, 0 to exit" ;
            choice = pickMenu();
            if (choice != 1) return -1;
        }
        else break;
    } while (1);
    newAcc.setID(iID);
    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3);
        std::cout << iID;
        gotoXY(73,5);
        iPwd = safeInput();
        gotoXY(0,10);
        if (iPwd.length() < 6 || iPwd.length() > 15) {
            std::cout << "Password length must be of 6-15 characters, press 1 to re-enter, 0 to exit.";
            choice = pickMenu();
            if (choice != 1) return false;
        }
        else break;
    } while(1);

    do {
        system("cls");
        printFile(getFolder() + "source\\SigninBox.txt");
        gotoXY(73,3);
        std::cout << iID;
        gotoXY(73,5);
        drawLine('*',iPwd.length());
        gotoXY(73,7);
        rePwd = safeInput();
        gotoXY(0,10);
        if (rePwd != iPwd) {
            std::cout << "Incorrect, press 1 to re-enter, 0 to exit.";
            choice = pickMenu();
            if (choice != 1) return -1;
        }
        else break;
    } while(1);
    
    newAcc.setPwd(iPwd);

    holdString("New account registered successfully!", 0.3);
    holdString("Login your account...", 0.3);

    newAcc.UpdateInfo();
    acclist.push_back(newAcc);
    return acclist.getSize() - 1;
}

#endif // !ACCOUNT_BRANCH