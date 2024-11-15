#ifndef SPET_H
#define SPET_H
#include "./Pet.h"
#include <iostream>
class ShopPet : public Pet
{
private:
    int price; // vnd
    std::string history;
    bool sold;

public:
    ShopPet(std::string pid = "SP1", std::string sid = "S0");

    int getPrice() const;
    std::string getHistory() const;
    void setPrice(int);
    void setHistory(const std::string &);
    bool hadSold() const;
    void setSold(bool);

    void readLine(const std::string &);
    std::string writeLine();
    void showDetails(int except = -1);
    void editInfo();
    void editChar();
    void setPet();
    void setNextID();
};

#endif // !SPET_H