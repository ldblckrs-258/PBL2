#include "./CustomerPet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

CustomerPet::CustomerPet(std::string pid, std::string sid, std::string oid) : Pet(pid, sid), owner_id(oid), service_used(sid) {}

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
    saveFull();
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

void CustomerPet::loadFull() {
    Pet::loadFull("customerPet");
    std::string fileName = getFolder() + "database\\pet\\customerPet\\" + id + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::in );
    if (!file.is_open()) {
        std::cerr << "Error opening file to load pet information." << fileName<< std::endl;
        return;
    }
    std::string line;
    int lineCount = 0;
    while (getline(file, line)) {
        switch (lineCount)
        {
        case 6:
            owner_id = line;
            break;
        case 7:
            service_used = line;
            break;
        default:
            break;
        }
        ++lineCount;
    }
    file.close();
}

void CustomerPet::saveFull() {
    std::string fileName = getFolder() + "database\\pet\\customerPet\\" + id + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error opening file to save pet information." << std::endl;
        return;
    }
    saveInfo("customerPet");
    file << owner_id << std::endl << service_used << std::endl;
    saveChar("customerPet");
    saveToAll();
}

void CustomerPet::saveToAll() {
    std::string fileName = getFolder() + "database\\pet\\allCPets.txt";

    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line)) 
        if (line == id) return;
    fileIn.close();

    std::ofstream fileOut(fileName, std::ios::app);
    if (!fileOut.is_open()) {
        std::cerr << "Error opening file to save Customer Pet ID.\n";
        return;
    }

    fileOut << id << std::endl;
    fileOut.close();            
}

void CustomerPet::setNextID() {
    std::string fileName = getFolder() + "database\\pet\\allCPets.txt";
    std::string lastID;

    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line)) {
        if (!line.empty())
            lastID = line;
    }
    fileIn.close();
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

void CustomerPet::newPet(){
    resetData();
    setNextID();
    setPet();
    saveFull();
}

void CustomerPet::resetData(){
    CustomerPet Temp;
    *this = Temp;
}
