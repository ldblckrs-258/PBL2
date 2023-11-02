#ifndef PET_H
#define PET_H

#include <iostream>
#include "./Crs.h"
class Pet {
protected:
    std::string id;
    std::string name;
    std::string species_id;
    std::string status;
    Crs details;
    int age; // months
    bool gender; // true ~ male, false ~ female

public:
    Pet(std::string pid = "p0", std::string sid = "s0");

    std::string getGender() const ;

    void showDetails(int except = -1);
    void editChar();
    void loadFull();
    void saveInfo();
    void saveChar();
};


#endif // !PET_H