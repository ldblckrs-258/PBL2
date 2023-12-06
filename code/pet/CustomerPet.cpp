#include "./CustomerPet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include "../branch/PetBranch.h"
#include "../branch/ServiceBranch.h"

CustomerPet::CustomerPet(std::string pid, std::string sid, std::string oid) : Pet(pid, sid), owner_id(oid), service_used(sid) {}

CustomerPet::CustomerPet(const ShopPet &other) : Pet(other)
{
    service_used = "S0";
    setNextID();
}
std::string CustomerPet::getOwnerID() const
{
    return owner_id;
}

std::string CustomerPet::getStatus() const
{
    return status;
}

void CustomerPet::setOwnerID(std::string oid)
{
    owner_id = oid;
}

void CustomerPet::showDetails(int except)
{
    system("cls");
    printFile(getFolder() + "source\\PetInfo.txt", 3);
    setColor(3);
    gotoXY(15, 15);
    std::cout << "6. Owner";
    gotoXY(15, 17);
    std::cout << "7. Service Used";
    setColor(7);

    if (except != 0)
    {
        gotoXY(34, 3);
        std::cout << id;
    }
    if (except != 1)
    {
        gotoXY(34, 5);
        std::cout << name;
    }
    if (except != 2)
    {
        gotoXY(34, 7);
        std::cout << age << " months";
    }
    if (except != 3)
    {
        gotoXY(34, 9);
        std::cout << getGender();
    }
    if (except != 4)
    {
        gotoXY(34, 11);
        std::cout << species_id << " - " << getSpcName(species_id);
    }
    if (except != 5)
    {
        gotoXY(34, 13);
        std::cout << status;
    }
    if (except != 6)
    {
        gotoXY(34, 15);
        std::cout << owner_id;
    }
    if (except != 7)
    {
        gotoXY(34, 17);
        std::cout << service_used << " - " << getServiceName(service_used);
    }
    if (except != 11)
    {
        gotoXY(103, 6);
        std::cout << details.getHeight() << " m";
    }
    if (except != 12)
    {
        gotoXY(103, 8);
        std::cout << details.getWeight() << " kg";
    }
    if (except != 13)
    {
        gotoXY(103, 10);
        std::cout << details.getTemperament();
    }
    if (except != 14)
    {
        gotoXY(103, 12);
        std::cout << details.getIntelligence() << "/10";
    }
    if (except != 15)
    {
        gotoXY(103, 14);
        std::cout << details.getSNeeds();
    }
    gotoXY(0, 21);
}

void CustomerPet::editInfo()
{
    int c;
    int i1;
    std::string i2;
    do
    {
        showDetails();
        std::cout << ">> Press a number 1-7 to edit, 0 to escape: ";
        c = pickMenu();
        switch (c)
        {
        case 1:
            showDetails(1);
            std::cout << ">> Enter pet name";
            gotoXY(34, 5);
            i2 = safeInput(36, false);
            name = ((i2.empty()) ? name : i2);
            gotoXY(0, 21);
            break;
        case 2:
            showDetails(2);
            std::cout << ">> Enter age (an integer)";
            gotoXY(34, 7);
            i1 = age;
            try
            {
                age = stod(safeInput(10, false));
            }
            catch (const std::exception &e)
            {
                age = i1;
            }
            gotoXY(0, 21);
            break;
        case 3:
            showDetails(3);
            std::cout << ">> Enter gender (1 for male, 0 for female)";
            gotoXY(34, 9);
            i1 = gender;
            try
            {
                gender = stoi(safeInput(1, false));
            }
            catch (const std::exception &e)
            {
                gender = i1;
            }
            gotoXY(0, 21);
            break;
        case 4:
            showDetails(4);
            std::cout << ">> Enter species id";
            gotoXY(34, 11);
            i2 = safeInput(36, false);
            species_id = ((i2.empty()) ? species_id : i2);
            gotoXY(0, 21);
            break;
        case 5:
            showDetails(5);
            std::cout << ">> Enter current status";
            gotoXY(34, 13);
            i2 = safeInput(36, false);
            status = ((i2.empty()) ? status : i2);
            gotoXY(0, 21);
            break;
        case 6:
            showDetails(6);
            std::cout << ">> Enter owner id";
            gotoXY(34, 15);
            i2 = safeInput(36, false);
            owner_id = ((i2.empty()) ? owner_id : i2);
            gotoXY(0, 21);
            break;
        case 7:
            showDetails(7);
            std::cout << ">> Enter service used id";
            gotoXY(34, 17);
            i2 = safeInput(36, false);
            service_used = ((i2.empty()) ? service_used : i2);
            gotoXY(0, 21);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        };
    } while (c != 0);
}

void CustomerPet::editChar()
{
    int c;
    double i1;
    std::string i2;
    do
    {
        showDetails();
        std::cout << ">> Press a number 1-5 to edit, 0 to escape: ";
        c = pickMenu();
        switch (c)
        {
        case 1:
            showDetails(11);
            std::cout << ">> Enter height (a positive decimal)";
            gotoXY(103, 6);
            try
            {
                i1 = stod(safeInput(10, false));
            }
            catch (const std::exception &e)
            {
                i1 = details.getHeight();
            }
            gotoXY(0, 21);
            details.setHeight(i1);
            break;
        case 2:
            showDetails(12);
            std::cout << ">> Enter weight (a positive decimal)";
            gotoXY(103, 8);
            try
            {
                i1 = stod(safeInput(10, false));
            }
            catch (const std::exception &e)
            {
                i1 = details.getWeight();
            }
            gotoXY(0, 21);
            details.setWeight(i1);
            break;
        case 3:
            showDetails(13);
            std::cout << ">> Enter temperament";
            gotoXY(103, 10);
            i2 = safeInput(36, false);
            gotoXY(0, 21);
            details.setTemperament(i2);
            break;
        case 4:
            showDetails(14);
            std::cout << ">> Enter intelligence level (an integer from 0 to 10)";
            gotoXY(103, 12);
            try
            {
                i1 = stoi(safeInput(2, false));
            }
            catch (const std::exception &e)
            {
                i1 = details.getIntelligence();
            }
            gotoXY(0, 21);
            details.setIntelligence(int(i1));
            break;
        case 5:
            showDetails(15);
            std::cout << ">> Enter special needs";
            gotoXY(103, 14);
            i2 = safeInput(36, false);
            gotoXY(0, 21);
            details.setSNeeds(i2);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        };
    } while (c != 0);
}

void CustomerPet::setPet()
{
    int choice;
    LinkedList<std::string> list;
    list.push_back("PET OPTIONS");
    list.push_back("1. Edit information");
    list.push_back("2. Edit characteristic");
    list.push_back("0. Exit");

    do
    {
        showDetails();
        std::cout << std::endl
                  << std::endl;
        printOptions(list, 3);
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
    } while (choice);
}

void CustomerPet::readLine(const std::string &str)
{
    std::string part;
    int count = 0;
    for (char c : str)
    {
        if (c != '\t')
            part += c;
        else
        {
            switch (count)
            {
            case 0:
                id = clearStr(part);
                break;
            case 1:
                name = clearStr(part);
                break;
            case 2:
                try
                {
                    age = stoi(clearStr(part));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    age = -1;
                }
                break;
            case 3:
                try
                {
                    gender = stoi(clearStr(part));
                }
                catch (const std::exception &e)
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
                try
                {
                    details.setHeight(stod(clearStr(part)));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    details.setHeight(-1);
                }
            case 9:
                try
                {
                    details.setWeight(stod(clearStr(part)));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    details.setWeight(-1);
                }
                break;
            case 10:
                details.setTemperament(clearStr(part));
                break;
            case 11:
                try
                {
                    details.setIntelligence(stoi(clearStr(part)));
                }
                catch (const std::exception &e)
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

std::string CustomerPet::writeLine()
{
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

void CustomerPet::setNextID()
{
    Node<CustomerPet> *temp = CPetsList.end();
    std::string lastID = temp->data.getID();
    if (lastID.empty())
    {
        id = "CP1";
    }
    size_t lastDP = lastID.find_first_of("0123456789");
    if (lastDP == std::string::npos)
    {
        id = "CP1";
    }
    else
    {
        std::string p = lastID.substr(0, lastDP);
        std::string s = lastID.substr(lastDP);
        int is = stoi(s);
        id = p + std::to_string(is + 1);
    }
}
