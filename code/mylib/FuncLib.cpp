#include "./FuncLib.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <filesystem>
#include <mutex>
#include <windows.h>

bool printFile(const std::string &filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Can't open soure file!" <<  std::endl;
        return false;
    }
    std::string line;
    while (getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
    inputFile.close();
    return true;
}

void firstSymbol(int mode, int number, char symbol) {
    if (mode == 0) std::cout << number << ". ";
        else std::cout << symbol << " ";
}

std::string hideInput() {
    std::string str;
    char ch;
    while ((ch = _getch()) != '\r') { 
        if (ch == 8) { 
            if (!str.empty()) {
                str.pop_back();
                std::cout << "\b \b"; 
            }
        } else {
            str.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return str;
}

int pickMenu() {
    char ch;
    int output;

    while (true) {
        ch = _getch();
        if (ch >= '0' && ch <= '9') {
            output = ch - '0';
            break;
        }
    }

    return output;
}

void holdString(const std::string &str, const double &time){
    std::cout << str << std::endl;
    auto duration = (time == int(time)) ? std::chrono::seconds(int(time)) : std::chrono::milliseconds(int(time * 1000));
    std::this_thread::sleep_for(duration);
}

void holdString(const std::string &str){
    std::cout << str << std::endl;
    std::cout << "Press Enter to continue...";
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    _getch();
}

namespace fs = std::filesystem;

std::string getFolder() {
    fs::path currentPath = fs::current_path();
    return currentPath.generic_string() + "\\";
}

void drawLine(char ch, int length){
    for (int i=0; i<length; i++)
        std::cout << ch;
}

void clearCin(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

