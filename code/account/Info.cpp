#include <iostream>
#include "./Info.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include <string>
#include <sstream>

Info::Info(std::string n, std::string date, std::string pos, std::string ct) : name(n), doBirth(date), position(pos), contact(ct) {}

void Info::getInfo(std::string sfname, int except) {
    system("cls");
    printFile(getFolder() + "\\source\\" + sfname);
    bool full = true;
    if (sfname == "InfoTable.txt")  full = false;
    if (except !=1) {gotoXY(69,full ? 5 : 3);   std::cout << name;}
    if (except !=2) {gotoXY(69,full ? 7 : 5);   std::cout << doBirth;}
    if (except !=3) {gotoXY(69,full ? 9 : 7);   std::cout << position;}
    if (except !=4) {gotoXY(69,full ? 11 : 9);   std::cout << contact;}
    gotoXY(0,full ? 15 : 11);
}

void Info::UpdateInfo() {
    int c;
    std::string temp;
    do {
        getInfo("InfoTable.txt");
        std::cout << "Press number 1-4 to edit, 0 to escape: ";
        c = pickMenu();
        switch (c) {
            case 1:
                getInfo("InfoTable.txt",1);
                std::cout << ">> Enter Name: ";
                gotoXY(69,3);
                getline(std::cin, name);
                gotoXY(0,11);
                break;
            case 2:
                do {
                    getInfo("InfoTable.txt",2);
                    if (!isValidDateFormat(temp))
                        std::cout << "Invalid format, example: 01/01/1970" << std::endl;
                    std::cout << ">> Enter Date of birth (dd/mm/yyyy): ";
                    gotoXY(69,5);
                    getline(std::cin, temp);
                    gotoXY(0,11);
                } while (!isValidDateFormat(temp));
                doBirth = temp;
                break;
            case 3:
                getInfo("InfoTable.txt",3);
                std::cout << ">> Enter Position: ";
                gotoXY(69,7);
                getline(std::cin, position);
                gotoXY(0,11);
                break;
            case 4:
                getInfo("InfoTable.txt",4);
                std::cout << ">> Contact: ";
                gotoXY(69,9);
                getline(std::cin, contact);
                gotoXY(0,11);
                break;
            default:
                std::cout << "Exit ..." << std::endl;
                system("cls");
                return;
        };
    } while (c != 0);
    system("cls");
}

std::string Info::getName() { return name; }
std::string Info::getDoBirth() { return doBirth; }
std::string Info::getPosition() { return position; }
std::string Info::getContact() { return contact; }

void Info::setName(std::string input) { name = input; }
void Info::setDoBirth(std::string input) { doBirth = input; }
void Info::setPosition(std::string input) { position = input; }
void Info::setContact(std::string input) { contact = input; }

bool isValidDateFormat(const std::string& dateStr) {
    if (dateStr.length() != 10) {
        return false;
    }

    if (dateStr[2] != '/' || dateStr[5] != '/') {
        return false;
    }

    std::istringstream iss(dateStr);
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