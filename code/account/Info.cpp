#include <iostream>
#include "./Info.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include <string>
#include <sstream>

std::string Info::getName() const { return name; }
std::string Info::getDoBirth() const{ return doBirth; }
std::string Info::getPosition() const { return position; }
std::string Info::getContact() const { return contact; }

void Info::setName(std::string input) { if(!input.empty())  name = input; }
void Info::setDoBirth(std::string input) { if(!input.empty())  doBirth = input; }
void Info::setPosition(std::string input) { if(!input.empty())  position = input; }
void Info::setContact(std::string input) { if(!input.empty())  contact = input; }

Info::Info(std::string n, std::string date, std::string pos, std::string ct) : name(n), doBirth(date), position(pos), contact(ct) {}

bool isValidDateFormat(const std::string& dateStr) {
    if (dateStr.length() != 10) {
        return false;
    }

    if (dateStr[2] != '/' || dateStr[5] != '/') {
        return false;
    }

    std::istringstream iss(dateStr);
    int day, month, year;
    char s1, s2;
    
    if (!(iss >> day >> s1 >> month >> s2 >> year)) {
        return false;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
        return false;
    }

    return true;
}