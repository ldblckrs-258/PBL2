#ifndef INVOICE_H
#define INVOICE_H

#include <iostream>
#include "../mylib/LinkedList.cpp"
#include "../mylib/Cursor.h"
#include "../mylib/FuncLib.h"

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
    Invoice(std::string id = "I1");
    void SaveInvoice();
    void ReadInvoice();
    void PrintInvoice();
    void GetTotal();
};
#endif // INVOICE