#include "../include/Variables.h"


Variables::Variables(){

}

Variables* Variables::getInstance()
{
    if (!instance){
        instance = new Variables;
    }
      return instance;
}

bool Variables::isCharacter(const char& c){
    if(c < 97 || c > 122){
            return false;
    }
    return true;
}

bool Variables::isVariable(const std::string& var){
    for(auto it = var.begin(); it != var.end(); ++it){
        if(!isCharacter(*it)){
            return false;
        }
    }
    return true;
}

bool Variables::persist(const std::string& var, const bigint& val){
    if(isVariable(var)){
        params[var] = val;
        return true;
    }
    return false;
}

bigint Variables::at(const std::string& var){
    if(isPresent(var)){
        return params[var];
    }

    // think of something smarter
    return 0;
}


bool Variables::isPresent(const std::string& var){
   if(params.find(var) != params.end()){
        return true;
    }
    return false;
}
