#ifndef EXPRESSION_H
#define EXPRESSION_H

#include"BaseExpression.h"
#include"Functions.h"

class Expression : public BaseExpression
{
    public:
        Expression();
        Expression(const std::string&);
        bigint evaluate();

    protected:
        const std::string isValid(const std::string&);
};

#endif // EXPRESSION_H
