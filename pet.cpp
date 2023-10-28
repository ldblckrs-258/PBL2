#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include "FuncLib.h"
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
protected:
    string id;
    string name;
    string species_id;
    string health;
    Crs details;
    int age; // months
    bool gender; // true ~ male, false ~ female

public:
    Pet() : age(0), gender(true) {
        // Tự động gán ID mới có thứ tự tiếp theo với ID cuối cùng được lưu trong file.
    }

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

        void SetNew(){
            cout << "SET NEW CUSTOMER PET:" << endl;
            cout << "> Name: "; cin.ignore(); getline(cin, name);
            cout << "> Age: "; cin >> age;
            cout << "> Gender (1-male, 0-female): "; cin >> gender;
            cout << "> Owner ID: "; cin >> owner_id;
            cout << "> Service Used ID: "; cin >> service_used;
            cout << "> Current Status: "; cin.ignore(); getline(cin, current_status);
            cout << "> Health: "; getline(cin, health);
            editDetails();
            system("cls");
        }

        void showAll() {
            cout << "CUSTOMER'S PET INFOMATION: " << endl;
            cout << "- ID: " << id << endl;
            cout << "- Name: " << name << endl;
            cout << "- Age: " << age << endl;
            cout << "- Gender: " << getGender() << endl;
            cout << "- Owner: " << getCustomerName(owner_id)<< endl;
            showDetails(1);
            cout << "- Health: " << health << endl;
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



void NewPet() {
    CustomerPet a;
    a.SetNew();
    a.showAll();
}