#ifndef BASEEXPRESSION_H
#define BASEEXPRESSION_H

#include "Variables.h"
#include<string>
#include<vector>

class BaseExpression
{
    public:
        virtual ulint evaluate(const std::vector<ulint>& vals) = 0;

    protected:
        std::string expr;
        virtual const std::string isValid(const std::string&) = 0;
        bool isNumber(const char&);
        bool isOperation(const char&);
        int precedence(const char&);
        ulint applyOp(const ulint&, const ulint&, const char&);
};

#endif // BASEEXPRESSION_H
