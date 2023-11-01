#include <iostream>
#include "./Info.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include <string>
#include <sstream>

Info::Info(string n, string date, string pos, string ct) : name(n), doBirth(date), position(pos), contact(ct) {}

void Info::getInfo() {
    system("cls");
    printFile(getFolder() + "\\source\\EmployeeTable.txt");
    gotoXY(69,5);   cout << name;
    gotoXY(69,7);   cout << doBirth;
    gotoXY(69,9);   cout << position;
    gotoXY(69,11);   cout << contact;
    gotoXY(0,15);
}

void Info::UpdateInfo() {
    int c;
    cout << "Enter number 1-4 to edit, others to escape: ";
    cin >> c;
    cin.ignore();
    do {
        switch (c) {
            case 1:
                cout << ">> Name: ";
                getline(cin, name);
                break;
            case 2:
                do {
                    if (!isValidDateFormat(doBirth))
                        cout << "Invalid format, example: 01/01/1970" << endl;
                    cout << ">> Date of birth (dd/mm/yyyy): ";
                    getline(cin, doBirth);
                } while (!isValidDateFormat(doBirth));
                break;
            case 3:
                cout << ">> Position: ";
                getline(cin, position);
                break;
            case 4:
                cout << ">> Contact: ";
                getline(cin, contact);
                break;
            default:
                cout << "Exit ..." << endl;
                system("cls");
                return;
        };
        cout << "Edit other (enter 0 to escape): ";
        cin >> c;
        cin.ignore();
    } while (c != 0);
    system("cls");
}

string Info::getName() { return name; }
string Info::getDoBirth() { return doBirth; }
string Info::getPosition() { return position; }
string Info::getContact() { return contact; }

void Info::setName(string input) { name = input; }
void Info::setDoBirth(string input) { doBirth = input; }
void Info::setPosition(string input) { position = input; }
void Info::setContact(string input) { contact = input; }

bool isValidDateFormat(const string& dateStr) {
    if (dateStr.length() != 10) {
        return false;
    }

    if (dateStr[2] != '/' || dateStr[5] != '/') {
        return false;
    }

    istringstream iss(dateStr);
    int day, month, year;
    char separator1, separator2;
    
    if (!(iss >> day >> separator1 >> month >> separator2 >> year)) {
        return false;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
        return false;
    }

    return true;
}