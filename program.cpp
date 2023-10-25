#include <iostream>
#include <Windows.h>
#include "account2.cpp"
// #include "pet.cpp"

using namespace std;

int main() {
    system("cls");
    EmployeeAccount User;
    if (LogIO(User)){
        system("cls");
        User.UpdateInfo();
        User.ShowInfo();
        // NewPet();
    }
}
