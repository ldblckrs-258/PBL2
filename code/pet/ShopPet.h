#ifndef SPET_H
#define SPET_H
#include "./Pet.h"
#include <iostream>
class ShopPet : public Pet {
    private:
        int price; // vnd
        std:: string history;
    public:
        ShopPet(std::string pid = "sp0", std::string sid = "s0");

        int getPrice() const;
        std:: string getHistory() const ;
        void setPrice(int);
        void setHistory(const std:: string &);

        void showDetails(int except = -1);
        void saveToAll();
        void saveFull();
        void editInfo();
        void setPet();
        void loadFull();
        void setNextID();
        void resetData();
        void newPet();
};


#endif // !SPET_H