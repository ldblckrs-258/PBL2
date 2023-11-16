#include "./Species.h"
#include <iostream>
#include <string>
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#define UDF "undefined"


Species::Species(){
    ID = "S0";
    breed = UDF;
    name = UDF;
    origin = UDF;
    lifespan = "0 years";
    traits = "none";
}

void Species::readLine(const std::string &str){
    std::string part;
    int count = 0;
    for (char c : str) {
        if (c != '\t') part += c;
        else {
            switch (count)
            {
                case 0:
                    ID = part;
                    break;
                case 1:
                    breed = part;
                    break;
                case 2:
                    name = part;
                    break;
                case 3:
                    origin = part;
                    break;
                case 4:
                    lifespan = part;
                    break;
                default:
                    break;
            }
        part.clear();
        ++count;
        }
    }
    traits = part;
}

std::string Species::getID() const{
    return ID;
}
std::string Species::getBreed() const{
    return breed;
}
std::string Species::getName() const{
    return name;
}
std::string Species::getOrigin() const{
    return origin;
}
std::string Species::getLifespan() const{
    return lifespan;
}
std::string Species::getTraits() const{
    return traits;
}