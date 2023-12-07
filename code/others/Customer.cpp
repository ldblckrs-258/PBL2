#include "./Customer.h"
#include <sstream>
#include "../branch/PetBranch.h"

Customer::Customer(std::string id) : ID(id), Name("Undefined"), Contact("Undefined") {}

std::string Customer::getID() const
{
    return ID;
}
std::string Customer::getName() const
{
    return Name;
}
std::string Customer::getContact() const
{
    return Contact;
}

extern LinkedList<Customer> CustomerList;
void Customer::SetNextID()
{
    Node<Customer> *temp = CustomerList.end();
    std::string lastID = temp->data.getID();
    if (lastID.empty())
    {
        ID = "C1";
    }
    size_t lastDP = lastID.find_first_of("0123456789");
    if (lastDP == std::string::npos)
    {
        ID = "C1";
    }
    else
    {
        std::string p = lastID.substr(0, lastDP);
        std::string s = lastID.substr(lastDP);
        int is = stoi(s);
        ID = p + std::to_string(is + 1);
    }
}

std::string Customer::writeLine()
{
    return ID + "\t" + Name + "\t" + Contact + "\n";
}

void Customer::readLine(const std::string &str)
{
    std::string part;
    int count = 0;
    for (char c : str)
    {
        if (c != '\t')
            part += c;
        else
        {
            std::stringstream ss("");
            std::string token;
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
    Contact = clearStr(part);
}

void Customer::ShowDetails(int except)
{
    system("cls");
    printFile(getFolder() + "source\\Customer.txt", 3);
    if (except != 0)
    {
        gotoXY(27, 3);
        printCenter(ID, 8);
    }
    if (except != 1)
    {
        gotoXY(38, 3);
        printCenter(Name, 42);
    }
    if (except != 2)
    {
        gotoXY(83, 3);
        printCenter(Contact, 28);
    }
    moveLine(3);
    if (except == -1)
        ViewAllCP(ID);
}

void Customer::EditInfo()
{
    int c, i2;
    std::string i;
    do
    {
        ShowDetails(0);
        std::cout << std::endl
                  << ">> Press a number 1-2 to edit, others to escape: ";
        c = pickMenu();
        switch (c)
        {
        // case 0:
        //     ShowDetails(0);
        //     std::cout << "Enter customer ID";
        //     gotoXY(17, 3);
        //     i = safeInput(8, false);
        //     ID = (i.empty() ? ID : i);
        //     gotoXY(0, 7);
        //     break;
        case 1:
            ShowDetails(1);
            std::cout << "Enter customer name";
            gotoXY(38, 3);
            i = safeInput(40, false);
            Name = (i.empty() ? Name : i);
            gotoXY(0, 7);
            break;
        case 2:
            ShowDetails(2);
            std::cout << "Enter customer contact";
            gotoXY(83, 3);
            i = safeInput(28, false);
            Contact = (i.empty() ? Contact : i);
            gotoXY(0, 7);
            break;
        default:
            std::cout << "Exit ..." << std::endl;
            return;
        }
    } while (c != 0);
}