#include "BaseExpression.h"

bool BaseExpression::isNumber(const char& c){
    if(c >= 48 && c <= 57){
        return true;
    }
    return false;
}

bool BaseExpression::isOperation(const char& c){
    if(c == 47 || c == 38 || c == 63 || c == 33 || (c >= 40 && c <= 43) || c == '|'){
        return true;
    }
    return false;
}

int BaseExpression::precedence(const char& op){
    if(op == '+'||op == '-'){
        return 2;
    }
    if(op == '*'||op == '/' || op == '%'){
        return 3;
    }
    if(op == '!' || op == '?' || op == '>' || op == '<'){
        return 1;
    }
    return 0;
}

ulint BaseExpression::applyOp(const ulint& a, const ulint& b, const char& op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
        case '<': return a < b;
        case '>': return a > b;
        case '?': return a == b;
        case '!': return a != b;
        case '&': return a && b;
        case '|': return a || b;
        default:
        return 0;
    }
}
