#include "./FuncLib.h"
#include "./Cursor.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <filesystem>
#include <mutex>
#include <windows.h>
#define WIDTH 48

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

std::string safeInput(int length, bool hide) {
    std::string str;
    int count = 0;
    char ch;
    while ((ch = _getch()) != '\r') { 
        if (ch == 8) { 
            if (!str.empty()) {
                str.pop_back();
                std::cout << "\b \b"; 
                count--;
            }
        } else if (count < length){
            str.push_back(ch);
            if (hide)
                std::cout << '*';
            else std::cout << ch;
            count++;
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
    if (!str.empty())
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

void printCenter(const std::string &str, const int &width){
    int left, right;
    left = (width - str.length())/2;
    right = width - str.length() - left;
    drawLine(' ', left);
    std::cout << str;
    drawLine(' ', right);
}

void printOptions(std::vector<std::string> &list){
    std::ifstream sfile(getFolder() + "source\\Options.txt");
    if (!sfile.is_open()) {
        std::cerr << "Can't open source file Options.txt" << std::endl;
        return;
    }
    std::string line;
    std::string s1, s2, s3;

    for (int i = 0; i < 3 && std::getline(sfile, line); ++i) {
        s1 += line + "\n";
    }
    for (int i = 0; i < 2 && std::getline(sfile, line); ++i) {
        s2 += line + "\n";
    }
    while (std::getline(sfile, line)) {
        s3 += line + "\n";
    }
    sfile.close();
    
    std::cout << s1;
    moveCursor(54,-2);   printCenter(list[0], WIDTH);    moveLine(2);
    for (int i = 1; i < list.size(); ++i){
        std::cout << s2;
        moveCursor(54,-2);   printCenter(list[i], WIDTH);    moveLine(2);
    }
    moveLine(-1);   std::cout << s3;    moveLine(1);
}

std::string commaInt(int number) {
    std::stringstream ss;
    ss << number;

    std::string sNumber = ss.str();
    int length = sNumber.length();
    std::string output;

    for (int i = 0; i < length; ++i) {
        output.push_back(sNumber[i]);
        if ((length - i - 1) % 3 == 0 && i != length - 1) {
            output.push_back(',');
        }
    }
    return output;
}

std::string commaInt(std::string number) {
    int length = number.length();
    std::string output;

    for (int i = 0; i < length; ++i) {
        output.push_back(number[i]);
        if ((length - i - 1) % 3 == 0 && i != length - 1) {
            output.push_back(',');
        }
    }
    return output;
}

void safeOutput(const std::string& str, int length) {
    if (str.length() <= length) {
        std::cout << str;
    } else {
        std::cout << str.substr(0, length - 3) << "...";
    }
}