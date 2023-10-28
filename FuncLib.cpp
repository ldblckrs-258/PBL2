#include "FuncLib.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;
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

int pickMenu() {
    char ch = _getch();
    int output = ch - '0';
    return output;
}

void holdString(const string &str, const double &time){
    cout << str << endl;
    auto duration = (time == int(time)) ? chrono::seconds(int(time)) : chrono::milliseconds(int(time * 1000));
    std::this_thread::sleep_for(duration);
}