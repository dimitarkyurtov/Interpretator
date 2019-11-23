#include <iostream>
#include "include/Variables.h"
#include "include/Expression.h"
#include "include/Function.h"
#include "include/Functions.h"
#include "include/Interpreter.h"
#include<string>
#include<map>
#include<vector>
using namespace std;


Variables* Variables::instance = 0;
Functions* Functions::instance = 0;
Interpreter* Interpreter::instance = 0;

int main()
{
    Interpreter* interpreter = Interpreter::getInstance();
    Variables* table = Variables::getInstance();
    Functions* funcTable = Functions::getInstance();
    ifstream myfile ("program.txt");
    interpreter->interpret(myfile, cout);
    std::vector<ulint> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    table->persist("a", 3);
    table->persist("b", 2);
    cout << funcTable->at("XD")->evaluate(v);
    return 0;
}
