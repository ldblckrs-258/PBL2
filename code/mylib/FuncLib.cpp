#include "./FuncLib.h"
#include "./Cursor.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <filesystem>
#include <mutex>
#include <windows.h>

void setColor(int colorCode)
{ // BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
    // ColorAttribute = Foreground + Background * 16
}

bool printFile(const std::string &filename, int color)
{
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Can't open soure file!" << std::endl;
        return false;
    }
    std::string line;
    setColor(color);
    while (getline(inputFile, line))
    {
        std::cout << line << std::endl;
    }
    setColor(7);
    inputFile.close();
    return true;
}

void firstSymbol(int mode, int number, char symbol)
{
    if (mode == 0)
        std::cout << number << ". ";
    else
        std::cout << symbol << " ";
}

std::string safeInput(int length, bool hide)
{
    std::string str;
    int count = 0;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == 8)
        {
            if (!str.empty())
            {
                str.pop_back();
                std::cout << "\b \b";
                count--;
            }
        }
        else if (count < length)
        {
            str.push_back(ch);
            if (hide)
                std::cout << '*';
            else
                std::cout << ch;
            count++;
        }
    }
    std::cout << std::endl;
    return str;
}

int pickMenu()
{
    showCursor(false);
    char ch;
    int output;

    while (true)
    {
        ch = _getch();
        if (ch >= '0' && ch <= '9')
        {
            output = ch - '0';
            break;
        }
        else if (ch == 8)
            return -99; // special choice: backscape
    }
    showCursor(true);
    return output;
}

void holdString(const std::string &str, const double &time)
{
    std::cout << str << std::endl;
    auto duration = (time == int(time)) ? std::chrono::seconds(int(time)) : std::chrono::milliseconds(int(time * 1000));
    std::this_thread::sleep_for(duration);
}

void holdString(const std::string &str)
{
    if (!str.empty())
        std::cout << str << std::endl;
    std::cout << std::endl
              << "Press any key to continue ...";
    _getch();
}

namespace fs = std::filesystem;

std::string getFolder()
{
    fs::path currentPath = fs::current_path();
    return currentPath.generic_string() + "\\";
}

void drawLine(char ch, int length)
{
    for (int i = 0; i < length; i++)
        std::cout << ch;
}

void clearCin()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printCenter(const std::string &str, const int &width)
{
    int left, right;
    left = (width - str.length()) / 2;
    right = width - str.length() - left;
    drawLine(' ', left);
    std::cout << str;
    drawLine(' ', right);
}

void printOptions(LinkedList<std::string> &list, int color)
{
    std::ifstream sfile(getFolder() + "source\\Options.txt");
    if (!sfile.is_open())
    {
        std::cerr << "Can't open source file Options.txt" << std::endl;
        return;
    }
    std::string line;
    std::string s1, s2, s3;

    for (int i = 0; i < 3 && std::getline(sfile, line); ++i)
        s1 += line + "\n";
    for (int i = 0; i < 2 && std::getline(sfile, line); ++i)
        s2 += line + "\n";
    while (std::getline(sfile, line))
        s3 += line + "\n";
    sfile.close();

    setColor(color);
    std::cout << s1;
    setColor(7);
    moveCursor(54, -2);
    printCenter(list[0], 48);
    moveLine(2);
    for (int i = 1; i < list.getSize(); ++i)
    {
        setColor(color);
        std::cout << s2;
        setColor(7);
        moveCursor(54, -2);
        printCenter(list[i], 48);
        moveLine(2);
    }
    moveLine(-1);
    setColor(color);
    std::cout << s3;
    setColor(7);
    moveLine(1);
    showCursor(false);
}

void printInputBox(LinkedList<std::string> &list, int color)
{
    std::ifstream sfile(getFolder() + "source\\InputSample.txt");
    if (!sfile.is_open())
    {
        std::cerr << "Can't open source file InputSample.txt" << std::endl;
        return;
    }
    std::string line;
    std::string s1, s2, s3;

    for (int i = 0; i < 3 && std::getline(sfile, line); ++i)
        s1 += line + "\n";
    for (int i = 0; i < 2 && std::getline(sfile, line); ++i)
        s2 += line + "\n";
    while (std::getline(sfile, line))
        s3 += line + "\n";
    sfile.close();

    setColor(color);
    std::cout << s1;
    setColor(7);
    moveCursor(50, -2);
    printCenter(list[0], 56);
    moveLine(2);
    for (int i = 1; i < list.getSize(); ++i)
    {
        setColor(color);
        std::cout << s2;
        setColor(7);
        moveCursor(50, -2);
        printCenter(list[i], 17);
        moveLine(2);
    }
    moveLine(-1);
    setColor(color);
    std::cout << s3;
    setColor(7);
    moveLine(1);
}

std::string commaInt(int number)
{
    std::stringstream ss;
    ss << number;

    std::string sNumber = ss.str();
    int length = sNumber.length();
    std::string output;

    for (int i = 0; i < length; ++i)
    {
        output.push_back(sNumber[i]);
        if ((length - i - 1) % 3 == 0 && i != length - 1)
        {
            output.push_back(',');
        }
    }
    return output;
}

std::string commaInt(std::string number)
{
    int length = number.length();
    std::string output;

    for (int i = 0; i < length; ++i)
    {
        output.push_back(number[i]);
        if ((length - i - 1) % 3 == 0 && i != length - 1)
        {
            output.push_back(',');
        }
    }
    return output;
}

LinkedList<std::string> getSample(const std::string &filename, bool mode)
{
    std::ifstream sfile(getFolder() + "source\\" + filename);
    LinkedList<std::string> output;
    if (!sfile.is_open())
    {
        std::cerr << "Can't open source file: " << filename << std::endl;
        return output;
    }
    std::string line;
    std::string s1, s2, s3;
    int n1 = mode ? 7 : 5;
    for (int i = 0; i < n1 && std::getline(sfile, line); ++i)
    {
        s1 += line + "\n";
    }
    for (int i = 0; i < 2 && std::getline(sfile, line); ++i)
    {
        s2 += line + "\n";
    }
    while (std::getline(sfile, line))
    {
        s3 += line + "\n";
    }
    sfile.close();
    output.push_back(s1);
    output.push_back(s2);
    output.push_back(s3);
    return output;
}

void safeOutput(const std::string &str, int length, int height)
{
    int xx, yy;
    getCursorPosition(xx, yy);
    int strLength = static_cast<int>(str.length());
    if (strLength <= length)
    {
        std::cout << str;
    }
    else if (height == 1)
    {
        std::cout << str.substr(0, length - 3) << "...";
    }
    else
    {
        int s_i = 0, e_i;
        for (int i = 0; i < height; ++i)
        {
            e_i = s_i + length;
            std::string part;
            for (int j = e_i; j > s_i; --j)
                if (str[j] == ' ')
                {
                    e_i = j;
                    break;
                }

            if (i == height - 1)
            {
                bool elp = e_i < strLength;
                if (!elp)
                {
                    e_i = strLength;
                    part = str.substr(s_i, e_i - s_i);
                }
                else
                {
                    part = str.substr(s_i, length - 3);
                    part += "...";
                }
            }
            else
            {
                part = str.substr(s_i, e_i - s_i);
            }
            std::cout << part;
            gotoXY(xx, ++yy);
            s_i = e_i + 1;
            if (s_i > strLength)
                break;
        }
    }
}

std::string boxInput(int maxlength, int maxheight)
{
    std::string str;
    int cursor[maxheight + 2][2];
    getCursorPosition(cursor[0][0], cursor[0][1]);
    int width = 1, height = 1;
    char ch;
    while ((ch = _getch()) != '\r')
    {
        if (ch == 8)
        {
            if (!str.empty())
            {
                getCursorPosition(cursor[maxheight + 1][0], cursor[maxheight + 1][1]);
                if (cursor[maxheight + 1][0] == cursor[0][0])
                {
                    --height;
                    width = maxlength;
                    --cursor[0][1];
                    gotoXY(cursor[height][0], cursor[height][1]);
                }
                str.pop_back();
                std::cout << "\b \b";
                --width;
            }
        }
        else if (height <= maxheight)
        {
            if ((width >= maxlength) && ch != ' ')
            {
                getCursorPosition(cursor[height][0], cursor[height][1]);
                gotoXY(cursor[0][0], ++cursor[0][1]);
                width = 0;
                ++height;
            }
            str.push_back(ch);
            std::cout << ch;
            ++width;
        }
    }
    std::cout << std::endl;
    return str;
}

std::string getCTime()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);

    std::string timeString;

    if (localTime->tm_hour < 10)
    {
        timeString += '0';
    }
    timeString += std::to_string(localTime->tm_hour) + ":";

    if (localTime->tm_min < 10)
    {
        timeString += '0';
    }
    timeString += std::to_string(localTime->tm_min) + " - ";

    if (localTime->tm_mday < 10)
    {
        timeString += '0';
    }
    timeString += std::to_string(localTime->tm_mday) + "/";

    if ((localTime->tm_mon + 1) < 10)
    {
        timeString += '0';
    }
    timeString += std::to_string(localTime->tm_mon + 1) + "/";
    timeString += std::to_string(localTime->tm_year + 1900);

    return timeString;
}

std::string toUpperCase(const std::string &str)
{
    std::string result = clearStr(str);
    for (char &c : result)
    {
        if ('a' <= c && c <= 'z')
        {
            c -= 32;
        }
    }
    return result;
}