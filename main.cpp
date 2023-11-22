#include <iostream>
#include "./code/PSMenu.cpp"
#include "./code/AccountMenu.cpp"
LinkedList<Species> SpeciesList;
LinkedList<CustomerPet> CPetsList;
LinkedList<ShopPet> SPetsList;
LinkedList<ManagerAccount> MAList;
LinkedList<EmployeeAccount> EAList;

template<typename T>
bool Logged(T &Acc){
    int choice;
    bool logout = false;
    LinkedList<std::string> menuList;
    menuList.push_back("MAIN MENU");
    menuList.push_back("1. Pets & Species");
    menuList.push_back("2. Goods & Service");
    menuList.push_back("3. Invoices & Transactions");
    menuList.push_back("4. Account settings");
    if (Acc.isManager()) menuList.push_back("5. Account Management");
    menuList.push_back("0. Exit");
    do {
        system("cls");
        printOptions(menuList, 3);
        choice = pickMenu();
        switch (choice)
        {
            case 1:
                PSMenu(Acc.isManager());
                break;
            case 2:
                // GSMenu();
                break;
            case 3:
                // ITMenu();
                break;
            case 4:
                logout = ASMenu(Acc);
                if (logout) return true;
                break;        
            case 5:
                if (Acc.isManager()){
                    AMMenu();
                    break;
                }
                else return false;      
            default:
                return false;
        }
    } while (1);
}

void PrintMain(){
    system("cls");
    printFile(".\\source\\MainMenu.txt",3);
    setColor(3);    gotoXY(0,0);
    std::cout << " Project Base Learing 2"; 
    drawLine(' ',105);  
    std::cout << "Le Duc Bao - Ngo Thi Kim Ly";
    gotoXY(70,12);  std::cout << "PET STORE MANAGEMENT";
    gotoXY(73,15);  std::cout << "> MAIN MENU <";
    gotoXY(48,26);  std::cout << "Press the number key corresponding to the menu items to access.";
    setColor(7);
    gotoXY(70,18);  std::cout << "1. Login as Employee";
    gotoXY(70,19);  std::cout << "2. Sign-in";
    gotoXY(70,20);  std::cout << "3. Login as Manager";
    gotoXY(70,21);  std::cout << "0. Exit program";
    moveLine(7);
}

LinkedList<int> LogIO() {
    int choice;
    LinkedList<int> output;
    output.push_back(-1);
    output.push_back(-1);
    do {
        PrintMain();
        choice = pickMenu();
        switch(choice) {
            case 1:
                output[0] = Login(EAList);
                if (output[0] != -1) {
                    output[1] = 1;
                    return output;
                }
                break;
            case 2:
                output[0] = Signin(EAList);
                if (output[0] != -1) {
                    output[1] = 1;
                    saveEAList();
                    return output;
                }
                break;
            case 3:
                output[0] = Login(MAList);
                if (output[0] != -1) {
                    output[1] = 2;
                    return output;
                }
                break;
            default: 
                std::cout << "Exiting ..." << std::endl;
                output[1] = 0;
                return output;
                break;
        }
    } while(1);
} 



int main() {
    int choice;
    bool reLogin;
    LinkedList<int> LogInfo;
    getSpeciesList();
    getCPList();
    getSPList();
    getEAList();
    getMAList();

    do {
        reLogin = false;
        LogInfo = LogIO();
        if (LogInfo[1] == 0) break;
        if  (LogInfo[0] != -1){
            if (LogInfo[1] == 1)
                reLogin = Logged(EAList[LogInfo[0]]);
            else if (LogInfo[1] == 2)
                reLogin = Logged(MAList[LogInfo[0]]);
            else break;
        }
    } while(reLogin);
}
