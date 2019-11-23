#ifndef VARIABLES_H
#define VARIABLES_H

#include <iostream>
#include <unordered_map>
#include <string>

using ulint = unsigned long int;

class Variables
{
    public:
        static Variables* getInstance();
        ulint at(const std::string&);
        bool persist(const std::string& , const ulint& );
        bool isPresent(const std::string&);
        std::unordered_map<std::string, ulint> params;
        bool isVariable(const std::string&);
        bool isCharacter(const char&);

    private:
         static Variables* instance;
         Variables();

};


#endif // VARIABLES_H
