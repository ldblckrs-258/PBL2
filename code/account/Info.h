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

        std::string getName() const;
        std::string getDoBirth() const;
        std::string getPosition() const;
        std::string getContact() const;
        void setName(std::string input);
        void setDoBirth(std::string input);
        void setPosition(std::string input);
        void setContact(std::string input);
};

bool isValidDateFormat(const std::string&);
#endif // INFO_H
