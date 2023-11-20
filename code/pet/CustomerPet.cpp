#include "./CustomerPet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

CustomerPet::CustomerPet(std::string pid, std::string sid, std::string oid) : Pet(pid, sid), owner_id(oid), service_used(sid) {}

std::string CustomerPet::getOwnerID() const{
    return owner_id;
}

std::string CustomerPet::getStatus() const{
    return status;
}

void CustomerPet::setPet(){
    int choice;
    LinkedList<std::string> list;
    list.push_back("PET OPTIONS");
    list.push_back("1. Edit information");
    list.push_back("2. Edit characteristic");
    list.push_back("0. Exit");

    do {
        showDetails();  
        std::cout << std::endl << std::endl;
        printOptions(list);
        choice = pickMenu();                
        switch (choice)
        {
        case 1:
            editInfo();
            break;
        case 2:
            editChar();
            break;
        default:
            break;
        }
    } while(choice);
}

void CustomerPet::editInfo() {
    int c;
    showDetails();
    std::cout << ">> Press a number 1-7 to edit, others to escape: ";
    c = pickMenu();
    do {
        switch (c) {
        case 1:
            showDetails(1);
            std::cout << ">> Enter pet name";
            gotoXY(34,5);  
            name = safeInput(36, false);
            gotoXY(0,21);
            break;
        case 2:
            showDetails(2);
            std::cout << ">> Enter age (an integer)";
            gotoXY(34,7);  
            try {
                age = stod(safeInput(10, false));
            }
            catch(const std::exception& e){
                age = 0;
            } 
            gotoXY(0,21);
            break;
        case 3:
            showDetails(3);
            std::cout << ">> Enter gender (1 for male, 0 for female)";
            gotoXY(34,9);  
            try {
                gender = stod(safeInput(1, false));
            }
            catch(const std::exception& e){
                gender = 1;
            }
            gotoXY(0,21);
            break;
        case 4:
            showDetails(4);
            std::cout << ">> Enter species id";
            gotoXY(34,11);  
            species_id = safeInput(36, false);
            gotoXY(0,21);
            break;
        case 5:
            showDetails(5);
            std::cout << ">> Enter current status";
            gotoXY(34,13);  
            status = safeInput(36, false);
            gotoXY(0,21);
            break;
        case 6:
            showDetails(6);
            std::cout << ">> Enter owner id";
            gotoXY(34,15);                  
            owner_id = safeInput(36, false); 
            gotoXY(0,21);
            break;
        case 7:
            showDetails(7);
            std::cout << ">> Enter service used id";
            gotoXY(34,17);  
            service_used = safeInput(36, false);  
            gotoXY(0,21);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        };
        drawLine(' ', 100);
        moveCursor(-100, 0);
        std::cout << "Edit other (press 0 to escape): ";
        c = pickMenu();
    } while (c != 0);
}

void CustomerPet::showDetails(int except) {
    Pet::showDetails(except);
    gotoXY(15, 15); std::cout << "6. Owner";
    if (except != 6) {gotoXY(34,15);   std::cout << owner_id;}
    gotoXY(15, 17); std::cout << "7. Service Used";
    if (except != 7) {gotoXY(34,17);   std::cout << service_used;}
    gotoXY(0,21);
}

void CustomerPet::readLine(const std::string &str){
        std::string part;
    int count = 0;
    for (char c : str) {
        if (c != '\t') part += c; 
        else {
            switch (count)
            {
                case 0:
                    id = clearStr(part);
                    break;
                case 1:
                    name = clearStr(part);
                    break;
                case 2:
                    try {
                        age = stoi(clearStr(part));
                    }
                    catch (const std::exception&e)
                    {   
                        std::cerr << e.what() << std::endl;
                        age = -1;
                    }
                    break;
                case 3:
                    try {
                        gender = stoi(clearStr(part));
                    }
                    catch (const std::exception&e)
                    {   
                        std::cerr << e.what() << std::endl;
                        gender = true;
                    }
                    break;
                case 4:
                    species_id = clearStr(part);
                    break;
                case 5:
                    status = clearStr(part);
                    break;
                case 6:
                    owner_id = clearStr(part);
                    break;
                case 7:
                    service_used = clearStr(part);
                    break;
                case 8:
                    try {
                        details.setHeight(stod(clearStr(part)));
                    }
                    catch (const std::exception&e)
                    {   
                        std::cerr << e.what() << std::endl;
                        details.setHeight(-1);
                    }
                case 9:
                    try {
                        details.setWeight(stod(clearStr(part)));
                    }
                    catch (const std::exception&e)
                    {   
                        std::cerr << e.what() << std::endl;
                        details.setWeight(-1);
                    }
                    break;
                case 10:
                    details.setTemperament(clearStr(part));
                    break;
                case 11:
                    try {
                        details.setIntelligence(stoi(clearStr(part)));
                    }
                    catch (const std::exception&e)
                    {   
                        std::cerr << e.what() << std::endl;
                        details.setIntelligence(-1);
                    }
                    break;
                default:
                    break;
            }
        part.clear();
        ++count;
        }
    }
    details.setSNeeds(clearStr(part));
}

std::string CustomerPet::writeLine() {
    return id + "\t" + 
        name + "\t" + 
        std::to_string(age) + "\t" + 
        std::to_string(gender) + "\t" + 
        species_id + "\t" + 
        status + "\t" + 
        owner_id + "\t" + 
        service_used + "\t" + 
        std::to_string(details.getHeight()) + "\t" + 
        std::to_string(details.getWeight()) + "\t" + 
        details.getTemperament() + "\t" + 
        std::to_string(details.getIntelligence()) + "\t" + 
        details.getSNeeds() + "\n";
}

extern LinkedList<CustomerPet> CPetsList;

void CustomerPet::setNextID() {
    Node<CustomerPet>*temp = CPetsList.end();
    std::string lastID = temp->data.getID();
    if (lastID.empty()) {
        id = "cp1";
    }
    size_t lastDP = lastID.find_first_of("0123456789");
    if (lastDP == std::string::npos) {
        id = "cp1";
    }
    else {
        std::string p = lastID.substr(0, lastDP);
        std::string s = lastID.substr(lastDP);
        int is = stoi(s);
        id = p + std::to_string(is+1);
    }
}
