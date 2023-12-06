#include "./Pet.h"
#include "../mylib/FuncLib.h"
#include "../mylib/Cursor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

Pet::Pet(std::string pid, std::string sid)
    : id(pid), name(UDF), gender(true), species_id(sid), age(0), status(UDF) {}

Pet::Pet(const Pet &other)
    : id(other.id), name(other.name), species_id(other.species_id),
      status(other.status), details(other.details), age(other.age), gender(other.gender)
{
    details.setHeight(other.details.getHeight());
    details.setWeight(other.details.getWeight());
    details.setTemperament(other.details.getTemperament());
    details.setIntelligence(other.details.getIntelligence());
    details.setSNeeds(other.details.getSNeeds());
}
std::string Pet::getID() const
{
    return id;
}

std::string Pet::getName() const
{
    return name;
}

std::string Pet::getSpcID() const
{
    return species_id;
}

std::string Pet::getGender() const
{
    if (gender)
        return "male";
    else
        return "female";
}
