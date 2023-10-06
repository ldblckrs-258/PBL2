#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

string readCellValue(int row, int col, const string& filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return "";
    }

    string line;
    int currentRow = 0;

    while (getline(file, line)) {
        if (currentRow == row) {
            istringstream iss(line);
            string cellValue;
            int currentCol = 0;

            while (getline(iss, cellValue, '\t')) {
                if (currentCol == col) {
                    return cellValue;
                }
                currentCol++;
            }
        }

        currentRow++;
    }

    cerr << "Invalid row or column index." << endl;
    return "";
}

int main() {
    int row = 2;  // Example: row 2
    int col = 6;  // Example: column 3
    string filename = "..\\database\\data\\Species.txt";  // Replace with your actual file name

    string cellValue = readCellValue(row-1, col-1, filename);

    if (!cellValue.empty()) {
        cout << "Cell value at row " << row << ", column " << col << ": " << cellValue << endl;
    }

    return 0;
}
