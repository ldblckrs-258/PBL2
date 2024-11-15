#ifndef PET_BRANCH
#define PET_BRANCH

#include "../pet/CustomerPet.h"
#include "../pet/ShopPet.h"
#include "../pet/Species.h"
#include "../mylib/FuncLib.h"
#include "../branch/CustomerBranch.h"

extern LinkedList<CustomerPet> CPetsList;
void getCPList();
void saveCPList();
void ViewAllCP(std::string filter = "");
void CreateNewCPet();

extern LinkedList<ShopPet> SPetsList;
void getSPList();
void saveSPList();
void ViewAllSP();
void CreateNewSPet();

extern LinkedList<Species> SpeciesList;
void getSpeciesList();
void saveSpc();
void ViewAllSpc();
void SearchSpc(bool manager = false);
void CreateNewSpc();
void EditSpc();
std::string getSpcName(std::string id);

void OpenExistPet(bool manager = false);
std::string getShopPetName(const std::string &);
int getShopPetPrice(const std::string &);

void SoldPet(std::string, std::string);
#endif