#ifndef CRS_H
#define CRS_H
#define UDF "undefined"
#include <iostream>

class Crs { // Pet's Characteristic
private:
    double weight; // kilogram
    double height; // meter
    std::string temperament;
    int intelligence; // level x/10
    std::string s_need;

public:
    Crs();

    double getWeight() const;
    double getHeight() const ;
    std::string getTemperament() const;
    int getIntelligence() const;
    std::string getSNeeds() const;

    void setWeight(double);
    void setHeight(double);
    void setTemperament(const std::string &);
    void setIntelligence(int);
    void setSNeeds(const std::string &);
};

#endif // !CRS_H