#ifndef SPET_H
#define SPET_H
#include "./Pet.h"
#include <iostream>
class ShopPet : public Pet {
    private:
        int price; // vnd
        std:: string history;
    public:
        ShopPet();
        int getPrice() const;
        std:: string getHistory() const ;

        void setPrice(int);
        void setHistory(const std:: string &);

};

#endif // !SPET_H