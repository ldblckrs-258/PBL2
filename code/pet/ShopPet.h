#ifndef SPET_H
#define SPET_H
#include "./Pet.h"
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

    void readLine(const std::string &) override;
    std::string writeLine() override;
    void showDetails(int except = -1) override;
    void editInfo() override;
    void editChar() override;
    void setPet() override;
    void setNextID() override;
};

#endif // !SPET_H