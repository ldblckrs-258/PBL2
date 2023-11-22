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
    std::string getID() const;
    std::string getName() const;
    std::string getSpcID() const;
    std::string getGender() const;
};


#endif // !PET_H