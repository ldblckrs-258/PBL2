#include "./ManagerAccount.h"
#include <iostream>
#include <fstream>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"

ManagerAccount::ManagerAccount() : Account()
{
    manager = true;
}

void ManagerAccount::readLine(const std::string &str)
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
                ID = clearStr(part);
                break;
            case 1:
                password = clearStr(part);
                break;
            case 2:
                try
                {
                    manager = stoi(clearStr(part));
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << std::endl;
                    manager = false;
                }
                break;
            case 3:
                details.setName(clearStr(part));
                break;
            case 4:
                details.setDoBirth(clearStr(part));
                break;
            case 5:
                details.setPosition(clearStr(part));
                break;
            default:
                break;
            }
            part.clear();
            ++count;
        }
    }
    details.setContact(clearStr(part));
}

std::string ManagerAccount::writeLine()
{
    return ID + "\t" +
           password + "\t" +
           std::to_string(manager) + "\t" +
           details.getName() + "\t" +
           details.getDoBirth() + "\t" +
           details.getPosition() + "\t" +
           details.getContact() + "\n";
}

void ManagerAccount::ShowInfo(int except)
{
    LinkedList<std::string> inputList;
    inputList.push_back("ACCOUNT INFORMATION");
    inputList.push_back("0. Account ID");
    inputList.push_back("1. Full Name");
    inputList.push_back("2. Date of birth");
    inputList.push_back("3. Position");
    inputList.push_back("4. Contact");
    system("cls");
    printInputBox(inputList, 2);
    if (except != 0)
    {
        gotoXY(70, 3);
        std::cout << ID;
    }
    if (except != 1)
    {
        gotoXY(70, 5);
        std::cout << details.getName();
    }
    if (except != 2)
    {
        gotoXY(70, 7);
        std::cout << details.getDoBirth();
    }
    if (except != 3)
    {
        gotoXY(70, 9);
        std::cout << details.getPosition();
    }
    if (except != 4)
    {
        gotoXY(70, 11);
        std::cout << details.getContact();
    }
    gotoXY(0, 15);
}

void ManagerAccount::UpdateInfo()
{
    int c;
    std::string temp;
    do
    {
        ShowInfo();
        std::cout << "Press number 1-4 to edit, 0 to escape: ";
        c = pickMenu();
        switch (c)
        {
        case 1:
            ShowInfo(1);
            std::cout << ">> Enter Name: ";
            gotoXY(70, 5);
            details.setName(safeInput(36, false));
            break;
        case 2:
            do
            {
                ShowInfo(2);
                if (!isValidDateFormat(temp))
                    std::cout << "Invalid format, example: 01/01/1970" << std::endl;
                std::cout << ">> Enter Date of birth (dd/mm/yyyy): ";
                gotoXY(70, 7);
                temp = safeInput(10, false);
                if (temp.empty())
                    temp = details.getDoBirth();
            } while (!isValidDateFormat(temp));
            details.setDoBirth(temp);
            break;
        case 3:
            ShowInfo(3);
            std::cout << ">> Enter Position: ";
            gotoXY(70, 9);
            details.setPosition(safeInput(36, false));
            break;
        case 4:
            ShowInfo(4);
            std::cout << ">> Contact: ";
            gotoXY(70, 11);
            details.setContact(safeInput(36, false));
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            system("cls");
            return;
        };
    } while (c != 0);
    system("cls");
}
