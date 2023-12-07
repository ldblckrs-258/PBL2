#include "./Service.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include "../branch/PetBranch.h"

Service::Service(const std::string &id, const std::string &n, const int &pr)
    : ID(id), Name(n), Price(pr)
{
}

std::string Service::getID() const
{
    return ID;
}
std::string Service::getName() const
{
    return Name;
}
int Service::getPrice() const
{
    return Price;
}

void Service::readLine(const std::string &str)
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
                Name = clearStr(part);
                break;
            default:
                break;
            }
            part.clear();
            ++count;
        }
    }
    try
    {
        Price = stoi(clearStr(part));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        Price = -1;
    }
}

std::string Service::writeLine()
{
    return ID + "\t" +
           Name + "\t" +
           std::to_string(Price) + "\n";
}

void Service::showDetails(int except)
{
    system("cls");
    setColor(3);
    std::cout << "              ++============+============================================+==============================++" << std::endl;
    std::cout << "              ||   0. ID    |              1. Service Name               |           2. Price           ||" << std::endl;
    std::cout << "              |+------------+--------------------------------------------+------------------------------+|" << std::endl;
    std::cout << "              ||            |                                            |                              ||" << std::endl;
    std::cout << "              ++============+============================================+==============================++" << std::endl;
    setColor(7);
    if (except != 0)
    {
        gotoXY(17, 3);
        printCenter(ID, 10);
    }
    if (except != 1)
    {
        gotoXY(30, 3);
        printCenter(Name, 42);
    }
    if (except != 2)
    {
        gotoXY(75, 3);
        printCenter(commaInt(Price) + " vnd", 28);
    }
    moveLine(2);
}

void Service::editInfo()
{
    int c, i2;
    std::string i;
    do
    {
        showDetails();
        std::cout << std::endl
                  << ">> Press a number 1-2 to edit, others to escape: ";
        c = pickMenu();
        switch (c)
        {
        // case 0:
        //     showDetails(0);
        //     std::cout << "Enter service ID";
        //     gotoXY(17, 3);
        //     i = safeInput(10, false);
        //     ID = (i.empty() ? ID : i);
        //     gotoXY(0, 6);
        //     break;
        case 1:
            showDetails(1);
            std::cout << "Enter service name";
            gotoXY(30, 3);
            i = safeInput(42, false);
            Name = (i.empty() ? Name : i);
            gotoXY(0, 6);
            break;
        case 2:
            showDetails(2);
            std::cout << "Enter service price";
            gotoXY(75, 3);
            i2 = Price;
            try
            {
                Price = stoi(safeInput(28, false));
            }
            catch (const std::exception &e)
            {
                Price = i2;
            }
            gotoXY(0, 6);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        }
    } while (c != 0);
}

extern LinkedList<Service> ServiceList;
void Service::setNextID()
{
    Node<Service> *temp = ServiceList.end();
    std::string lastID = temp->data.getID();
    if (lastID.empty())
    {
        ID = "S1";
    }
    size_t lastDP = lastID.find_first_of("0123456789");
    if (lastDP == std::string::npos)
    {
        ID = "S1";
    }
    else
    {
        std::string p = lastID.substr(0, lastDP);
        std::string s = lastID.substr(lastDP);
        int is = stoi(s);
        ID = p + std::to_string(is + 1);
    }
}