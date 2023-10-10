#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "linkedlist.cpp"
using namespace std;


class Account {
    protected:
        string ID;
        string password;
    public: 
        Account(string ID = "account", string pwd = "000000") 
            : ID(ID), password(pwd) {};

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
        string name;
        string doBirth;
        string position;
        string contact;
    public:
        void getInfo() {
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
        Info details;
        int salary;
        LinkedList <string, string> Schedule;
    public:
        void ShowInfo(){
            cout << "ID: " << ID << endl;
            details.getInfo();
            cout << "- Salary: " << salary << " vnd" << endl;
        }
        void UpdateInfo(){

        };
        void GetSch();
        void UpdateSch();
        void GetSalary();
        void UpdateSalary();
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
    string line, savedPwd;
    while (getline(file, line)) {
        size_t pos = line.find(":");
        string savedID = line.substr(0, pos);
        savedPwd = line.substr(pos + 1);
        if (savedID == userID) {
            userFound = true;            
            break;
        }
    }
    if (userFound) {
        Account user(userID, savedPwd);
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




