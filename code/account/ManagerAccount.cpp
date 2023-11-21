#include "./ManagerAccount.h"
#include <iostream>
#include <fstream>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

LinkedList<std::string> ManagerAccount::EmployeeList;

ManagerAccount::ManagerAccount() : Account() {
    manager = true;
}

void ManagerAccount::ShowInfo() {
    details.getInfo("EmployeeTable.txt");
    gotoXY(69,3);   std::cout << ID ;
    gotoXY(50,13);  std::cout << "5. Employees";
    gotoXY(69,13);  std::cout << EmployeeList.getSize();
    gotoXY(0,15);
}

void ManagerAccount::readLine(const std::string &str) {
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
                default:
                    break;
            }
        part.clear();
        ++count;
        }
    }
    details.setContact(clearStr(part));
}

std::string ManagerAccount::writeLine(){
    return ID + "\t" + 
        password + "\t" + 
        std::to_string(manager) + "\t" + 
        details.getName() + "\t" + 
        details.getDoBirth() + "\t" + 
        details.getPosition() + "\t" + 
        details.getContact() + "\n";
}