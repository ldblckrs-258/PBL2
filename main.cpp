#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

template <typename T, typename P>
class LinkedList {
    private:
        struct Node {
            T data1;
            P data2;
            Node* next;
            Node(const T& data) : data(data), next(nullptr) {}
        };
        Node* head;

    public:
        LinkedList() : head(nullptr) {}

        ~LinkedList() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void append(const T& data) {
            if (!head) {
                head = new Node(data);
            } else {
                Node* current = head;
                while (current->next) {
                    current = current->next;
                }
                current->next = new Node(data);
            }
        }

        void remove(const T& value) {
            Node* current = head;
            Node* prev = nullptr;
            
            while (current) {
                if (current->data == value) {
                    if (prev) {
                        prev->next = current->next;
                    } else {
                        head = current->next;
                    }
                    delete current;
                    return; 
                }
                
                prev = current;
                current = current->next;
            }
        }

        void removeLast() {
            if (!head) {
                return; 
            }
            if (!head->next) {
                delete head;
                head = nullptr;
                return; 
            }
            Node* current = head;
            Node* prev = nullptr;
            while (current->next) {
                prev = current;
                current = current->next;
            }
            delete current;
            prev->next = nullptr;
        }

        void clear() {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }

        void display() {
            Node* current = head;
            while (current) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;
        }
};


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
};

class Info {
    private:
        string Name;
        string DoBirth;
        string Position;
        string Contact;
    public:
        void ChangeDirect(int index);
        void GetDirect(int index, string value);
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


int main() {
    fstream file;
    file.open("..\\database\\account\\allacc.txt", ios::in | ios::out | ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int choice;
    cout << "Enter '1' to log in, '2' to create a new account, or '0' to quit: ";
    cin >> choice;

    if (choice == 1) {
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
        file.clear();  // Clear EOF flag
        file.seekg(0, ios::beg);  // Reset pointer

        if (userFound) {
            Account user;
            if (user.login()) {
                // Làm việc sau khi đăng nhập thành công
            }
        } else {
            cout << "User not found. Please register a new account." << endl;
        }
    } 
    
    else if (choice == 2) {
        string newID, newPassword;
        cout << "Enter a new user ID: ";
        cin >> newID;
        cout << "Enter a new password: ";
        cin >> newPassword;
        Account newUser(newID, newPassword);
        newUser.saveAcc(file);
        cout << "New account registered successfully!" << endl;
    } 
    
    else if (choice == 0) 
        cout << "Exiting program." << endl;
    
    else 
        cout << "Invalid choice. Exiting program." << endl;

    file.close();

    return 0;
}




