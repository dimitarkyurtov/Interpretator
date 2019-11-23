#ifndef FUNCTION_H
#define FUNCTION_H

#include "BaseExpression.h"
#include "Variables.h"
#include<vector>
#include<stack>
#include<map>

class Function : BaseExpression
{
    public:
        Function(const std::string&, const std::vector<std::string>&);
        ulint evaluate();
        ulint call(const std::vector<ulint>&);

    protected:
        unsigned paramsCount;
        Variables* paramsPtr;
        std::map<std::string, ulint> vars;
        const std::string isValid(const std::string&);
};

#endif // FUNCTION_H
