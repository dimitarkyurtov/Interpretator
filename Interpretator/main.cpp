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
    /*std::vector<ulint> v;
    v.push_back(1);
    table->persist("a", 3);
    table->persist("b", 2);
    table->persist("c", 4);
    /*
    std::vector<std::string> v2;
    v2.push_back("x");
    Function f = Function("2*3*x", v2);
    cout << f.call(v);
    cout << funcTable->at("XD")->call(v) << endl;
    std::vector<ulint> v2;
    Expression e = Expression("LMAO[3,1]");
    cout << e.evaluate();*/
    interpreter->interpret(myfile, cout);
    return 0;
}
