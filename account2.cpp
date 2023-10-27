#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "linkedlist.cpp"
#include <limits>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;
#define UDF "undefined"

bool printFile(const string &filename){
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Can't open soure file!" << endl;
        return false;
    }
    string line;
    while (getline(inputFile, line)) {
        cout << line << endl;
    }
    inputFile.close();
    return true;
}

void firstSymbol(int mode, int number, char symbol) {
    if (mode == 0) cout << number << ". ";
        else cout << symbol << " ";
}

string hideInput() {
    string str;
    
    char ch;
    while ((ch = _getch()) != '\r') { 
        if (ch == 8) { 
            if (!str.empty()) {
                str.pop_back();
                cout << "\b \b"; 
            }
        } else {
            str.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return str;
}

bool isValidDateFormat(const string& dateStr) {
    if (dateStr.length() != 10) {
        return false;
    }

    if (dateStr[2] != '/' || dateStr[5] != '/') {
        return false;
    }

    istringstream iss(dateStr);
    int day, month, year;
    char separator1, separator2;
    
    if (!(iss >> day >> separator1 >> month >> separator2 >> year)) {
        return false;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1000 || year > 9999) {
        return false;
    }

    return true;
}

int pickMenu() {
    char ch = _getch();
    int output = ch - '0';
    return output;
}

class Info {
    private:
        string name;
        string doBirth;
        string position;
        string contact;
    public:
        Info(string n = UDF, string date = "01/01/1970", string pos = UDF, string ct = UDF): name(n), doBirth(date), position(pos), contact(ct){};
        void getInfo(int mode = 1){
            firstSymbol(mode, 1, '-'); cout << "Name: " << name << endl;
            firstSymbol(mode, 2, '-'); cout << "Date of birth: " << doBirth << endl;
            firstSymbol(mode, 3, '-'); cout << "Position: " << position << endl;
            firstSymbol(mode, 4, '-'); cout << "Contact: " << contact << endl;
        }
        void UpdateInfo(){
            int c;
            cout << "UPDATE ACCOUNT INFORMATION: " << endl;
            getInfo(0);
            cout << "Enter number 1-4 to edit, others to escape: ";
            cin >> c;
            cin.ignore();
            do {
                switch (c) {
                case 1:
                    cout << ">> Name: ";
                    getline(cin, name); 
                    break;
                case 2:
                    do {
                        if (!isValidDateFormat(doBirth)) cout << "Invalid fomart, example: 01/01/1970" << endl;
                        cout << ">> Date of birth (dd/mm/yyyy): ";
                        getline(cin, doBirth);
                    } while(!isValidDateFormat(doBirth));
                    
                    break;
                case 3:
                    cout << ">> Position: ";
                    getline(cin, position); 
                    break;
                case 4:
                    cout << ">> Contact: ";
                    getline(cin, contact); 
                    break;
                default:
                    cout << "Exit ..." << endl;
                    system("cls");
                    return;
                };
                cout << "Edit other (enter 0 to escape): ";
                cin >> c;
                cin.ignore();
            } while (c != 0);
            system("cls");
        }
        string getName(){return name;}
        string getDoBirth(){return doBirth;}
        string getPosition(){return position;}
        string getContact(){return contact;}
        void setName(string input){name = input;}
        void setDoBirth(string input){doBirth = input;}
        void setPosition(string input){position = input;}
        void setContact(string input){contact = input;}
        
};

class Account {
    protected:
        string ID;
        string password;
        Info details;
        bool status;
    public: 
        Account(string ID = "account", string pwd = "000000"): ID(ID), password(pwd) {
            if (ID == "account" && password == "000000") status = false;
            else status = true;
        };

        bool checkPwd(string check){
            return check == password;
        }
        string getID(){
            return ID;
        }
        string getPwd(){
            return password;
        }
        void setPwd(string input){
            password = input;
        }

        bool check(){
            return status;
        }
        bool ChangePwd(){
            string old;
            Start:
            cout << "Enter your OLD password: ";
            cin >> old;
            if (old == "0") return false;
            else if (!checkPwd(old)) {
                cout << "The old password is incorrect, please re-enter (or Enter 0 to exit) " << endl;
                goto Start;
            } 

            cout << "Enter your NEW password: ";
            cin >> password;
            cout << "Password Changed!";
            return true;
        }
        void saveAcc() {
            fstream file;
            file.open("..\\database\\account\\allacc.txt", ios::out | ios::app);
            if (!file.is_open()) {
                cout << "Error opening file." << endl;
                return ;
            }
            file << ID << ":" << password << "\n";
            file.close();
        }
        void Login();
        void Signin();
        void UpdateInfo(){
            details.UpdateInfo();
            saveFull();}
        void loadFull();
        void saveFull();
};

void Account:: saveFull(){
    string fileName = "..\\database\\account\\employee\\" + ID + ".txt";
    fstream file;
    file.open(fileName, ios::out );

    if (!file.is_open()) {
        cout << "Error opening file to save employee information." << endl;
        return;
    }
    
    file << details.getName() << endl;
    file << details.getDoBirth() << endl;
    file << details.getPosition() << endl;
    file << details.getContact() << endl;
    file.close();
}

void Account:: loadFull(){
        string fileName = "..\\database\\account\\employee\\" + ID + ".txt";
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file to load employee information." << endl;
        return;
    }

    string line;
    if (getline(file, line)) details.setName(line);
    if (getline(file, line)) details.setDoBirth(line);
    if (getline(file, line)) details.setPosition(line);
    if (getline(file, line)) details.setContact(line);

    file.close();
}

class EmployeeAccount : public Account {
    private: 
        int salary;
        LinkedList <string, string> Schedule;
    public:
        EmployeeAccount(int s = 0) : Account(), salary(s){};
        void ShowInfo(){
            loadFull();
            cout << "> ID: " << ID << endl;
            details.getInfo();
            cout << "- Salary: " << salary << " vnd" << endl;
        }
        void saveFull();
        void saveSalary();
        void loadFull();
        void UpdateInfo(){
            Account::UpdateInfo();
            saveSalary();
        }
};

void EmployeeAccount:: saveSalary(){
    string fileName = "..\\database\\account\\employee\\" + ID + ".txt";
    fstream file;
    file.open(fileName, ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file to save employee information." << endl;
        return;
    }
    file << salary << endl;
    file.close();
}

void EmployeeAccount:: saveFull() {
    Account::saveFull();
    saveSalary();
}

void EmployeeAccount::loadFull() {
    string fileName = "..\\database\\account\\employee\\" + ID + ".txt";
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Error opening file to load employee information." << endl;
        return;
    }

    Account::loadFull();
    string line;
    int lineCount = 1;
    while (getline(file, line)) {
        if (lineCount == 5) break; 
        ++lineCount;
    } 
    
    salary = stoi(line);
    file.close(); 
}

class ManagerAccount : public Account {
    private: 
        LinkedList <string, string> EmployeeList;
    public:
        void GetInfo();
        void UpdateInfo();
        void GetEL();
        void UpdateEL();
};


void Account:: Login(){
    fstream file;
    file.open("..\\database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return ;
    }

    cout << "Enter your user ID: ";
    cin >> ID;
    bool userFound = false;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        string savedID = line.substr(0, pos);
        password = line.substr(pos + 1);
        if (savedID == ID) {
            userFound = true;            
            break;
        }
    }
    file.close();
    if (userFound) {
        string inputPwd;
        cout << "Enter your password: ";
        inputPwd = hideInput();
        cout << "Login your account..." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        if (checkPwd(inputPwd)) {
            cout << "Logged in successfully!" << endl;
            status = true;
            return;
        }
        cout << "Login failed. Incorrect password." << endl;
    } else
        cout << "User not found. Please register a new account." << endl;
    return;
}

void Account:: Signin(){
    fstream file;
    file.open("..\\database\\account\\allacc.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return ;
    }

    bool userFound = false;
    do {
        if (userFound) {
            cout << "ID already exists, please enter another !" << endl;;
        }
        userFound = false;
        cout << "Enter a new user ID: ";
        cin >> ID;
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(":");
            string savedID = line.substr(0, pos);
            password = line.substr(pos + 1);
            if (savedID == ID) {
                userFound = true;            
                break;
            }
        }
        if (ID == "account") userFound = true; 
    } while (userFound);
    file.close();

    cout << "Enter a new password: ";
    password = hideInput();
    while (password.length() < 6 || password.length() > 15){
        cout << "Password length must be of 6-15 characters: ";
        password  = hideInput();
    }
    string repwd;
    do {
        cout << "Re-enter password: ";
        repwd = hideInput();
        if (repwd != password) {
            cout << "Incorrect, please confirm again! " << endl;}
        else break;
    } while(1);
    saveAcc();
    status = true;
    cout << "New account registered successfully!" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "Login your account..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
}

bool LogIO(EmployeeAccount &User) {
    int choice;
    do {
        system("cls");
        printFile("..\\source\\MenuDraw.txt");
        choice = pickMenu();
        system("cls");
        switch(choice) {
            case 1:
                User.Login();
                if (User.check()) {
                    User.loadFull();
                    return User.check();}
                break;
            case 2:
                User.Signin();
                if (User.check()) return User.check();
                break;
            case 0:
                cout << "Exiting program." << endl;
                return false;
                break;  
            default: 
                cout << "Invalid choice. Exiting program." << endl;
                return false;
                break;
        }
            cout << "1. Return to menu" << endl;
            cout << "0. Exit program" << endl;
            cin >> choice;
            if (!choice) return false;
    } while(1);
}




