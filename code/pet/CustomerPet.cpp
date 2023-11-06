#include "./CustomerPet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

CustomerPet::CustomerPet(std::string pid, std::string sid, std::string oid) : Pet(pid, sid), owner_id(oid), service_used(sid) {}

void CustomerPet::setPet(){
    int choice;
    do {
        showDetails();  
        std::cout << std::endl << std::endl;
        printFile(getFolder() + "source\\PetOption.txt");
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
            getline(std::cin, name);  
            gotoXY(0,21);
            break;
        case 2:
            showDetails(2);
            std::cout << ">> Enter age (an integer)";
            gotoXY(34,7);  
            std::cin >> age;  clearCin();  
            gotoXY(0,21);
            break;
        case 3:
            showDetails(3);
            std::cout << ">> Enter gender (1 for male, 0 for female)";
            gotoXY(34,9);  
            std::cin >> gender;  clearCin();
            gotoXY(0,21);
            break;
        case 4:
            showDetails(4);
            std::cout << ">> Enter species id";
            gotoXY(34,11);  
            getline(std::cin, species_id);   
            gotoXY(0,21);
            break;
        case 5:
            showDetails(5);
            std::cout << ">> Enter current status";
            gotoXY(34,13);  
            getline(std::cin, status);   
            gotoXY(0,21);
            break;
        case 6:
            showDetails(6);
            std::cout << ">> Enter owner id";
            gotoXY(34,15);                  
            getline(std::cin, owner_id);   
            gotoXY(0,21);
            break;
        case 7:
            showDetails(7);
            std::cout << ">> Enter service used id";
            gotoXY(34,17);  
            getline(std::cin, service_used);   
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
    if (except != 6) {gotoXY(34,15);   std::cout << owner_id;}
    if (except != 7) {gotoXY(34,17);   std::cout << service_used;}
    gotoXY(0,21);
}

void CustomerPet::loadFull() {
    Pet::loadFull();
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
    saveInfo();
    file << owner_id << std::endl << service_used << std::endl;
    saveChar();
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

void CustomerPet::existPet(){            
    system("cls");
    printFile(getFolder() + "source\\InputID.txt");
    gotoXY(67,3);
    std::cin >> id;
    moveLine(2);
    bool exist = false;
    std::string fileName = getFolder() + "database\\pet\\allCPets.txt";
    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line)) 
        if (line == id){
            exist = true;
            break;
        }
    fileIn.close();
    if (exist){
        loadFull();
        setPet();
    }
    else holdString("ID does not exist, please re-enter or create a new profile!");

}

void CustomerPet::resetData(){
    CustomerPet Temp;
    *this = Temp;
}
void ViewAllCP() {
    system("cls");
    printFile(getFolder() + "source\\AllCPSample1.txt");
    std::string allCP = getFolder() + "database\\pet\\allCPets.txt";
    std::ifstream allCPFile(allCP);
    if(!allCPFile.is_open()){
        std::cerr << "Error opening " << allCP << std::endl;
        return;
    }

    std::vector<std::string> sID;
    std::string line;
    while (allCPFile >> line) {
        sID.push_back(line);
    }
    allCPFile.close();

    for (const std::string &aID : sID) {
        std::string aCP = getFolder() + "database\\pet\\customerPet\\" + aID + ".txt";
        std::ifstream aCPFile(aCP);

        if (!aCPFile.is_open()) {
            continue;
        }
        printFile(getFolder() + "source\\AllCPSample2.txt");
        std::string aline;
        int lineCount = 0;
        while (getline(aCPFile, aline)) {
            switch (lineCount)
            {
            case 0:
                moveCursor(8,-2);   std::cout << aline;   moveLine(2);
                break;
            case 1:
                moveCursor(21,-2);   std::cout << aline;   moveLine(2);
                break;
            case 4:
                moveCursor(47,-2);   std::cout << aline;   moveLine(2);
                break;
            case 5:
                moveCursor(118,-2);   std::cout << aline;   moveLine(2);
                break;
            case 6:
                moveCursor(82,-2);   std::cout << aline;   moveLine(2);
                break;
            default:
                break;
            }
            ++lineCount;
        }
        aCPFile.close();
    }
    moveLine(-1);
    printFile(getFolder() + "source\\AllCPSample3.txt");
    holdString("");
}