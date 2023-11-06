#include <iostream>
#include "./mylib/FuncLib.h"
#include "./pet/CustomerPet.h"
#include "./pet/ShopPet.h"
#include "./pet/Species.h"


void PSMenu(){
    int choice;
    CustomerPet CP;
    ShopPet SP;
    do {
        system("cls");
        printFile(".\\source\\EPS.txt");
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                CP.newPet();
                break;
            case 2:
                CP.existPet();
                // Needs expansion, including Shop pet.
                break;
            case 3:
                ViewAllCP();
                break;
            case 4:
                ViewAllSpc();
                break;        
            default:
                return;
        }
    } while (1);
}