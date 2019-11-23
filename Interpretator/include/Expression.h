#ifndef EXPRESSION_H
#define EXPRESSION_H

#include"BaseExpression.h"

class Expression : public BaseExpression
{
    public:
        Expression();
        Expression(const std::string&);
        ulint evaluate();

    protected:
        const std::string isValid(const std::string&);
};

#endif // EXPRESSION_H
