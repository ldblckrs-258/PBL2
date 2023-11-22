#include "./AccountBranch.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>


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
int Login(LinkedList<T>& accList) {
    int choice, index;
    std::string iID;
    LinkedList<std::string> inputList;
    inputList.push_back("LOGIN");
    inputList.push_back("ID");
    inputList.push_back("Password");
    do {
        system("cls");
        printInputBox(inputList, 2);
        gotoXY(72,3); 
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
        printInputBox(inputList, 2);
        gotoXY(72,3); 
        std::cout << iID;
        gotoXY(72,5);
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
template int Login<EmployeeAccount>(LinkedList<EmployeeAccount>& acclist);
template int Login<ManagerAccount>(LinkedList<ManagerAccount>& acclist);

template<typename T>
int Signin(LinkedList<T>& acclist){
    int choice;
    T newAcc;
    std::string iID, iPwd, rePwd;
    LinkedList<std::string> inputList;
    inputList.push_back("REGISTER");
    inputList.push_back("ID");
    inputList.push_back("Password");
    inputList.push_back("Confirm Password");
    do {
        system("cls");
        printInputBox(inputList, 2);
        gotoXY(72,3); 
        iID = safeInput(30, false);
        gotoXY(0,10);
        bool userFound = (acclist.search(iID, &T::getID) != -1);
        if (userFound){
            std::cout << "ID already exists, press 1 to re-enter, 0 to exit" ;
            choice = pickMenu();
            if (choice != 1) return -1;
        }
        else if (iID.length() < 6 || iID.length() > 25){
            std::cout << "ID must be of 6-25 characters, press 1 to re-enter, 0 to exit" ;
            choice = pickMenu();
            if (choice != 1) return -1;
        }
        else break;
    } while (1);
    newAcc.setID(iID);
    do {
        system("cls");
        printInputBox(inputList, 2);
        gotoXY(72,3);
        std::cout << iID;
        gotoXY(72,5);
        iPwd = safeInput();
        gotoXY(0,10);
        if (iPwd.length() < 6 || iPwd.length() > 15) {
            std::cout << "Password length must be of 6-15 characters, press 1 to re-enter, 0 to exit.";
            choice = pickMenu();
            if (choice != 1) return -1;
        }
        else break;
    } while(1);

    do {
        system("cls");
        printInputBox(inputList, 2);
        gotoXY(72,3);
        std::cout << iID;
        gotoXY(72,5);
        drawLine('*',iPwd.length());
        gotoXY(72,7);
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

    holdString("New account registered successfully!", 0.5);

    newAcc.UpdateInfo();
    acclist.push_back(newAcc);
    return acclist.getSize() - 1;
}
template int Signin<EmployeeAccount>(LinkedList<EmployeeAccount>& acclist);
template int Signin<ManagerAccount>(LinkedList<ManagerAccount>& acclist);

void EditExistAccount(){
    system("cls");
    LinkedList<std::string> menulist;
    menulist.push_back("EDIT EMPLOYEE INFORMATION");
    menulist.push_back("1. Access via ID");
    menulist.push_back("2. Access via Name");
    menulist.push_back("0. Exit");
    int choice;
    do {
        system("cls");
        printOptions(menulist, 1);
        choice = pickMenu();
        int index;  std::string value;
        moveLine(2);
        printFile(getFolder() + "source\\InputOne.txt");
        switch (choice)
        {
            case 1:
                moveCursor(71,-4);   std::cout << "ACCESS VIA ID" << std::endl;
                moveCursor(61,1);   std::cout << "ID" << std::endl;
                moveCursor(72,-1);   value = safeInput(30, false);
                moveLine(2);
                index = EAList.search(value, &Account::getID);
                break;
            case 2:
                moveCursor(70,-4);   std::cout << "SACCESS VIA NAME" << std::endl;
                moveCursor(56,1);   std::cout << "Species name" << std::endl;
                moveCursor(72,-1);   value = safeInput(30, false);
                moveLine(2);
                index = EAList.search(value, &Account::getName);
                break;
            default:
                return;
        }

        if (index != -1) {
            EAList[index].UpdateInfo(true);
            setColor(4);
            std::cout << "PRESS BACKSCAPE TO REMOVE THIS SPECIES, OTHERS NUMBER TO REFUSE" << std::endl;
            setColor(7);
            int choice = pickMenu();
            if (choice == -99){
                EAList.remove(index);
                holdString("Deleting ...", 0.5);
            }
            saveEAList();
        }
        else {
            std::cout << "Value not found!" << std::endl;
        }
        system("pause");
    } while (1);
}

void ViewAllEmployee(){
    system("cls");
    LinkedList<std::string> sample = getSample("AllEmployeeSample.txt");
    setColor(3);    std::cout << sample[0]; setColor(7); 
    Node<EmployeeAccount>* temp = EAList.begin();
    while (temp) {
        setColor(3);    std::cout << sample[1]; setColor(7); 
        moveCursor(7,-2);   std::cout << temp->data.getID();
        moveInLine(36); std::cout << temp->data.getName();
        moveInLine(65); std::cout << temp->data.getPosition();
        moveInLine(94); std::cout << temp->data.getContact();
        moveInLine(129);
        std::cout << std::setw(17) << std::right << commaInt(temp->data.getSalary()) << " vnd";
        moveLine(2);
        temp = temp->next;
    }
    moveLine(-1);   setColor(3);    std::cout << sample[2] << std::endl;    setColor(7); 
    system("pause");
}
