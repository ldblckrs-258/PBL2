#include "./branch/PetBranch.h"

void PetsMenu(bool manager = false){
    int choice;
    LinkedList<std::string> menuList;
    menuList.push_back("PETS MENU");
    menuList.push_back("1. Create new pet profile");
    menuList.push_back("2. Open existing pet profile");
    menuList.push_back("3. View all pets");
    if (manager) menuList.push_back("4. Create new shop pet profile");
    menuList.push_back("0. Exit");
    do {
        system("cls");
        printOptions(menuList, 3);
        choice = pickMenu();
        switch (choice){
            case 1:
                CreateNewCPet();
                break;
            case 2:
                OpenExistPet(manager);
                break;
            case 3:
                system("cls");
                ViewAllCP();
                ViewAllSP();
                holdString("");
                break;
            case 4:
                if (manager)    CreateNewSPet();
                else return;
                break;
            default:
                return;
        }
    } while (1);
}

void SpeciesMenu(bool manager = false){
        int choice;
    LinkedList<std::string> menuList;
    menuList.push_back("PETS MENU");
    menuList.push_back("1. Search species");
    menuList.push_back("2. View all species");
    if (manager) {
        menuList.push_back("3. Add new species");
        menuList.push_back("4. Edit species");
    }
    menuList.push_back("0. Exit");
    do {
        system("cls");
        printOptions(menuList, 3);
        choice = pickMenu();
        switch (choice){
            case 1:
                SearchSpc();
                break;
            case 2:
                ViewAllSpc();
                break;
            case 3:
                if (manager)    CreateNewSpc();
                else return;
                break;
                break;
            case 4:
                if (manager)    EditSpc();
                else return;
                break;
            default:
                return;
        }
    } while (1);
}

void PSMenu(bool manager =  false){
    int choice;
    CustomerPet CP;
    ShopPet SP;
    LinkedList<std::string> list;
    list.push_back("PETS & SPECIES MENU");
    list.push_back("1. Pets");
    list.push_back("2. Species");
    list.push_back("0. Exit");
    do {
        system("cls");
        printOptions(list, 3);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PetsMenu(manager);
                break;
            case 2:
                SpeciesMenu(manager);
                break;
            default:
                return;
        }
    } while (1);
}

