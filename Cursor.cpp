#include "Cursor.h"
#include <windows.h>

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getCursorPosition(int &x, int &y) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        x = csbi.dwCursorPosition.X;
        y = csbi.dwCursorPosition.Y;
    } else {
        x = 0;
        y = 0;
    }
}

void moveCursor(int x, int y){
    int dx, dy;
    getCursorPosition(dx, dy);
    gotoXY(x+dx, y+dy);
}