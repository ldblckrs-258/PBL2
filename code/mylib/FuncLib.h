#ifndef FUNCLIB_H
#define FUNCLIB_H
#include <string>
#include <vector>
bool printFile(const std::string &);
void firstSymbol(int, int, char);
std::string safeInput(int length = 15, bool hide = true);
int pickMenu();
void clearCin();
void holdString(const std::string &, const double &);
void holdString(const std::string &);
std::string getFolder();
void drawLine(char, int );
void printCenter(const std::string &, const int &);
void printOptions(std::vector<std::string> &);
std::string commaInt(int);
std::string commaInt(std::string);
void safeOutput(const std::string&, int );
#endif