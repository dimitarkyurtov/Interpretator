#ifndef VARIABLES_H
#define VARIABLES_H

#include "BigInt.cpp"
#include <iostream>
#include <unordered_map>
#include <string>

using ulint = unsigned long int;

class Variables
{
    public:
        static Variables* getInstance();
        bigint at(const std::string&);
        bool persist(const std::string& , const bigint& );
        bool isPresent(const std::string&);
        std::unordered_map<std::string, bigint> params;
        bool isVariable(const std::string&);
        bool isCharacter(const char&);

    private:
         static Variables* instance;
         Variables();

};


#endif // VARIABLES_H
