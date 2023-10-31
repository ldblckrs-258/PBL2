#ifndef FUNCLIB_H
#define FUNCLIB_H
#include <string>
using namespace std;

bool printFile(const string &);
void firstSymbol(int, int, char);
string hideInput();
int pickMenu();
void clearCin();
void holdString(const string &, const double &);
void holdString(const string &);
string getFolder();
void drawLine(char, int );
#endif