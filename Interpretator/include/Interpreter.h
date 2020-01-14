#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Variables.h"
#include "Functions.h"
#include "Expression.h"
#include<string>
#include <fstream>
#include<iostream>
#include<algorithm>

class Interpreter
{
    public:
        static Interpreter* getInstance();
        void interpret(std::ifstream& , std::ostream&);

    private:
        void defineFunction(const std::string&, const std::string&, const std::vector<std::string>&);
        void persistParam(const std::string&);
        void print(const std::string&, std::ostream&);
        Variables* paramsPtr;
        Functions* funcsPtr;
        static Interpreter* instance;
        Interpreter();
};

#endif // INTERPRETER_H
