#include "./InvoiceBranch.h"
#include "./PetBranch.h"
#include "./ServiceBranch.h"
#include <fstream>
void CreateInvoice()
{
    Invoice newI;
    std::string inputStr;

    system("cls");
    printFile(getFolder() + "source\\InputOne.txt", 2);
    gotoXY(69, 1);
    std::cout << "ENTER CUSTOMER ID";
    gotoXY(60, 3);
    std::cout << "ID";
    gotoXY(72, 3);
    std::cin >> inputStr;
    moveLine(2);
    newI.setCustomerID(toUpperCase(inputStr));

    int c;
    LinkedList<std::string> optionslist;
    optionslist.push_back("ADD TO INVOICE");
    optionslist.push_back("1. Buy a shop pet");
    optionslist.push_back("2. Using a service");
    optionslist.push_back("0. Exit");
    do
    {
        system("cls");
        printOptions(optionslist, 2);
        c = pickMenu();
        invoiceNode newN;
        if (c == 1)
        {
            newN.type = 1;
            newN.quantity = 1;
            do
            {
                system("cls");
                printFile(getFolder() + "source\\InputOne.txt", 2);
                gotoXY(69, 1);
                std::cout << "ENTER SHOP PET ID";
                gotoXY(60, 3);
                std::cout << "ID";
                gotoXY(72, 3);
                std::cin >> inputStr;
                moveLine(2);

                int index = SPetsList.search(inputStr, &ShopPet::getID);
                if (index == -1)
                {
                    std::cout << "Shop pet ID does not exist, press 1 to re-enter, 0 to exit";
                    c = pickMenu();
                    if (c != 1)
                        return;
                }
                else
                {
                    newN.node_id = toUpperCase(inputStr);
                    break;
                }
            } while (1);
        }
        else if (c == 2)
        {
            newN.type = 2;
            do
            {
                system("cls");
                printFile(getFolder() + "source\\InputOne.txt", 2);
                gotoXY(69, 1);
                std::cout << "ENTER SERVICE ID";
                gotoXY(60, 3);
                std::cout << "ID";
                gotoXY(72, 3);
                std::cin >> inputStr;
                moveLine(2);

                int index = ServiceList.search(inputStr, &Service::getID);
                if (index == -1)
                {
                    std::cout << "Service ID does not exist, press 1 to re-enter, 0 to exit";
                    c = pickMenu();
                    if (c != 1)
                        return;
                }
                else
                {
                    newN.node_id = toUpperCase(inputStr);
                    break;
                }
            } while (1);
            system("cls");
            printFile(getFolder() + "source\\InputOne.txt", 2);
            gotoXY(67, 1);
            std::cout << "ENTER SPECIES QUANTITY";
            gotoXY(60, 3);
            std::cout << "NUMBER";
            gotoXY(72, 3);
            std::cin >> newN.quantity;
            moveLine(2);
        }
        else
            break;
        newI.PushNode(newN);

    } while (1);
    newI.GetTotal();
    newI.SaveInvoice();
    newI.PrintInvoice();
    newI.RemoveSold();
}

void OpenExistInvoice()
{
    system("cls");
    std::string inputID;
    printFile(getFolder() + "source\\InputOne.txt", 2);
    gotoXY(72, 1);
    std::cout << "ACCESS VIA ID";
    gotoXY(60, 3);
    std::cout << "ID";
    gotoXY(72, 3);
    std::cin >> inputID;
    moveLine(2);

    std::string fileName = getFolder() + "database\\invoices\\IDList.txt";
    std::ifstream fileIn(fileName);
    std::string line;
    bool found = false;
    while (getline(fileIn, line))
    {
        if (line == inputID)
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        Invoice Exist;
        Exist.setID(inputID);
        Exist.ReadInvoice();
        Exist.PrintInvoice();
    }
    else
    {
        holdString("ID does not exist, please re-enter or create new one!");
    }
    return;
}