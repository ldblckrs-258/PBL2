#include <iostream>
#include <fstream>
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
    system("cls");
    std::ifstream sfile(getFolder() + "source\\AllCPSample.txt");
    if (!sfile.is_open()) {
        std::cerr << "Can't open source file" << std::endl;
        holdString("");
        return;
    }
    std::string line;
    std::string s1, s2, s3;

    for (int i = 0; i < 5 && std::getline(sfile, line); ++i) {
        s1 += line + "\n";
    }
    for (int i = 0; i < 2 && std::getline(sfile, line); ++i) {
        s2 += line + "\n";
    }
    while (std::getline(sfile, line)) {
        s3 += line + "\n";
    }
    sfile.close();

    std::cout << s1;
    std::string allCP = getFolder() + "database\\pet\\allCPets.txt";
    std::ifstream allCPFile(allCP);
    if(!allCPFile.is_open()){
        std::cerr << "Error opening " << allCP << std::endl;
        holdString("");
        return;
    }

    std::vector<std::string> sID;
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
        std::cout << s2 ;
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
    std::cout << s3 ;
    holdString("");
}

void PSMenu(bool manager =  false){
    int choice;
    CustomerPet CP;
    ShopPet SP;
    std::vector<std::string> list;
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
                ViewAllCP();
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