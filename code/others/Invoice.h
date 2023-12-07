#ifndef INVOICE_H
#define INVOICE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "../branch/PetBranch.h"
#include "../branch/ServiceBranch.h"
#include "../branch/CustomerBranch.h"

class invoiceNode
{
public:
    int type; // 1. Buying pet, 2. Using service
    std::string node_id;
    int quantity;
};

class Invoice
{
private:
    std::string ID;
    std::string Time;
    std::string Customer_ID;
    LinkedList<invoiceNode> List;
    int Total;

public:
    Invoice();
    ~Invoice();
    std::string getCustomerID() const;
    std::string getID() const;
    std::string getTime() const;
    void setCustomerID(std::string);
    void setID(std::string);
    void SaveID();
    void SetNextID();
    void SaveInvoice();
    void ReadInvoice();
    void PrintInvoice();
    void GetTotal();
    void PushNode(const invoiceNode &node);
    void RemoveSold();
};
#endif // INVOICE