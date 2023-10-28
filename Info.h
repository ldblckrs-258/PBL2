#ifndef INFO_H
#define INFO_H

#include <string>
#define UDF "undefined"
using namespace std;

class Info {
    private:
        string name;
        string doBirth;
        string position;
        string contact;

    public:
        Info(string n = UDF, string date = "01/01/1970", string pos = UDF, string ct = UDF);
        void getInfo(int mode = 1);
        void UpdateInfo();
        string getName();
        string getDoBirth();
        string getPosition();
        string getContact();
        void setName(string input);
        void setDoBirth(string input);
        void setPosition(string input);
        void setContact(string input);
};

bool isValidDateFormat(const string&);
#endif // INFO_H
