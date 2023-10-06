#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;

string getServiceName(const string &id){
    string value = "undefined";
    // Get service name from 'database/data/Service.xlsx' by ID
    return value;
}

string getCustomerName(const string &id){
    string value = "undefined";
    // Get customer name from 'database/data/Customer.xlsx' by ID
    return value;
}

void firstSymbol(int mode, int number, char symbol) {
    if (mode == 0) cout << number << ". ";
        else cout << symbol << " ";
}

class Crs { // Pet's Characteristic
private:
    double weight; // kilogram
    double height; // meter
    string temperament;
    int intelligence; // level x/10
    string s_need;

public:
    Crs() : weight(0.0), height(0.0), intelligence(0) {}
    Crs(const Crs &other) : weight(other.weight), height(other.height), temperament(other.temperament), intelligence(other.intelligence), s_need(other.s_need) {}

    double getWeight() const { return weight; }
    double getHeight() const { return height; }
    string getTemperament() const { return temperament; }
    int getIntelligence() const { return intelligence; }
    string getSNeeds() const { return s_need; }

    void setWeight(double w) { weight = w; }
    void setHeight(double h) { height = h; }
    void setTemperament(const string &temp) { temperament = temp; }
    void setIntelligence(int intel) { intelligence = intel; }
    void setSNeeds(const string &needs) { s_need = needs; }
};

class Pet {
private:
    string id;
    string name;
    string species_id;
    string health;
    Crs details;
    int age; // months
    bool gender; // true ~ male, false ~ female

public:
    Pet() : age(0), gender(true) {}
    Pet(const Pet &other) : id(other.id), name(other.name), species_id(other.species_id), health(other.health), details(other.details), age(other.age), gender(other.gender) {}

    string getId() const { return id; }
    string getName() const { return name; }
    string getSpeciesId() const { return species_id; }
    string getHealth() const { return health; }
    int getAge() const { return age; }
    string getGender() const {
        if (gender) return "male";
            else return "female";
    }

    void showDetails(int mode = 0) const {
        if (mode==0)
            cout << "PET'S CHARACTERISTIC: " << endl;
        int i=1;
        char s = '+';
        firstSymbol(mode,i++,s);
        cout << "Weight : " << details.getWeight() << " kg"<< endl;
        firstSymbol(mode,i++,s);
        cout << "Height : " << details.getHeight() << " m" << endl;
        firstSymbol(mode,i++,s);
        cout << "Temperament : " << details.getTemperament() << endl;
        firstSymbol(mode,i++,s);
        cout << "Intelligence Level : " << details.getIntelligence() << "/10" << endl;
        firstSymbol(mode,i,s);
        cout << "Special Needs : " << details.getSNeeds() << endl;
    }

    void setId(const string &newId) { id = newId; }
    void setName(const string &newName) { name = newName; }
    void setSpeciesId(const string &newSpeciesId) { species_id = newSpeciesId; }
    void setHealth(const string &newHealth) { health = newHealth; }
    void setAge(int newAge) { age = newAge; }
    void setGender(bool newGender) { gender = newGender; }

    void editDetails() {
        int c;
        cout << "EDIT ";
        showDetails();
        cout << ">> Enter number 1-5 to edit, others to escape: ";
        cin >> c;
        double i1; 
        string i2;
        do {
            switch (c) {
            case 1:
                cout << "Change pet's weight to : ";
                cin >> i1;
                details.setWeight(i1);
                break;
            case 2:
                cout << "Change pet's height to : ";
                cin >> i1;
                details.setHeight(i1);
                break;
            case 3:
                cout << "Change pet's temperament to : ";
                cin.ignore();
                getline(cin, i2);
                details.setTemperament(i2);
                break;
            case 4:
                cout << "Change pet's intelligence level to : ";
                cin >> i1;
                details.setIntelligence(int(i1));
                break;
            case 5:
                cout << "Change pet's special needs to : ";
                cin.ignore();
                getline(cin, i2);
                details.setSNeeds(i2);
                break;
            default:
                cout << "Exit ..." << endl;
                return;
            };
            cout << "Edit other (enter 0 to escape): ";
            cin >> c;
        } while (c != 0);
        system("cls");
    }
};


class CustomerPet : public Pet {
    private:
        string owner_id;
        string service_used; // id
        string current_status;

    public:
        CustomerPet(string oid = "0", string sid = "0") : owner_id(oid), service_used(sid) {}
        CustomerPet(const CustomerPet &other) 
            : Pet(other), owner_id(other.owner_id), service_used(other.service_used), current_status(other.current_status) {}

        string getOwnerId() const { return owner_id; }
        string getServiceUsed() const { return service_used; }
        string getCurrentStatus() const { return current_status; }

        void setOwnerId(const string &newOI) { owner_id = newOI; }
        void setServiceUsed(const string &newSU) { service_used = newSU; }
        void setCurrentStatus(const string &newCS) { current_status = newCS; }

        void showAll() {
            cout << "CUSTOMER'S PET INFOMATION: " << endl;
            cout << "- ID: " << getId() << endl;
            cout << "- Name: " << getName() << endl;
            cout << "- Age: " << getAge() << endl;
            cout << "- Gender: " << getGender() << endl;
            cout << "- Owner: " << getCustomerName(owner_id)<< endl;
            showDetails(1);
            cout << "- Health: " << getHealth() << endl;
            cout << "- Service Used: " << getServiceName(service_used) << endl;
            cout << "- Current Status: " << current_status << endl;
        }

};

class ShopPet : public Pet {
    private:
        int price; // vnd
        string history;
    public:
        ShopPet() : price(0) {}
        ShopPet(const ShopPet &other) : Pet(other), price(other.price), history(other.history) {}

        int getPrice() const { return price; }
        string getHistory() const { return history; }

        void setPrice(int newPrice) { price = newPrice; }
        void setHistory(const string &newHistory) { history = newHistory; }

};



int main() {
    CustomerPet a;
    a.editDetails();
    a.showAll();
    cout << "Press Enter to exit..."; 
    system("pause");
    return 0;
}