#ifndef FUNCLIB_H
#define FUNCLIB_H
#include <string>
#include "./LinkedList.cpp"

void setColor(int);
bool printFile(const std::string &, int color = 7);
void firstSymbol(int, int, char);
std::string safeInput(int length = 15, bool hide = true);
int pickMenu();
void clearCin();
void holdString(const std::string &, const double &);
void holdString(const std::string &);
std::string getFolder();
void drawLine(char, int);
void printCenter(const std::string &, const int &);
void printOptions(LinkedList<std::string> &, int color = 7);
void printInputBox(LinkedList<std::string> &, int color = 7);
std::string commaInt(int);
std::string commaInt(std::string);
LinkedList<std::string> getSample(const std::string &, bool mode = false);
void safeOutput(const std::string &str, int length, int height = 1);
std::string boxInput(int, int);
std::string getTime();
#endif