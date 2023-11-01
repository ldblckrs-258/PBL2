#ifndef FUNCLIB_H
#define FUNCLIB_H
#include <string>

bool printFile(const std::string &);
void firstSymbol(int, int, char);
std::string hideInput();
int pickMenu();
void clearCin();
void holdString(const std::string &, const double &);
void holdString(const std::string &);
std::string getFolder();
void drawLine(char, int );
#endif