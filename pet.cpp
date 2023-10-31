#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include "FuncLib.cpp"
#include "Cursor.cpp"
#define UDF "undefined"
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

string getSpeciesName(const string &id){
    string value = "undefined";
    // Get customer name from 'database/data/Species.xlsx' by ID
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
    Crs() : weight(0.0), height(0.0), s_need("None") {
        temperament = UDF;
        intelligence = 5;
    }
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
    string status;
    Crs details;
    int age; // months
    bool gender; // true ~ male, false ~ female

public:
    Pet(string pid = "p0", string sid = "s0") : id(pid), name(UDF), gender(true) {
        species_id = sid;
        age = 0;
        status = UDF;
    }

    string getGender() const {
        if (gender) return "male";
            else return "female";
    }

    void showDetails(int except = -1){
        system("cls");
        printFile("..\\source\\PetInfo.txt");
        if (except != 0)    {gotoXY(34,3);   cout << id;}
        if (except != 1)    {gotoXY(34,5);   cout << name;}
        if (except != 2)    {gotoXY(34,7);   cout << age << " months";}
        if (except != 3)    {gotoXY(34,9);   cout << getGender();}
        if (except != 4)    {gotoXY(34,11);   cout << species_id;}
        if (except != 5)    {gotoXY(34,13);   cout << status;}

        if (except != 11)    {gotoXY(103,6);   cout << details.getHeight() << " m";}
        if (except != 12)    {gotoXY(103,8);   cout << details.getWeight() << " kg";}
        if (except != 13)    {gotoXY(103,10);   cout << details.getTemperament() ;}
        if (except != 14)    {gotoXY(103,12);   cout << details.getIntelligence() << "/10";}
        if (except != 15)    {gotoXY(103,14);   cout << details.getSNeeds();}

        gotoXY(0,21);
    }
    
    void editChar() {
        int c;
        showDetails();
        cout << ">> Press a number 1-5 to edit, others to escape: ";
        c = pickMenu();
        double i1; 
        string i2;
        do {
            switch (c) {
            case 1:
                showDetails(11);
                cout << ">> Enter height (a positive decimal)";
                gotoXY(103,6);  
                cin >> i1;  clearCin();
                gotoXY(0,21);
                details.setHeight(i1);
                break;
            case 2:
                showDetails(12);
                cout << ">> Enter weight (a positive decimal)";
                gotoXY(103,8);  
                cin >> i1;  clearCin();  
                gotoXY(0,21);
                details.setWeight(i1);
                break;
            case 3:
                showDetails(13);
                cout << ">> Enter temperament";
                gotoXY(103,10);  
                getline(cin, i2);  gotoXY(0,21);
                details.setTemperament(i2);
                break;
            case 4:
                showDetails(14);
                cout << ">> Enter intelligence level (an integer from 0 to 10)";
                gotoXY(103,12);  
                cin >> i1;  clearCin();  
                gotoXY(0,21);
                details.setIntelligence(int(i1));
                break;
            case 5:
                showDetails(15);
                cout << ">> Enter special needs";
                gotoXY(103,14);  
                getline(cin, i2);  
                gotoXY(0,21);
                details.setSNeeds(i2);
                break;
            default:
                cout << "Exit ..." << endl;
                return;
            };
            drawLine(' ', 100); moveCursor(-100,0);
            cout << "Edit other (0 to escape): ";
            cin.clear();
            c = pickMenu();
        } while (c != 0);
    }

    void loadFull() {
        string fileName = "..\\database\\pet\\customerPet\\" + id + ".txt";
        fstream file;
        file.open(fileName, ios::in );
        if (!file.is_open()) {
            cerr << "Error opening file to load pet information." << fileName<< endl;
            return;
        }

        string line;
        int lineCount = 0;
        while (getline(file, line)) {
            int it = 0; double dt = 0;
            switch (lineCount)
            {
            case 0:
                id = line;
                break;
            case 1:
                name = line;
                break;
            case 2:
                try{it = stoi(line);}
                catch(const invalid_argument& e){
                    cerr << e.what() << '\n';
                }
                age = it;
                break;
            case 3:
                gender = (line == "1") ? true : false ;
                break;
            case 4:
                species_id = line;
                break;
            case 5:
                status = line;
                break;
            case 8:
                try {dt = stod(line);}
                catch(const invalid_argument& e){
                    cerr << e.what() << '\n';
                }
                details.setHeight(dt);
                break;
            case 9:
                try {dt = stod(line);}
                catch(const invalid_argument& e){
                    cerr << e.what() << '\n';
                }
                details.setWeight(dt);
                break;
            case 10:
                details.setTemperament(line);
                break;
            case 11:
                try{it = stoi(line);}
                catch(const invalid_argument& e){
                    cerr << e.what() << '\n';
                }
                details.setIntelligence(it);
                break;
            case 12:
                details.setSNeeds(line);
                break;
            default:
                break;
            }
            ++lineCount;
        }
        file.close();
    }

    void saveInfo() {
        string fileName = "..\\database\\pet\\customerPet\\" + id + ".txt";
        fstream file;
        file.open(fileName, ios::out);

        if (!file.is_open()) {
            cerr << "Error opening file to save pet information." << endl;
            return;
        }
        
        file << id << endl;
        file << name << endl;
        file << age << endl;
        file << gender << endl;
        file << species_id << endl;
        file << status << endl;
        file.close();
    }

    void saveChar() {
        string fileName = "..\\database\\pet\\customerPet\\" + id + ".txt";
        fstream file;
        file.open(fileName, ios::out | ios::app);

        if (!file.is_open()) {
            cerr << "Error opening file to save pet information." << endl;
            return;
        }
        
        file << details.getHeight() << endl;
        file << details.getWeight() << endl;
        file << details.getTemperament() << endl;
        file << details.getIntelligence() << endl;
        file << details.getSNeeds() << endl;
        file.close();
    }

};


class CustomerPet : public Pet {
    private:
        string owner_id;
        string service_used; // id

    public:
        CustomerPet(string pid = "cp0", string sid = "s0", string oid = "c0" ) : Pet(pid, sid), owner_id(oid), service_used(sid) {}
        void setPet(){
            int choice;
            do {
                showDetails();  
                cout << endl << endl;
                printFile("..\\source\\PetOption.txt");
                choice = pickMenu();                
                switch (choice)
                {
                case 1:
                    editInfo();
                    break;
                case 2:
                    editChar();
                    break;
                default:
                    break;
                }
            } while(choice);
            saveFull();
        }

        void editInfo() {
            int c;
            showDetails();
                    cout << ">> Press a number 1-7 to edit, others to escape: ";
            c = pickMenu();
            do {
                switch (c) {
                case 1:
                    showDetails(1);
                    cout << ">> Enter pet name";
                    gotoXY(34,5);  
                    getline(cin, name);  
                    gotoXY(0,21);
                    break;
                case 2:
                    showDetails(2);
                    cout << ">> Enter age (an integer)";
                    gotoXY(34,7);  
                    cin >> age;  clearCin();  
                    gotoXY(0,21);
                    break;
                case 3:
                    showDetails(3);
                    cout << ">> Enter gender (1 for male, 0 for female)";
                    gotoXY(34,9);  
                    cin >> gender;  clearCin();
                    gotoXY(0,21);
                    break;
                case 4:
                    showDetails(4);
                    cout << ">> Enter species id";
                    gotoXY(34,11);  
                    getline(cin, species_id);   
                    gotoXY(0,21);
                    break;
                case 5:
                    showDetails(5);
                    cout << ">> Enter current status";
                    gotoXY(34,13);  
                    getline(cin, status);   
                    gotoXY(0,21);
                    break;
                case 6:
                    showDetails(6);
                    cout << ">> Enter owner id";
                    gotoXY(34,15);                  
                    getline(cin, owner_id);   
                    gotoXY(0,21);
                    break;
                case 7:
                    showDetails(7);
                    cout << ">> Enter service used id";
                    gotoXY(34,17);  
                    getline(cin, service_used);   
                    gotoXY(0,21);
                    break;
                default:
                    cout << "Exit ..." << endl;
                    return;
                };
                cout << "Edit other (press 0 to escape): ";
                c = pickMenu();
            } while (c != 0);
        }

        void showDetails(int except = -1) {
            Pet::showDetails(except);
            if (except != 6) {gotoXY(34,15);   cout << owner_id;}
            if (except != 7) {gotoXY(34,17);   cout << service_used;}
            gotoXY(0,21);
        }

        void loadFull() {
            Pet::loadFull();
            string fileName = "..\\database\\pet\\customerPet\\" + id + ".txt";
            fstream file;
            file.open(fileName, ios::in );
            if (!file.is_open()) {
                cerr << "Error opening file to load pet information." << fileName<< endl;
                return;
            }
            string line;
            int lineCount = 0;
            while (getline(file, line)) {
                switch (lineCount)
                {
                case 6:
                    owner_id = line;
                    break;
                case 7:
                    service_used = line;
                    break;
                default:
                    break;
                }
                ++lineCount;
            }
            file.close();
        }

        void saveFull() {
            string fileName = "..\\database\\pet\\customerPet\\" + id + ".txt";
            fstream file;
            file.open(fileName, ios::out | ios::app);

            if (!file.is_open()) {
                cerr << "Error opening file to save pet information." << endl;
                return;
            }
            saveInfo();
            file << owner_id << endl << service_used << endl;
            saveChar();
            saveToAll();
        }

        void saveToAll() {
            string fileName = "..\\database\\pet\\allCPets.txt";

            ifstream fileIn(fileName);
            string line;
            while (getline(fileIn, line)) 
                if (line == id) return;
            fileIn.close();

            ofstream fileOut(fileName, ios::app);
            if (!fileOut.is_open()) {
                cerr << "Error opening file to save Customer Pet ID.\n";
                return;
            }

            fileOut << id << endl;
            fileOut.close();            
        }
        
        void setNextID() {
            string fileName = "..\\database\\pet\\allCPets.txt";
            string lastID;

            ifstream fileIn(fileName);
            string line;
            while (getline(fileIn, line)) {
                if (!line.empty())
                    lastID = line;
            }
            fileIn.close();
            if (lastID.empty()) {
                id = "cp1";
            }
            size_t lastDP = lastID.find_first_of("0123456789");
            if (lastDP == string::npos) {
                id = "cp1";
            }
            else {
                string p = lastID.substr(0, lastDP);
                string s = lastID.substr(lastDP);
                int is = stoi(s);
                id = p + to_string(is+1);
            }
        }

        void newPet(){
            setNextID();
            setPet();
            saveFull();
        }

        void existPet(){            
            system("cls");
            printFile("..\\source\\InputID.txt");
            gotoXY(67,3);
            cin >> id;
            moveLine(2);
            bool exist = false;
            string fileName = "..\\database\\pet\\allCPets.txt";
            ifstream fileIn(fileName);
            string line;
            while (getline(fileIn, line)) 
                if (line == id){
                    exist = true;
                    break;
                }
            fileIn.close();
            if (exist){
                loadFull();
                setPet();
            }
            else holdString("ID does not exist, please re-enter or create a new profile!");

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

void ViewAllCP() {
    system("cls");
    printFile("..\\source\\AllCPSample1.txt");
    string allCP = "..\\database\\pet\\allCPets.txt";
    ifstream allCPFile(allCP);
    if(!allCPFile.is_open()){
        cerr << "Error opening " << allCP << endl;
        return;
    }

    vector<string> sID;
    string line;
    while (allCPFile >> line) {
        sID.push_back(line);
    }
    allCPFile.close();

    for (const string &aID : sID) {
        string aCP = "..\\database\\pet\\customerPet\\" + aID + ".txt";
        ifstream aCPFile(aCP);

        if (!aCPFile.is_open()) {
            continue;
        }
        printFile("..\\source\\AllCPSample2.txt");
        string aline;
        int lineCount = 0;
        while (getline(aCPFile, aline)) {
            switch (lineCount)
            {
            case 0:
                moveCursor(8,-2);   cout << aline;   moveLine(2);
                break;
            case 1:
                moveCursor(21,-2);   cout << aline;   moveLine(2);
                break;
            case 4:
                moveCursor(47,-2);   cout << aline;   moveLine(2);
                break;
            case 5:
                moveCursor(118,-2);   cout << aline;   moveLine(2);
                break;
            case 6:
                moveCursor(82,-2);   cout << aline;   moveLine(2);
                break;
            default:
                break;
            }
            ++lineCount;
        }
        aCPFile.close();
    }
    moveLine(-1);
    printFile("..\\source\\AllCPSample3.txt");
}

void petMenu(){
    system("cls");
    printFile("..\\source\\PetMenu.txt");
    int choice = 0;
    CustomerPet CP;
    do {
        choice = pickMenu();
        if (choice == 1){
            CP.newPet();
            system("cls");
            printFile("..\\source\\PetMenu.txt");
        }
        else if (choice == 2){
            CP.existPet();
            system("cls");
            printFile("..\\source\\PetMenu.txt");
        }
        else if (choice == 3){
            ViewAllCP();
            printFile("..\\source\\PetMenu.txt");
        }
        else {  choice = 0; }
    } while (choice);
}

int main(){
    petMenu();
}