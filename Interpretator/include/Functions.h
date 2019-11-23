#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Function.h"
#include <unordered_map>
#include <string>

class Functions
{
    public:
        static Functions* getInstance();
        Function* const at(const std::string&);
        bool persist(const std::string& , Function* const);
        bool isPresent(const std::string&);
        std::unordered_map<std::string, Function*> funcs;
        bool isFunction(const std::string&);
        bool isCapitalCharacter(const char&);

    private:
         static Functions* instance;
         Functions();
};

#endif // FUNCTIONS_H
