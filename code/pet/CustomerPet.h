#ifndef CPET_H
#define CPET_H
#include <iostream>
#include "./Pet.h"

class CustomerPet : public Pet
{
private:
    std::string owner_id;
    std::string service_used; // id

public:
    CustomerPet(std::string pid = "CP0", std::string sid = "S0", std::string oid = "C0");

    std::string getOwnerID() const;
    std::string getStatus() const;

    void showDetails(int except = -1);
    void editInfo();
    void editChar();
    void setPet();
    void readLine(const std::string &);
    std::string writeLine();
    void setNextID();
};

#endif // !CPET_H