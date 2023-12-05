#include "./ServiceBranch.h"
#include <fstream>
#include <limits>

void getServiceList()
{
    std::ifstream SFile(getFolder() + "database\\others\\Service.txt");
    if (!SFile.is_open())
    {
        std::cerr << "Cannot open service data file" << std::endl;
        return;
    }

    std::string line;
    SFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(SFile, line))
    {
        if (!line.empty() && line.length() > 5)
        {
            Service snew;
            snew.readLine(line);
            ServiceList.push_back(snew);
        }
    }
    SFile.close();
}
void saveServiceList()
{
    std::ofstream dataFile(getFolder() + "database\\others\\Service.txt");
    if (!dataFile.is_open())
    {
        std::cerr << "Cannot open service data file" << std::endl;
        return;
    }
    dataFile << "ID\tService Name\tPrice\n";
    for (int i = 0; i < ServiceList.getSize(); ++i)
    {
        std::string line;
        line = ServiceList[i].writeLine();
        dataFile << line;
    }
    dataFile.close();
}
void ViewAllServices()
{
    system("cls");
    LinkedList<std::string> sample = getSample("ServiceSample.txt");
    setColor(3);
    std::cout << sample[0];
    setColor(7);
    Node<Service> *temp = ServiceList.begin();
    while (temp)
    {
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        moveCursor(17, -2);
        printCenter(temp->data.getID(), 10);
        moveInLine(30);
        printCenter(temp->data.getName(), 42);
        moveInLine(75);
        printCenter(commaInt(temp->data.getPrice()) + " vnd", 28);
        moveLine(2);
        temp = temp->next;
    }
    moveLine(-1);
    setColor(3);
    std::cout << sample[2] << std::endl;
    setColor(7);
    holdString("");
}
void CreateNewService()
{
    Service S;
    S.setNextID();
    S.editInfo();
    ServiceList.push_back(S);
    saveServiceList();
}

void OpenExistService(bool manager)
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

    int index = ServiceList.search(inputID, &Service::getID);
    if (index == -1)
    {
        holdString("ID does not exist, please re-enter or create new one!");
        return;
    }

    if (!manager)
    {
        ServiceList[index].showDetails();
        holdString("");
        return;
    }

    ServiceList[index].editInfo();
    ServiceList[index].showDetails();
    setColor(4);
    std::cout << "PRESS BACKSCAPE TO REMOVE THIS SERVICE, OTHERS NUMBER TO REFUSE" << std::endl;
    setColor(7);
    int choice = pickMenu();
    if (choice == -99)
    {
        ServiceList.remove(index);
        holdString("Deleting ...", 0.5);
    }
    saveServiceList();
    return;
}

std::string getServiceName(const std::string &id)
{
    int index = ServiceList.search(id, &Service::getID);
    if (index >= 0)
        return ServiceList[index].getName();
    else
        return " Service ID Undefined";
}

int getServicePrice(const std::string &id)
{
    int index = ServiceList.search(id, &Service::getID);
    if (index >= 0)
        return ServiceList[index].getPrice();
    else
        return 0;
}