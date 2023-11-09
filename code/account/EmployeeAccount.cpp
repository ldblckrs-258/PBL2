#include "./Account.h"
#include "./EmployeeAccount.h"
#include <iostream>
#include <fstream>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

EmployeeAccount::EmployeeAccount(int s) : Account(), salary(s) {
    manager = false;
}

void EmployeeAccount::ShowInfo() {
    loadFull();
    details.getInfo("EmployeeTable.txt");
    gotoXY(69,3);   std::cout << ID ;
    gotoXY(69,13);  std::cout << salary << " vnd";
    gotoXY(0,15);
}

void EmployeeAccount::saveFull() {
    Account::saveFull();
    saveSalary();
}

void EmployeeAccount::saveSalary() {
    std::string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::out | std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file to save employee information." << std::endl;
        return;
    }
    file << salary << std::endl;
    file.close();
}

void EmployeeAccount::loadFull() {
    std::string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Error opening file to load employee information." << std::endl;
        return;
    }

    Account::loadFull();
    std::string line;
    int lineCount = 1;
    while (getline(file, line)) {
        if (lineCount == 5)
            break;
        ++lineCount;
    }

    salary = stoi(line);
    file.close();
}

void EmployeeAccount::UpdateInfo() {
    ShowInfo();
    Account::UpdateInfo();
    saveSalary();
}
