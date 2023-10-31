#include "FuncLib.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <filesystem>
#include <mutex>
#include <windows.h>

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

void holdString(const string &str){
    cout << str << endl;
    cout << "Press Enter to continue...";
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    _getch();
}

namespace fs = std::filesystem;

string getFolder() {
    fs::path currentPath = fs::current_path();
    return currentPath.generic_string() + "\\";
}

void drawLine(char ch, int length){
    for (int i=0; i<length; i++)
        cout << ch;
}

void clearCin(){
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void moveLine(int n){
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hStdout, &csbi);

    coord.X = 0;
    coord.Y = csbi.dwCursorPosition.Y + n;

    SetConsoleCursorPosition(hStdout, coord);
}

