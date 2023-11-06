#ifndef CPET_H
#define CPET_H
#include <iostream>
#include "./Pet.h"

class CustomerPet : public Pet {
    private:
        std::string owner_id;
        std::string service_used; // id

    public:
        CustomerPet(std::string pid = "cp0", std::string sid = "s0", std::string oid = "c0" );

        void setPet();
        void editInfo();
        void showDetails(int except = -1);
        void loadFull();
        void saveFull();
        void saveToAll();
        void setNextID();
        void newPet();
        void resetData();
        void existPet();
};

void ViewAllCP();
#endif // !CPET_H