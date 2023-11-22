#include "./Pet.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

Pet::Pet(std::string pid, std::string sid) 
    : id(pid), name(UDF), gender(true), species_id(sid), age(0), status(UDF) {}

std::string Pet::getID() const {
    return id;
}

std::string Pet::getName() const{
    return name;
}

std::string Pet::getSpcID() const{
    return species_id;
}

std::string Pet::getGender() const {
    if (gender) return "male";
        else return "female";
}
