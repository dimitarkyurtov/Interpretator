#ifndef BASEEXPRESSION_H
#define BASEEXPRESSION_H

#include "Variables.h"
#include<string>
#include<vector>

class BaseExpression
{
    public:
        virtual bigint evaluate() = 0;

    protected:
        std::string expr;
        virtual const std::string isValid(const std::string&) = 0;
        bool isNumber(const char&);
        bool isOperation(const char&);
        int precedence(const char&);
        bigint applyOp(const bigint&, const bigint&, const char&);
};

#endif // BASEEXPRESSION_H
