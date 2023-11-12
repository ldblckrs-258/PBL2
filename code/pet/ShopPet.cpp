#include "./ShopPet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

ShopPet::ShopPet(std::string pid, std::string sid) : Pet(pid, sid), price(0), history(UDF) {}

int ShopPet::getPrice() const {
    return price;
}

std::string ShopPet::getHistory() const {
    return history; 
}

void ShopPet::setPrice(int newPrice) {
    price = newPrice; 
}

void ShopPet::setHistory(const std::string &newHistory){ 
    history = newHistory; 
}

void ShopPet::showDetails(int except){
    Pet::showDetails(except);
    gotoXY(15, 15); std::cout << "6. History";
    if (except != 6) {gotoXY(34,15);   std::cout << history;}
    gotoXY(15, 17); std::cout << "7. Price";
    if (except != 7) {gotoXY(34,17);   std::cout << price << " vnd";}
    gotoXY(0,21);
}

void ShopPet::saveToAll() {
    std::string fileName = getFolder() + "database\\pet\\allSPets.txt";

    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line)) 
        if (line == id) return;
    fileIn.close();

    std::ofstream fileOut(fileName, std::ios::app);
    if (!fileOut.is_open()) {
        std::cerr << "Error opening file to save Shop Pet ID.\n";
        return;
    }

    fileOut << id << std::endl;
    fileOut.close();            
}

void ShopPet::saveFull() {
    std::string fileName = getFolder() + "database\\pet\\shopPet\\" + id + ".txt";
    std::fstream file;
    file.open(fileName, std::ios::out | std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Error opening file to save pet information." << std::endl;
        return;
    }
    saveInfo("shopPet");
    file << history << std::endl << price << std::endl;
    saveChar("shopPet");
    saveToAll();
}

void ShopPet::editInfo() {
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
            std::cout << ">> Enter history";
            gotoXY(34,15);                  
            history = safeInput(36, false);
            gotoXY(0,21);
            break;
        case 7:
            showDetails(7);
            std::cout << ">> Enter price";
            gotoXY(34,15);                  
            try {
                price = stod(safeInput(36, false));
            }
            catch(const std::exception& e){
                price = 0;
            }
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

void ShopPet::setPet(){
    int choice;
    std::vector<std::string> list;
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

void ShopPet::loadFull() {
    Pet::loadFull("shopPet");
    std::string fileName = getFolder() + "database\\pet\\shopPet\\" + id + ".txt";
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
            history = line;
            break;
        case 7:
            try{
                price = stoi(line);
            } catch(const std::exception& e){
                std::cerr << "The file containing pet information is corrupted" << '\n';
                return;
            }
            break;
        default:
            break;
        }
        ++lineCount;
    }
    file.close();
}

void ShopPet::setNextID() {
    std::string fileName = getFolder() + "database\\pet\\allSPets.txt";
    std::string lastID;

    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line)) {
        if (!line.empty())
            lastID = line;
    }
    fileIn.close();
    if (lastID.empty()) {
        id = "sp1";
    }
    size_t lastDP = lastID.find_first_of("0123456789");
    if (lastDP == std::string::npos) {
        id = "sp1";
    }
    else {
        std::string p = lastID.substr(0, lastDP);
        std::string s = lastID.substr(lastDP);
        int is = stoi(s);
        id = p + std::to_string(is+1);
    }
}

void ShopPet::resetData(){
    ShopPet Temp;
    *this = Temp;
}

void ShopPet::newPet(){
    resetData();
    setNextID();
    setPet();
    saveFull();
}

