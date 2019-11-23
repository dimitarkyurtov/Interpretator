#include "Functions.h"

Functions::Functions(){

}

Functions* Functions::getInstance()
{
    if (!instance){
        instance = new Functions;
    }
      return instance;
}

bool Functions::isCapitalCharacter(const char& c){
    if(c < 65 || c > 90){
            return false;
    }
    return true;
}

bool Functions::isFunction(const std::string& var){
    for(auto it = var.begin(); it != var.end(); ++it){
        if(!isCapitalCharacter(*it)){
            return false;
        }
    }
    return true;
}

bool Functions::persist(const std::string& var, Function* const val){
    if(!isPresent(var) && isFunction(var)){
        funcs[var] = val;
        return true;
    }
    return false;
}

Function* const Functions::at(const std::string& var){
    if(isPresent(var)){
        return funcs[var];
    }

    return nullptr;
}


bool Functions::isPresent(const std::string& var){
   if(funcs.find(var) != funcs.end()){
        return true;
    }
    return false;
}

