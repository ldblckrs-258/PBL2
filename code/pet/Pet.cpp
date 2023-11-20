#include "./Pet.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

Pet::Pet(std::string pid, std::string sid) 
    : id(pid), name(UDF), gender(true), species_id(sid), age(0), status(UDF) {}

std::string Pet::getID() const {
    return id;
}

std::string Pet::getName() const{
    return name;
}

std::string Pet::getSpcID() const{
    return species_id;
}

std::string Pet::getGender() const {
    if (gender) return "male";
        else return "female";
}

void Pet::showDetails(int except){
    system("cls");
    printFile(getFolder() + "source\\PetInfo.txt");
    if (except != 0)    {gotoXY(34,3);   std::cout << id;}
    if (except != 1)    {gotoXY(34,5);   std::cout << name;}
    if (except != 2)    {gotoXY(34,7);   std::cout << age << " months";}
    if (except != 3)    {gotoXY(34,9);   std::cout << getGender();}
    if (except != 4)    {gotoXY(34,11);   std::cout << species_id;}
    if (except != 5)    {gotoXY(34,13);   std::cout << status;}

    if (except != 11)    {gotoXY(103,6);   std::cout << details.getHeight() << " m";}
    if (except != 12)    {gotoXY(103,8);   std::cout << details.getWeight() << " kg";}
    if (except != 13)    {gotoXY(103,10);   std::cout << details.getTemperament() ;}
    if (except != 14)    {gotoXY(103,12);   std::cout << details.getIntelligence() << "/10";}
    if (except != 15)    {gotoXY(103,14);   std::cout << details.getSNeeds();}

    gotoXY(0,21);
}

void Pet::editChar() {
    int c;
    showDetails();
    std::cout << ">> Press a number 1-5 to edit, others to escape: ";
    c = pickMenu();
    double i1; 
    std::string i2;
    do {
        switch (c) {
        case 1:
            showDetails(11);
            std::cout << ">> Enter height (a positive decimal)";
            gotoXY(103,6);  
            try {
                i1 = stod(safeInput(10, false));
            }
            catch(const std::exception& e){
                i1 = 0;
            }
            gotoXY(0,21);
            details.setHeight(i1);
            break;
        case 2:
            showDetails(12);
            std::cout << ">> Enter weight (a positive decimal)";
            gotoXY(103,8);  
            try {
                i1 = stod(safeInput(10, false));
            }
            catch(const std::exception& e){
                i1 = 0;
            } 
            gotoXY(0,21);
            details.setWeight(i1);
            break;
        case 3:
            showDetails(13);
            std::cout << ">> Enter temperament";
            gotoXY(103,10);  
            i2 = safeInput(36, false);
            gotoXY(0,21);
            details.setTemperament(i2);
            break;
        case 4:
            showDetails(14);
            std::cout << ">> Enter intelligence level (an integer from 0 to 10)";
            gotoXY(103,12);  
            try {
                i1 = stoi(safeInput(2, false));
            }
            catch(const std::exception& e){
                i1 = 0;
            } 
            gotoXY(0,21);
            details.setIntelligence(int(i1));
            break;
        case 5:
            showDetails(15);
            std::cout << ">> Enter special needs";
            gotoXY(103,14);  
            i2 = safeInput(36, false);
            gotoXY(0,21);
            details.setSNeeds(i2);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        };
        drawLine(' ', 100); moveCursor(-100,0);
        std::cout << "Edit other (0 to escape): ";
        std::cin.clear();
        c = pickMenu();
    } while (c != 0);
}
