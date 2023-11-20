#include "./Cursor.h"
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

void moveLine(int n){
    COORD coord;    
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hStdout, &csbi);

    coord.X = 0;
    coord.Y = csbi.dwCursorPosition.Y + n;

    SetConsoleCursorPosition(hStdout, coord);
}

void moveInLine(int x){
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hStdout, &csbi);

    coord.X = x;
    coord.Y = csbi.dwCursorPosition.Y;

    SetConsoleCursorPosition(hStdout, coord);
}

void showCursor(bool display){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, display };
	SetConsoleCursorInfo(handle, &cursor);
}