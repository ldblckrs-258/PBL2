#include "./CustomerBranch.h"
#include <fstream>
#include <limits>

void getCustomerList()
{
    std::ifstream SFile(getFolder() + "database\\others\\Customers.txt");
    if (!SFile.is_open())
    {
        std::cerr << "Cannot open customers data file" << std::endl;
        return;
    }

    std::string line;
    SFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(SFile, line))
    {
        if (!line.empty() && line.length() > 5)
        {
            Customer cnew;
            cnew.readLine(line);
            CustomerList.push_back(cnew);
        }
    }
    SFile.close();
}

void saveCustomerList()
{
    std::ofstream dataFile(getFolder() + "database\\others\\Customers.txt");
    if (!dataFile.is_open())
    {
        std::cerr << "Cannot open customers data file" << std::endl;
        return;
    }
    dataFile << "ID\tCustomer Name\tContact\n";
    for (int i = 0; i < CustomerList.getSize(); ++i)
    {
        std::string line;
        line = CustomerList[i].writeLine();
        dataFile << line;
    }
    dataFile.close();
}

void ViewAllCustomers()
{
    system("cls");
    LinkedList<std::string> sample = getSample("AllCustomerSample.txt");
    setColor(3);
    std::cout << sample[0];
    setColor(7);
    Node<Customer> *temp = CustomerList.begin();
    while (temp)
    {
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        moveCursor(37, -2);
        printCenter(temp->data.getID(), 8);
        moveInLine(48);
        printCenter(temp->data.getName(), 42);
        moveInLine(93);
        printCenter(temp->data.getContact(), 28);
        moveLine(2);
        temp = temp->next;
    }
    moveLine(-1);
    setColor(3);
    std::cout << sample[2] << std::endl;
    setColor(7);
    holdString("");
}

void CreateNewCustomer()
{
    Customer NC;
    NC.SetNextID();
    NC.EditInfo();
    CustomerList.push_back(NC);
    saveCustomerList();
}

void OpenExistCustomer()
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

    int index = CustomerList.search(inputID, &Customer::getID);
    if (index >= 0)
    {
        CustomerList[index].EditInfo();
        system("cls");
        CustomerList[index].ShowDetails();
        setColor(4);
        std::cout << "PRESS BACKSCAPE TO REMOVE THIS CUSTOMER PROFILE, OTHERS NUMBER TO REFUSE" << std::endl;
        setColor(7);
        int choice = pickMenu();
        if (choice == -99)
        {
            CustomerList.remove(index);
            holdString("Deleting ...", 0.5);
        }
        saveCustomerList();
        return;
    }
    holdString("ID does not exist, please re-enter or create new one!");
    return;
}

std::string getCustomerName(const std::string &id)
{
    int index = CustomerList.search(id, &Customer::getID);
    if (index >= 0)
        return CustomerList[index].getName();
    else
        return "Customer ID undefined";
}