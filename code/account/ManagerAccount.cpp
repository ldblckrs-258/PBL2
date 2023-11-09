#include "./ManagerAccount.h"
#include <iostream>
#include <fstream>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

std::vector<std::string> ManagerAccount::EmployeeList;

ManagerAccount::ManagerAccount() : Account() {
    manager = true;
}

void ManagerAccount::getEL(){
    std::ifstream file(getFolder() +"database\\account\\allacc.txt");
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return ;
    }
    std::string line;
    while (std::getline(file, line)) {
        EmployeeList.push_back(line);
    }
    file.close();
}

void ManagerAccount::loadFull(){
    Account::loadFull();
}

void ManagerAccount::ShowInfo() {
    loadFull();
    details.getInfo("EmployeeTable.txt");
    gotoXY(69,3);   std::cout << ID ;
    gotoXY(50,13);  std::cout << "5. Employees";
    gotoXY(69,13);  std::cout << EmployeeList.size();
    gotoXY(0,15);
}

void ManagerAccount::saveAcc(){
    std::fstream file;
    file.open(getFolder() + "database\\account\\managers.txt", std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return;
    }
    file << ID << ":" << password << "\n";
    file.close();
}