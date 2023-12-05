#include "./Invoice.h"
#include <fstream>
#include <sstream>
#include "../branch/PetBranch.h"
#include "../branch/ServiceBranch.h"
Invoice::Invoice(std::string id) : ID(id), Time(getTime()), Customer_ID("C0"), Total(0) {}

void Invoice::SaveInvoice()
{
    std::ofstream File(getFolder() + "database\\invoices\\" + ID + ".txt");
    if (!File.is_open())
    {
        std::cerr << "Cannot open invoice file" << std::endl;
        return;
    }
    File << Time << "\n";
    File << Customer_ID << "\n";
    File << Total << "\n";

    Node<invoiceNode> *temp = List.begin();
    while (temp)
    {
        std::cout << temp->data.type << "|" << temp->data.node_id << "|" << temp->data.quantity << "\n";
        temp = temp->next;
    }
}

void Invoice::ReadInvoice()
{
    std::ifstream File(getFolder() + "database\\invoices\\" + ID + ".txt");
    if (!File.is_open())
    {
        std::cerr << "Cannot open invoice file" << std::endl;
        return;
    }

    std::getline(File, Time);
    std::getline(File, Customer_ID);
    File >> Total;
    File.ignore();
    std::string line;
    List.clear();
    while (std::getline(File, line))
    {
        invoiceNode node;
        int pos = line.find('|');
        try
        {
            node.type = stoi(line.substr(0, pos));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }

        node.node_id = line.substr(pos + 1, line.find('|', pos + 1) - pos - 1);

        try
        {
            node.quantity = stoi(line.substr(line.find('|', pos + 1) + 1));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }
        List.push_back(node);
    }
    File.close();
}

void Invoice::PrintInvoice()
{
    system("cls");
    LinkedList<std::string> sample = getSample("InvoiceSample.txt", true);
    setColor(3);
    std::cout << sample[0];
    setColor(7);

    gotoXY(24, 3);
    std::cout << ID;
    moveInLine(42);
    std::cout << Customer_ID;
    moveInLine(87);
    std::cout << Time;
    moveLine(4);

    Node<invoiceNode> *temp = List.begin();
    while (temp)
    {
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        moveCursor(12, -2);
        printCenter(temp->data.node_id, 10);
        if (temp->data.type == 1)
        {
            moveInLine(25);
            printCenter(getShopPetName(temp->data.node_id), 42);
            moveInLine(81);
            printCenter(commaInt(getShopPetPrice(temp->data.node_id)) + " vnd", 29);
        }
        else if (temp->data.type == 2)
        {
            moveInLine(25);
            printCenter(getServiceName(temp->data.node_id), 42);
            moveInLine(81);
            printCenter(commaInt(getServicePrice(temp->data.node_id)) + " vnd", 29);
        }
        else
            continue;
        moveInLine(70);
        printCenter(std::to_string(temp->data.quantity), 8);
        moveLine(2);
        temp = temp->next;
    }
    setColor(3);
    std::cout << sample[2];
    setColor(7);
    moveCursor(81, -2);
    printCenter(commaInt(Total) + " vnd", 29);
    moveLine(2);
    holdString("");
}

void Invoice::GetTotal()
{
    Node<invoiceNode> *temp = List.begin();
    while (temp)
    {
        if (temp->data.type == 1)
            Total += (temp->data.quantity) * (getShopPetPrice(temp->data.node_id));
        else if (temp->data.type == 2)
            Total += (temp->data.quantity) * (getServicePrice(temp->data.node_id));
    }
    return;
}