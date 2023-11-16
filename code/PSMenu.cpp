#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "./mylib/FuncLib.h"
#include "./mylib/Cursor.h"
#include "./pet/CustomerPet.h"
#include "./pet/ShopPet.h"
#include "./pet/Species.h"

void existPet(bool manager = false){            
    system("cls");
    std::string inputID;
    printFile(getFolder() + "source\\InputID.txt");
    gotoXY(67,3);
    std::cin >> inputID;
    moveLine(2);

    bool exist = false;
    std::string fileName, head, type;
    head = inputID.substr(0,2);
    if (head == "cp")   type = "allCPets";
    else if (head == "sp")  type = "allSPets";
    else {
        holdString("ID does not exist, please re-enter or create a new profile!");
        return;
    }

    fileName =  getFolder() + "database\\pet\\" + type + ".txt";
    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line)) 
        if (line == inputID){
            exist = true;
            break;
        }
    fileIn.close();

    if (exist && (type == "allCPets")){
        CustomerPet CP(inputID);
        CP.loadFull();
        clearCin();
        CP.setPet();
    }
    else if (exist && (type == "allSPets")){
        ShopPet SP(inputID);
        SP.loadFull();
        clearCin();
        if (manager){
            SP.setPet();
        } else {
            SP.showDetails();
            holdString(" ");
        }
    }
    else holdString("ID does not exist, please re-enter or create a new profile!");
}

void ViewAllCP() {
    LinkedList<std::string> sample = getSample("AllCPSample.txt");
    std::cout << sample[0];

    std::string allCP = getFolder() + "database\\pet\\allCPets.txt";
    std::ifstream allCPFile(allCP);
    if(!allCPFile.is_open()){
        std::cerr << "Error opening: allCPets.txt" << allCP << std::endl;
        holdString("");
        return;
    }

    std::string line;
    LinkedList<std::string> sID;
    while (allCPFile >> line) {
        sID.push_back(line);
    }
    allCPFile.close();

    Node<std::string> *aID = sID.begin();
    while(aID) {
        std::ifstream aCPFile(getFolder() + "database\\pet\\customerPet\\" + aID->data + ".txt");

        if (!aCPFile.is_open()) {
            continue;
        }
        std::cout << sample[1] ;
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
        aID = aID->next;
    }
    moveLine(-1);
    std::cout << sample[2] << std::endl ;
}

void ViewAllSP() {
    LinkedList<std::string> sample = getSample("AllSPSample.txt");
    std::string line;

    std::cout << sample[0];
    std::string allSP = getFolder() + "database\\pet\\allSPets.txt";
    std::ifstream allSPFile(allSP);
    if(!allSPFile.is_open()){
        std::cerr << "Error opening: allSPets.txt " << allSP << std::endl;
        holdString("");
        return;
    }

    LinkedList<std::string> sID;
    while (allSPFile >> line) {
        sID.push_back(line);
    }
    allSPFile.close();

    Node<std::string> *aID = sID.begin();
    while(aID) {
        std::ifstream aSPFile(getFolder() + "database\\pet\\shopPet\\" + aID->data + ".txt");

        if (!aSPFile.is_open()) {
            continue;
        }
        std::cout << sample[1] ;
        std::string aline;
        int lineCount = 0;
        while (getline(aSPFile, aline)) {
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
            case 6:
                moveCursor(82,-2);   std::cout << aline;   moveLine(2);
                break;
            case 7:
                moveCursor(132,-2);
                std::cout << std::setw(15) << std::right << commaInt(aline) << " vnd";
                moveLine(2);
                break;
            default:
                break;
            }
            ++lineCount;
        }
        aSPFile.close();
        aID = aID->next;
    }
    moveLine(-1);
    std::cout << sample[2] << std::endl ;
}

void PSMenu(bool manager =  false){
    int choice;
    CustomerPet CP;
    ShopPet SP;
    LinkedList<std::string> list;
    list.push_back("PETS & SPECIES");
    list.push_back("1. Create new pet profile");
    list.push_back("2. Open existing pet profile");
    list.push_back("3. View all pets");
    list.push_back("4. View all species");
    if (manager) list.push_back("5. Create new shop pet profile");
    list.push_back("0. Exit");
    do {
        system("cls");
        printOptions(list);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                CP.newPet();
                break;
            case 2:
                existPet(manager);
                break;
            case 3:
                system("cls");
                ViewAllCP();
                ViewAllSP();
                holdString("");
                break;
            case 4:
                ViewAllSpc();
                break;
            case 5:
                if (manager)    SP.newPet();
                else return;
                break;
            default:
                return;
        }
    } while (1);
}

void ViewAllSpc(){
    LinkedList<Species> list;
    std::ifstream dataFile(getFolder() + "database\\pet\\species.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Cannot open species data file" << std::endl;
        return;
    }

    std::string line;
    dataFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(dataFile, line)){
        if (!line.empty() && line.length() > 50){
            Species snew;
            snew.readLine(line);
            list.push_back(snew);
        }
    }
    dataFile.close();

    system("cls");
    LinkedList<std::string> sample = getSample("AllSpcSample.txt");
    std::cout << sample[0];
    Node<Species>* temp = list.begin();
    while (temp) {
        std::cout << sample[1];
        moveCursor(7,-2);   std::cout << temp->data.getID();
        moveInLine(18); std::cout << temp->data.getBreed();
        moveInLine(34); std::cout << temp->data.getName();
        moveInLine(68); std::cout << temp->data.getOrigin();
        moveInLine(91); std::cout << temp->data.getLifespan();
        moveInLine(110); safeOutput(temp->data.getTraits(), 82);
        moveLine(2);
        temp = temp->next;
    }
    moveLine(-1);   std::cout << sample[2] << std::endl;
    system("pause");
}