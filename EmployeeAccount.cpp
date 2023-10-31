#include "Account.h"
#include "EmployeeAccount.h"
#include <iostream>
#include <fstream>
#include "FuncLib.h"
#include "Cursor.h"

EmployeeAccount::EmployeeAccount(int s) : Account(), salary(s) {}

void EmployeeAccount::ShowInfo() {
    loadFull();
    details.getInfo();
    gotoXY(69,3);   cout << ID ;
    gotoXY(69,13);  cout << salary << " vnd";
    gotoXY(0,15);
}

void EmployeeAccount::saveFull() {
    Account::saveFull();
    saveSalary();
}

void EmployeeAccount::saveSalary() {
    string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
    fstream file;
    file.open(fileName, ios::out | ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file to save employee information." << endl;
        return;
    }
    file << salary << endl;
    file.close();
}

void EmployeeAccount::loadFull() {
    string fileName = getFolder() + "database\\account\\employee\\" + ID + ".txt";
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file to load employee information." << endl;
        return;
    }

    Account::loadFull();
    string line;
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
