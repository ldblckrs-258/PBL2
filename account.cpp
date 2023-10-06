#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "linkedlist.cpp"
using namespace std;


class Account {
    private:
        string ID;
        string Password;
    public: 
        Account(string ID = "account", string pwd = "123456") 
            : ID(ID), Password(pwd) {};

        bool checkPwd(string check){
            return check == Password;
        }
        string getID(){
            return ID;
        }
        string getPwd(){
            return Password;
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
            cin >> Password;
            cout << "Password Changed!";
            return true;
        }

        void saveAcc(fstream& f) {
            f << ID << ":" << Password << "\n";
        }

        bool login() {
            string inputPwd;
            cout << "Enter your password: ";
            cin >> inputPwd;
            if (checkPwd(inputPwd)) {
                cout << "Logged in successfully!" << endl;
                return true;
            }
            cout << "Login failed. Incorrect password." << endl;
            return false;
        }

        void getInfo() {
            cout << "Account ID : " << ID << endl;
            
        }
};

class Info {
    private:
        string Name;
        string DoBirth;
        string Position;
        string Contact;
    public:
        string getName() {return Name;}
        string getDoBirth() {return DoBirth;}
        string getPosition() {return Position;}
        string getName() {return Name;}
};

class EmployeeAccount : public Account {
    private: 
        Info Details;
        LinkedList <string, string> Schedule;
        int Salary;
    public:
        void GetInfo();
        void UpdateInfo();
        void GetSch();
        void UpdateSch();
        void GetSalary();
        void UpdateSalary();
        void getInfo() {
            cout << "Account ID : " << getID();
        }
};

class ManagerAccount : public Account {
    private: 
        Info Details;
        LinkedList <string, string> EmployeeList;
    public:
        void GetInfo();
        void UpdateInfo();
        void GetEL();
        void UpdateEL();
};

Account Login(){
    fstream file;
    file.open("..\\database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    Account temp;
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return temp;
    }

    string userID;
    cout << "Enter your user ID: ";
    cin >> userID;
    bool userFound = false;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        string savedID = line.substr(0, pos);
        if (savedID == userID) {
            userFound = true;
            break;
        }
    }
    if (userFound) {
        Account user(userID);
        if (user.login()){ file.close(); return user;}
    } else
        cout << "User not found. Please register a new account." << endl;
    file.close();
    return temp;
}


Account Signin(){
    fstream file;
    file.open("..\\database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        Account temp;
        return temp;
    }

    string newID, newPassword;
    cout << "Enter a new user ID: ";
    cin >> newID;
    cout << "Enter a new password: ";
    cin >> newPassword;
    Account newUser(newID, newPassword);
    newUser.saveAcc(file);
    cout << "New account registered successfully!" << endl;
    file.close();
    return newUser;
}

int main() {
    Account User;
    int choice;
    cout << "Enter '1' to log in, '2' to create a new account, or '0' to quit: ";
    cin >> choice;

    if (choice == 1) {
        User = Login();
    } 
    
    else if (choice == 2) {
        User = Signin();
    } 
    
    else if (choice == 0) 
        cout << "Exiting program." << endl;
    
    else 
        cout << "Invalid choice. Exiting program." << endl;

    return 0;
}




