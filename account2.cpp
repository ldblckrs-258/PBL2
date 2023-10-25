#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "linkedlist.cpp"
using namespace std;
#define UDF "undefined"
void firstSymbol(int mode, int number, char symbol) {
    if (mode == 0) cout << number << ". ";
        else cout << symbol << " ";
}

class Info {
    private:
        string name;
        string doBirth;
        string position;
        string contact;
    public:
        Info(string n = UDF, string date = UDF, string pos = UDF, string ct = UDF): name(n), doBirth(date), position(pos), contact(ct){};
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
            cout << ">> Enter number 1-4 to edit, others to escape: ";
            cin >> c;
            cin.ignore();
            do {
                switch (c) {
                case 1:
                    cout << ">> Name: ";
                    getline(cin, name); 
                    break;
                case 2:
                    cout << ">> Date of birth: ";
                    getline(cin, doBirth); 
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
            } while (c != 0);
            system("cls");
        }
    
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
        void saveAcc(fstream& f) {
            f << ID << ":" << password << "\n";
        }
        void Login();
        void Signin();
        void UpdateInfo(){details.UpdateInfo();}
};


class EmployeeAccount : public Account {
    private: 
        int salary;
        LinkedList <string, string> Schedule;
    public:
        EmployeeAccount(int s = 0) : Account(), salary(s){};
        void ShowInfo(){
            cout << "> ID: " << ID << endl;
            details.getInfo();
            cout << "- Salary: " << salary << " vnd" << endl;
        }
};

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
        cin >> inputPwd;
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
    file.open("..\\database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return ;
    }
    cout << "Enter a new user ID: ";
    cin >> ID;
    while (ID == "account"){
        cout << "Please enter another id :";
        cin >> ID;
    }
    cout << "Enter a new password: ";
    cin >> password;
    while (password.length() < 6 || password.length() > 15){
        cout << "Password length must be of 6-15 characters: ";
        cin >> password;
    }
    status = true;
    saveAcc(file);
    cout << "New account registered successfully!" << endl;
    file.close();
}

bool LogIO(EmployeeAccount &User) {
    int choice;
    cout << ">>  MAIN MENU  <<" << endl;
    cout << "   1. Login" << endl;
    cout << "   2. Sign in" << endl;
    cout << "   0. Exit" << endl;

    cin >> choice;
    system("cls");
    switch(choice) {
        case 1:
            User.Login();
            break;
        case 2:
            User.Signin();
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;  
        default: 
            cout << "Invalid choice. Exiting program." << endl;
            break;
    }
    return User.check();
}




