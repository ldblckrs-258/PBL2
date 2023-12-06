#include "./Species.h"
#define UDF "undefined"

Species::Species()
{
    ID = "A0";
    breed = UDF;
    name = UDF;
    origin = UDF;
    lifespan = "0 years";
    traits = "none";
}

void Species::readLine(const std::string &str)
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
                breed = clearStr(part);
                break;
            case 2:
                name = clearStr(part);
                break;
            case 3:
                origin = clearStr(part);
                break;
            case 4:
                lifespan = clearStr(part);
                break;
            default:
                break;
            }
            part.clear();
            ++count;
        }
    }
    traits = clearStr(part);
}

std::string Species::getID() const
{
    return ID;
}
std::string Species::getBreed() const
{
    return breed;
}
std::string Species::getName() const
{
    return name;
}
std::string Species::getOrigin() const
{
    return origin;
}
std::string Species::getLifespan() const
{
    return lifespan;
}
std::string Species::getTraits() const
{
    return traits;
}

void Species::showDetails(int except)
{
    printFile(getFolder() + "source\\SpeciesTable.txt", 3);
    int xx, yy;
    getCursorPosition(xx, yy);
    if (except != 1)
    {
        moveCursor(7, -10);
        printCenter(ID, 8);
        gotoXY(xx, yy);
    }
    if (except != 2)
    {
        moveCursor(18, -10);
        printCenter(breed, 19);
        gotoXY(xx, yy);
    }
    if (except != 3)
    {
        moveCursor(40, -10);
        printCenter(name, 37);
        gotoXY(xx, yy);
    }
    if (except != 4)
    {
        moveCursor(80, -10);
        printCenter(origin, 24);
        gotoXY(xx, yy);
    }
    if (except != 5)
    {
        moveCursor(107, -10);
        printCenter(lifespan, 22);
        gotoXY(xx, yy);
    }
    if (except != 6)
    {
        moveCursor(8, -6);
        safeOutput(traits, 120, 5);
        gotoXY(xx, yy);
    }
}

void Species::editDetails()
{
    int c, xx, yy;
    system("cls");
    showDetails();
    getCursorPosition(xx, yy);
    std::cout << ">> Press a number 1-7 to edit, others to escape: ";
    c = pickMenu();
    std::string temp;
    do
    {
        switch (c)
        {
        case 1:
            system("cls");
            showDetails(1);
            std::cout << ">> Enter species ID";
            gotoXY(7, 5);
            temp = safeInput(8, false);
            ID = (temp.empty() ? ID : temp);
            gotoXY(xx, yy);
            break;
        case 2:
            system("cls");
            showDetails(2);
            std::cout << ">> Enter breed";
            gotoXY(18, 5);
            temp = safeInput(19, false);
            breed = (temp.empty() ? breed : temp);
            gotoXY(xx, yy);
            break;
        case 3:
            system("cls");
            showDetails(3);
            std::cout << ">> Enter species name";
            gotoXY(40, 5);
            temp = safeInput(37, false);
            name = (temp.empty() ? name : temp);
            gotoXY(xx, yy);
            break;
        case 4:
            system("cls");
            showDetails(4);
            std::cout << ">> Enter species origin";
            gotoXY(80, 5);
            temp = safeInput(24, false);
            origin = (temp.empty() ? origin : temp);
            gotoXY(xx, yy);
            break;
        case 5:
            system("cls");
            showDetails(5);
            std::cout << ">> Enter species average lifespan";
            gotoXY(107, 5);
            temp = safeInput(22, false);
            lifespan = (temp.empty() ? lifespan : temp);
            gotoXY(xx, yy);
            break;
        case 6:
            system("cls");
            showDetails(6);
            std::cout << ">> Enter species traits";
            gotoXY(8, 9);
            temp = boxInput(120, 5);
            traits = (temp.empty() ? traits : temp);
            gotoXY(xx, yy);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        };
        drawLine(' ', 120);
        moveCursor(-120, 0);
        std::cout << "Edit other (press 0 to escape): ";
        c = pickMenu();
    } while (c != 0);
}