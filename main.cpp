#include <iostream>
#include "./code/mylib/FuncLib.h"
#include "./code/PSMenu.cpp"
#include "./code/ASMenu.cpp"
#include "./code/account/EmployeeAccount.h"
#include "./code/account/ManagerAccount.h"

LinkedList<Species> getSpeciesList(){
    LinkedList<Species> list;
    std::ifstream dataFile(getFolder() + "database\\pet\\species.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Cannot open species data file" << std::endl;
        return list;
    }

    std::string line;
    dataFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (std::getline(dataFile, line)){
        if (!line.empty() && line.length() > 50){
            Species snew;
            snew.readLine(line);
            list.push_back(snew);
        }
    }
    dataFile.close();
    return list;
}

bool ELogged(EmployeeAccount &EUser){
    int choice;
    bool logout = false;
    do {
        system("cls");
        printFile(".\\source\\EMenu.txt");
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PSMenu();
                break;
            case 2:
                // GSMenu();
                break;
            case 3:
                // ITMenu();
                break;
            case 4:
                logout = ASMenu(EUser);
                if (logout) return true;
                break;        
            default:
                return false;
        }
    } while (1);
}

bool MLogged(ManagerAccount &MUser){
    int choice;
    bool logout = false;
    do {
        system("cls");
        printFile(".\\source\\EMenu.txt");
        moveCursor(66,-6);  std::cout << "5. Employee Management";
        moveLine(1);    moveCursor(66,0);   std::cout << "0. Exit Program";
        moveLine(5);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PSMenu(true);
                break;
            case 2:
                // GSMenu();
                break;
            case 3:
                // ITMenu();
                break;
            case 4:
                logout = ASMenu(MUser);
                if (logout) return true;
                break; 
            case 5:
                // EMMenu();
                break;
            default:
                return false;
        }
    } while (1);
}

int LogIO(EmployeeAccount &EUser, ManagerAccount &MUser) {
    int choice;
    do {
        system("cls");
        printFile(".\\source\\MainMenu.txt");
        choice = pickMenu();
        switch(choice) {
            case 1:
                if(EUser.Login()){
                    EUser.loadFull();
                    return 1;
                }
                break;
            case 2:
                if (EUser.Signin()){
                    EUser.saveFull();
                    return 1;
                }
                break;
            case 3:
                if (MUser.Login()) {
                    MUser.loadFull();
                    return 2;}
                break;
            default: 
                std::cout << "Exiting ..." << std::endl;
                return 0;
                break;
        }
    } while(1);
} 

LinkedList<Species> SpeciesList = getSpeciesList();

int main() {
    int choice, mode;
    bool login = false;
    EmployeeAccount EUser;
    ManagerAccount::getEL();
    ManagerAccount MUser;
    do {
        mode = LogIO(EUser, MUser);
        login = mode;
        switch (mode)
        {
            case 1:
                if (ELogged(EUser))
                    login = false;
                break;
            case 2:
                if (MLogged(MUser))
                    login = false;
                break;
            default:
                return 0;
        }
    } while(!login);
}
