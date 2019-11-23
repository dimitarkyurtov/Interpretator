#include <iostream>
#include "include/Variables.h"
#include "include/Expression.h"
#include "include/Function.h"
#include "include/Functions.h"
#include<string>
#include<map>
#include<vector>
using namespace std;


Variables* Variables::instance = 0;
Functions* Functions::instance = 0;

int main()
{
    Variables* table = Variables::getInstance();
    Functions* funcTable = Functions::getInstance();
    table->persist("lmao", 10);
    table->persist("lmAo", 11);
    vector<string> v;
    v.push_back("xw");
    v.push_back("y");
    vector<ulint> v2;
    v2.push_back(1);
    v2.push_back(2);
    Function* f = new Function("xw+3*y+lmao", v);
    cout << f->call(v2);
    funcTable->persist("FUNC", f);
    table->persist("lmao", 12);
    cout << funcTable->at("FUNC")->call(v2);
    return 0;
}
