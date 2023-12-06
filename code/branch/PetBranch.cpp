
#include "./PetBranch.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "../mylib/Cursor.h"

// =============== CUSTOMER'S PETS  =============== //

void getCPList()
{
    std::ifstream CPFile(getFolder() + "database\\pet\\customerPets.txt");
    if (!CPFile.is_open())
    {
        std::cerr << "Cannot open customer's pets data file" << std::endl;
        return;
    }

    std::string line;
    CPFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(CPFile, line))
    {
        if (!line.empty() && line.length() > 10)
        {
            CustomerPet cnew;
            cnew.readLine(line);
            CPetsList.push_back(cnew);
        }
    }
    CPFile.close();
}

void saveCPList()
{
    std::ofstream dataFile(getFolder() + "database\\pet\\customerPets.txt");
    if (!dataFile.is_open())
    {
        std::cerr << "Cannot open customer's pets data file" << std::endl;
        return;
    }
    dataFile << "ID\tName\tAge\tGender\tSpecies ID\tStatus\tOwner ID\tService Used ID\tHeight\tWeight\tTemperament\tIntelligence\tSpecial Needs\n";
    for (int i = 0; i < CPetsList.getSize(); ++i)
    {
        std::string line;
        line = CPetsList[i].writeLine();
        dataFile << line;
    }
    dataFile.close();
}

void ViewAllCP(std::string filter)
{
    LinkedList<std::string> sample = getSample("AllCPSample.txt");
    setColor(3);
    std::cout << sample[0];
    setColor(7);
    Node<CustomerPet> *temp = CPetsList.begin();
    while (temp)
    {
        if (filter != "" && temp->data.getOwnerID() != filter)
        {
            temp = temp->next;
            continue;
        }
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        moveCursor(8, -2);
        std::cout << temp->data.getID();
        moveInLine(21);
        std::cout << temp->data.getName();
        moveInLine(47);
        std::cout << getSpcName(temp->data.getSpcID());
        moveInLine(82);
        std::cout << getCustomerName(temp->data.getOwnerID());
        moveInLine(118);
        std::cout << temp->data.getStatus();
        moveLine(2);
        temp = temp->next;
    }
    moveLine(-1);
    setColor(3);
    std::cout << sample[2] << std::endl;
    setColor(7);
}

void CreateNewCPet()
{
    CustomerPet CP;
    CP.setNextID();
    CP.setPet();
    CPetsList.push_back(CP);
    saveCPList();
}

// ================= SHOP'S PETS  ================= //

void getSPList()
{
    std::ifstream CPFile(getFolder() + "database\\pet\\shopPets.txt");
    if (!CPFile.is_open())
    {
        std::cerr << "Cannot open shop's pets data file" << std::endl;
        return;
    }

    std::string line;
    CPFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(CPFile, line))
    {
        if (!line.empty() && line.length() > 10)
        {
            ShopPet spnew;
            spnew.readLine(line);
            SPetsList.push_back(spnew);
        }
    }
    CPFile.close();
}

void saveSPList()
{
    std::ofstream dataFile(getFolder() + "database\\pet\\shopPets.txt");
    if (!dataFile.is_open())
    {
        std::cerr << "Cannot open shop's pets data file" << std::endl;
        return;
    }
    dataFile << "ID\tName\tAge\tGender\tSpecies ID\tStatus\tHistory\tPrice\tHeight\tWeight\tTemperament\tIntelligence\tSpecial Needs\tHad Sold ?\n";
    for (int i = 0; i < SPetsList.getSize(); ++i)
    {
        std::string line;
        line = SPetsList[i].writeLine();
        dataFile << line;
    }
    dataFile.close();
}

void ViewAllSP()
{
    LinkedList<std::string> sample = getSample("AllSPSample.txt");
    setColor(3);
    std::cout << sample[0];
    setColor(7);
    Node<ShopPet> *temp = SPetsList.begin();
    while (temp)
    {
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        if (temp->data.hadSold())
            setColor(4);
        moveCursor(8, -2);
        std::cout << temp->data.getID();
        moveInLine(21);
        std::cout << temp->data.getName();
        moveInLine(47);
        std::cout << getSpcName(temp->data.getSpcID());
        moveInLine(82);
        std::cout << temp->data.getHistory();
        moveInLine(132);
        std::cout << std::setw(15) << std::right << commaInt(temp->data.getPrice()) << " vnd";
        moveLine(2);
        setColor(7);
        temp = temp->next;
    }
    moveLine(-1);
    setColor(3);
    std::cout << sample[2] << std::endl;
    setColor(7);
}

void CreateNewSPet()
{
    ShopPet SP;
    SP.setNextID();
    SP.setPet();
    SPetsList.push_back(SP);
    saveSPList();
}

// =================== SPECIES  =================== //

void getSpeciesList()
{
    std::ifstream dataFile(getFolder() + "database\\pet\\species.txt");
    if (!dataFile.is_open())
    {
        std::cerr << "Cannot open species data file" << std::endl;
        return;
    }

    std::string line;
    dataFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(dataFile, line))
    {
        if (!line.empty() && line.length() > 50)
        {
            Species snew;
            snew.readLine(line);
            SpeciesList.push_back(snew);
        }
    }
    dataFile.close();
    return;
}

void saveSpc()
{
    std::ofstream dataFile(getFolder() + "database\\pet\\species.txt");
    if (!dataFile.is_open())
    {
        std::cerr << "Cannot open species data file" << std::endl;
        return;
    }
    dataFile << "ID\tBreed\tSpecies\tName\tOrigin\tAverage lifespan\tTraits\n";
    for (int i = 0; i < SpeciesList.getSize(); ++i)
    {
        std::string line;
        line = SpeciesList[i].getID() + "\t" + SpeciesList[i].getBreed() + "\t" + SpeciesList[i].getName() + "\t" + SpeciesList[i].getOrigin() + "\t" + SpeciesList[i].getLifespan() + "\t" + SpeciesList[i].getTraits() + "\n";
        dataFile << line;
    }
    dataFile.close();
}

void ViewAllSpc()
{

    system("cls");
    LinkedList<std::string> sample = getSample("AllSpcSample.txt");
    setColor(3);
    std::cout << sample[0];
    setColor(7);
    Node<Species> *temp = SpeciesList.begin();
    while (temp)
    {
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        moveCursor(7, -2);
        std::cout << temp->data.getID();
        moveInLine(18);
        std::cout << temp->data.getBreed();
        moveInLine(34);
        std::cout << temp->data.getName();
        moveInLine(68);
        std::cout << temp->data.getOrigin();
        moveInLine(91);
        std::cout << temp->data.getLifespan();
        moveInLine(110);
        safeOutput(temp->data.getTraits(), 41);
        moveLine(2);
        temp = temp->next;
    }
    moveLine(-1);
    setColor(3);
    std::cout << sample[2] << std::endl;
    setColor(7);
    system("pause");
}

void SearchSpc()
{
    system("cls");
    LinkedList<std::string> menulist;
    menulist.push_back("SEARCH SPECIES");
    menulist.push_back("1. Search by ID");
    menulist.push_back("2. Search by Name");
    menulist.push_back("0. Exit");
    int choice;
    do
    {
        system("cls");
        printOptions(menulist, 2);
        choice = pickMenu();
        int index;
        std::string value;
        moveLine(2);
        printFile(getFolder() + "source\\InputOne.txt");
        switch (choice)
        {
        case 1:
            moveCursor(71, -4);
            std::cout << "SEARCH BY ID" << std::endl;
            moveCursor(61, 1);
            std::cout << "ID" << std::endl;
            moveCursor(72, -1);
            value = safeInput(30, false);
            moveLine(2);
            index = SpeciesList.search(value, &Species::getID);
            break;
        case 2:
            moveCursor(70, -4);
            std::cout << "SEARCH BY NAME" << std::endl;
            moveCursor(56, 1);
            std::cout << "Species name" << std::endl;
            moveCursor(72, -1);
            value = safeInput(30, false);
            moveLine(2);
            index = SpeciesList.search(value, &Species::getName);
            break;
        default:
            return;
        }

        if (index != -1)
        {
            SpeciesList[index].showDetails();
        }
        else
        {
            std::cout << "Value not found!" << std::endl;
        }
        system("pause");
    } while (1);
}

void CreateNewSpc()
{
    Species newSpc;
    newSpc.editDetails();
    SpeciesList.push_back(newSpc);
    saveSpc();
    moveLine(1);
    holdString("Add new species successful !", 1);
}

void EditSpc()
{
    std::string iID;
    int sIndex;

    do
    {
        system("cls");
        printFile(getFolder() + "source\\InputOne.txt", 2);
        gotoXY(71, 1);
        std::cout << "ACCESS VIA ID";
        gotoXY(61, 3);
        std::cout << "ID";
        gotoXY(72, 3);
        iID = safeInput(10, false);
        moveLine(2);
        sIndex = SpeciesList.search(iID, &Species::getID);
        if (sIndex == -1)
        {
            std::cout << "Species not found, press 1 to re-enter, 0 to escape ";
            int choice = pickMenu();
            if (choice != 1)
                return;
        }
        else
            break;
    } while (1);

    SpeciesList[sIndex].editDetails();
    system("cls");
    SpeciesList[sIndex].showDetails();
    setColor(4);
    std::cout << "PRESS BACKSCAPE TO REMOVE THIS SPECIES, OTHERS NUMBER TO REFUSE" << std::endl;
    setColor(7);
    int choice = pickMenu();
    if (choice == -99)
    {
        SpeciesList.remove(sIndex);
        holdString("Deleting ...", 0.5);
    }
    saveSpc();
    holdString("");
}

std::string getSpcName(std::string id)
{
    int index = SpeciesList.search(id, &Species::getID);
    if (index == -1)
        return "Undefined";
    else
        return SpeciesList[index].getName();
}
// ===================== MENU  ===================== //

void OpenExistPet(bool manager)
{
    system("cls");
    std::string inputID;
    printFile(getFolder() + "source\\InputOne.txt", 2);
    gotoXY(72, 1);
    std::cout << "ACCESS VIA ID";
    gotoXY(60, 3);
    std::cout << "ID";
    gotoXY(72, 3);
    inputID = safeInput(20, false);
    moveLine(2);

    std::string head = toUpperCase(inputID.substr(0, 2));

    if (head == "CP")
    {
        int index = CPetsList.search(inputID, &CustomerPet::getID);
        if (index >= 0)
        {
            CPetsList[index].setPet();
            system("cls");
            CPetsList[index].showDetails();
            setColor(4);
            std::cout << "PRESS BACKSCAPE TO REMOVE THIS PET, OTHERS NUMBER TO REFUSE" << std::endl;
            setColor(7);
            int choice = pickMenu();
            if (choice == -99)
            {
                CPetsList.remove(index);
                holdString("Deleting ...", 0.5);
            }
            saveCPList();
            return;
        }
    }
    else if (head == "SP")
    {
        int index = SPetsList.search(inputID, &ShopPet::getID);
        if (index >= 0)
        {
            if (!manager)
            {
                SPetsList[index].showDetails();
                holdString("");
                return;
            }
            SPetsList[index].setPet();
            system("cls");
            SPetsList[index].showDetails();
            setColor(4);
            std::cout << "PRESS BACKSCAPE TO REMOVE THIS PET, OTHERS NUMBER TO REFUSE" << std::endl;
            setColor(7);
            int choice = pickMenu();
            if (choice == -99)
            {
                SPetsList.remove(index);
                holdString("Deleting ...", 0.5);
            }
            saveSPList();
            return;
        }
    }
    holdString("ID does not exist, please re-enter or create new one!");
    return;
}

std::string getShopPetName(const std::string &id)
{
    int index = SPetsList.search(id, &ShopPet::getID);
    if (index >= 0)
        return SPetsList[index].getName();
    else
        return "Shop Pet ID undefined";
}

int getShopPetPrice(const std::string &id)
{
    int index = SPetsList.search(id, &ShopPet::getID);
    if (index >= 0)
        return SPetsList[index].getPrice();
    else
        return 0;
}

void SoldPet(std::string shoppet_id, std::string customer_id)
{
    int index = SPetsList.search(shoppet_id, &ShopPet::getID);
    if (index < 0)
        return;
    CustomerPet NewCP = SPetsList[index];
    NewCP.setOwnerID(customer_id);
    SPetsList[index].setSold(true);
    CPetsList.push_back(NewCP);
    saveCPList();
    saveSPList();
}