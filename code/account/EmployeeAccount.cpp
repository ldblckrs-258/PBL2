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
    details.getInfo("EmployeeTable.txt");
    gotoXY(69,3);   std::cout << ID ;
    gotoXY(69,13);  std::cout << salary << " vnd";
    gotoXY(0,15);
}


void EmployeeAccount::readLine(const std::string &str) {
    std::string part;
    int count = 0;
    for (char c : str) {
        if (c != '\t') part += c; 
        else {
            switch (count)
            {
                case 0:
                    ID = clearStr(part);
                    break;
                case 1:
                    password = clearStr(part);
                    break;
                case 2:
                    try {
                        manager = stoi(clearStr(part));
                    }
                    catch (const std::exception&e)
                    {   
                        std::cerr << e.what() << std::endl;
                        manager = false;
                    }
                    break;
                case 3:
                    details.setName(clearStr(part));
                    break;
                case 4:
                    details.setDoBirth(clearStr(part));
                    break;
                case 5:
                    details.setPosition(clearStr(part));
                    break;
                case 6:
                    details.setContact(clearStr(part));
                    break;
                default:
                    break;
            }
        part.clear();
        ++count;
        }
    }
    try {salary = stoi(clearStr(part));}
    catch (const std::exception&e)
    {   
        std::cerr << e.what() << std::endl;
        salary = -1;
    }
}

std::string EmployeeAccount::writeLine(){
    return ID + "\t" + 
        password + "\t" + 
        std::to_string(manager) + "\t" + 
        details.getName() + "\t" + 
        details.getDoBirth() + "\t" + 
        details.getPosition() + "\t" + 
        details.getContact() + "\t" + 
        std::to_string(salary) + "\n";
}


void EmployeeAccount::UpdateInfo() {
    ShowInfo();
    Account::UpdateInfo();
}
