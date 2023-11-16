#ifndef SPECIES_H
#define SPECIES_H
#include <string>
class Species{
    private:

        std::string ID;
        std::string breed;
        std::string name;
        std::string origin;
        std::string lifespan;
        std::string traits;
    public:
        Species();
        ~Species(){};
        void readLine(const std::string &str);
        std::string getID() const;
        std::string getBreed() const;
        std::string getName() const;
        std::string getOrigin() const;
        std::string getLifespan() const;
        std::string getTraits() const;
};

void ViewAllSpc();

#endif // !SPECIES_H