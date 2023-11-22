#include "./Crs.h"

Crs::Crs() : weight(0.0), height(0.0), s_need("None"), temperament(UDF), intelligence(5){}

double Crs::getWeight() const { return weight; }
double Crs::getHeight() const { return height; }
std::string Crs::getTemperament() const { return temperament; }
int Crs::getIntelligence() const { return intelligence; }
std::string Crs::getSNeeds() const { return s_need; }

void Crs::setWeight(double w) { weight = w; }
void Crs::setHeight(double h) { height = h; }
void Crs::setTemperament(const std::string &temp) { if(!temp.empty())   temperament = temp; }
void Crs::setIntelligence(int intel) { intelligence = intel; }
void Crs::setSNeeds(const std::string &needs) { if(!needs.empty())   s_need = needs; }