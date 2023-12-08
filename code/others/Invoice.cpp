#include "./Invoice.h"
Invoice::Invoice() : Time(getCTime()), Customer_ID("C0"), Total(0)
{
    SetNextID();
}

Invoice::~Invoice()
{
    List.clear();
}

std::string Invoice::getID() const
{
    return ID;
}
std::string Invoice::getTime() const
{
    return Time;
}

std::string Invoice::getCustomerID() const
{
    return Customer_ID;
}

void Invoice::setID(std::string id)
{
    ID = id;
}

void Invoice::setCustomerID(std::string cid)
{
    Customer_ID = cid;
}

void Invoice::Invoice::SaveID()
{

    std::string fileName = getFolder() + "database\\invoices\\IDList.txt";
    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line))
        if (line == ID)
            return;
    fileIn.close();
    std::ofstream fileOut(fileName, std::ios::app);
    if (!fileOut.is_open())
    {
        std::cerr << "Error opening file to save invoice ID.\n";
        return;
    }
    fileOut << ID << std::endl;
    fileOut.close();
}

void Invoice::SetNextID()
{
    std::string fileName = getFolder() + "database\\invoices\\IDList.txt";
    std::string lastID;
    std::ifstream fileIn(fileName);
    std::string line;
    while (getline(fileIn, line))
    {
        if (!line.empty())
            lastID = line;
    }
    fileIn.close();
    if (lastID.empty())
        ID = "I1";
    size_t lastDP = lastID.find_first_of("0123456789");
    if (lastDP == std::string::npos)
        ID = "I1";
    else
    {
        std::string p = lastID.substr(0, lastDP);
        std::string s = lastID.substr(lastDP);
        int is = stoi(s);
        ID = p + std::to_string(is + 1);
    }
}

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
        File << temp->data.type << "|" << temp->data.node_id << "|" << temp->data.quantity << "\n";
        temp = temp->next;
    }
    File.close();
    SaveID();
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

    gotoXY(44, 3);
    std::cout << ID;
    moveInLine(62);
    std::cout << getCustomerName(Customer_ID);
    moveInLine(107);
    std::cout << Time;
    moveLine(4);

    Node<invoiceNode> *temp = List.begin();
    while (temp)
    {
        setColor(3);
        std::cout << sample[1];
        setColor(7);
        moveCursor(32, -2);
        printCenter(temp->data.node_id, 10);
        if (temp->data.type == 1)
        {
            moveInLine(45);
            printCenter(getShopPetName(temp->data.node_id), 42);
            moveInLine(101);
            printCenter(commaInt(getShopPetPrice(temp->data.node_id)) + " vnd", 29);
        }
        else if (temp->data.type == 2)
        {
            moveInLine(45);
            printCenter(getServiceName(temp->data.node_id), 42);
            moveInLine(101);
            printCenter(commaInt(getServicePrice(temp->data.node_id)) + " vnd", 29);
        }
        else
            continue;
        moveInLine(90);
        printCenter(std::to_string(temp->data.quantity), 8);
        moveLine(2);
        temp = temp->next;
    }
    setColor(3);
    std::cout << sample[2];
    setColor(7);
    moveCursor(101, -2);
    printCenter(commaInt(Total) + " vnd", 29);
    moveLine(2);
    holdString("");
}

void Invoice::GetTotal()
{
    Total = 0;
    Node<invoiceNode> *temp = List.begin();
    while (temp)
    {
        if (temp->data.type == 1)
            Total += (temp->data.quantity) * (getShopPetPrice(temp->data.node_id));
        else if (temp->data.type == 2)
            Total += (temp->data.quantity) * (getServicePrice(temp->data.node_id));
        temp = temp->next;
    }
    return;
}

void Invoice::PushNode(const invoiceNode &node)
{
    List.push_back(node);
}

void Invoice::RemoveSold()
{
    Node<invoiceNode> *temp = List.begin();
    while (temp)
    {
        if (temp->data.type == 1)
            SoldPet(temp->data.node_id, Customer_ID);
        temp = temp->next;
    }
    return;
}