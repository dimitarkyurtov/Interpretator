#ifndef FUNCTION_H
#define FUNCTION_H

#include "BaseExpression.h"
#include "Variables.h"
#include "Functions.h"
#include<vector>
#include<stack>
#include<map>

class Function : BaseExpression
{
    public:
        Function(const std::string&, const std::vector<std::string>&);
        bigint evaluate();
        bigint call(const std::vector<bigint>&);

    protected:
        unsigned paramsCount;
        Variables* paramsPtr;
        std::map<std::string, bigint> vars;
        const std::string isValid(const std::string&);
};

#endif // FUNCTION_H
