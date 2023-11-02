#ifndef INFO_H
#define INFO_H

#include <string>
#define UDF "undefined"
class Info {
    private:
        std::string name;
        std::string doBirth;
        std::string position;
        std::string contact;

    public:
        Info(std::string n = UDF, std::string date = "01/01/1970", std::string pos = UDF, std::string ct = UDF);
        void getInfo(std::string sfname, int except = 10);
        void UpdateInfo();
        std::string getName();
        std::string getDoBirth();
        std::string getPosition();
        std::string getContact();
        void setName(std::string input);
        void setDoBirth(std::string input);
        void setPosition(std::string input);
        void setContact(std::string input);
};

bool isValidDateFormat(const std::string&);
#endif // INFO_H
