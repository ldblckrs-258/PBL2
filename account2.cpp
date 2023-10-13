#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "linkedlist.cpp"
using namespace std;
#define UDF "undefined"

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
};

class Info {
    private:
        string name;
        string doBirth;
        string position;
        string contact;
    public:
        Info(string n = UDF, string date = UDF, string pos = UDF, string ct = UDF): name(n), doBirth(date), position(pos), contact(ct){};
        void getInfo(){
            cout << "- Name: " << name << endl;
            cout << "- Date of birth: " << doBirth << endl;
            cout << "- Position: " << position << endl;
            cout << "- Contact: " << contact << endl;
        }
        void setName(string input) {name = input;};
        void setDate(string input) {doBirth = input;};
        void setPos(string input) {position = input;};
        void setContact(string input) {contact = input;};

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
            return true;
        case 2:
            User.Signin();
            return true;
        case 0:
            cout << "Exiting program." << endl;
            return false;
        default: 
            cout << "Invalid choice. Exiting program." << endl;
            return false;
    }
}




