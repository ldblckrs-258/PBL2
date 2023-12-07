#ifndef INVOICE_BRANCH
#define INVOICE_BRANCH

#include "../others/Invoice.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include "./PetBranch.h"
#include "./ServiceBranch.h"
#include "./CustomerBranch.h"

void CreateInvoice();
void OpenExistInvoice();
void ViewAllInvoices();
#endif // !INVOICE_BRANCH