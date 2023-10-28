#include "Account.h"
#include "EmployeeAccount.h"
#include <iostream>
#include <fstream>
#include "MyDefine.h"
using namespace std;
EmployeeAccount::EmployeeAccount(int s) : Account(), salary(s) {}

void EmployeeAccount::ShowInfo() {
    loadFull();
    cout << "> ID: " << ID << endl;
    details.getInfo();
    cout << "- Salary: " << salary << " vnd" << endl;
}

void EmployeeAccount::saveFull() {
    Account::saveFull();
    saveSalary();
}

void EmployeeAccount::saveSalary() {
    string fileName = string(Folder) + "database\\account\\employee\\" + ID + ".txt";
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
    string fileName = string(Folder) + "database\\account\\employee\\" + ID + ".txt";
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
    Account::UpdateInfo();
    saveSalary();
}
