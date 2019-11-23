#include "Function.h"

Function::Function(const std::string& expr, const std::vector<std::string>& varrs){
    this->expr = expr;
    paramsCount = varrs.size();
    paramsPtr = Variables::getInstance();
    for(auto x : varrs){
        if(paramsPtr->isVariable(x) && !paramsPtr->isPresent(x)){
            this->vars[x] = 0;
        }
    }
}

const std::string Function::isValid(const std::string&){
    return expr;
}

ulint Function::call(const std::vector<ulint>& vals){
    if(paramsCount == vals.size()){
        unsigned i = 0;
        for(auto x : vars){
            vars[x.first] = vals[i];
            i++;
        }
    } else {
        std::cerr << "Error!!!" << std::endl;
        return 0;
    }
}

ulint Function::evaluate(const std::vector<ulint>& vals){
    if(paramsCount == vals.size()){
        unsigned i = 0;
        for(auto x : vars){
            vars[x.first] = vals[i];
            i++;
        }
    } else {
        std::cerr << "Error!!" << std::endl;
        return 0;
    }
    std::stack<char> ops;
    std::stack<ulint> nums;
    unsigned i;
    ulint a;
    ulint b;
    unsigned size = expr.size();
    for(i = 0; i < size; i ++){
        if(expr[i] == '('){
            ops.push(expr[i]);
        }

        else if(isNumber(expr[i])){
            ulint val = 0;

            while(i < size && isNumber(expr[i])){

                val = (val*10) + (expr[i]-'0');
                i++;
            }

            nums.push(val);
            i--;
        }

        else if(paramsPtr->isCharacter(expr[i])){
            std::string val;

            while(i < size && paramsPtr->isCharacter(expr[i])){

                val += expr[i];
                i++;
            }

            if(paramsPtr->isPresent(val)){
                nums.push(paramsPtr->params[val]);
            } else if(vars.find(val) != vars.end()){
                nums.push(vars[val]);
            }
             else{
                std::cout << val << std::endl;
                std::cerr << "Error!!!!";
                return 0;
            }

            i--;
        }

        else if(Functions::getInstance()->isCapitalCharacter(expr[i])){
            std::string val;

            while(i < size && Functions::getInstance()->isCapitalCharacter(expr[i])){

                val += expr[i];
                i++;
            }
            i++;
            std::vector<ulint> vars;
            while(expr[i] != ']'){
                if(isNumber(expr[i])){
                    ulint val = 0;

                    while(i < size && isNumber(expr[i])){

                        val = (val*10) + (expr[i]-'0');
                        i++;
                    }
                    vars.push_back(val);
                    i--;
                }
                i++;
            }
            i++;

            if(Functions::getInstance()->isPresent(val)){
                std::cout << Functions::getInstance()->at(val)->evaluate(vars) << std::endl;
                nums.push(Functions::getInstance()->at(val)->evaluate(vars));
            } else{
                std::cerr << "Error!!!";
                return 0;
            }

            i--;
            std::cout << expr[i] << std::endl;
            i++;
        }



        else if(expr[i] == ')'){
            while(!ops.empty() && ops.top() != '('){
                a = nums.top();
                nums.pop();

                b = nums.top();
                nums.pop();

                nums.push(applyOp(b, a, ops.top()));
                ops.pop();
            }
            ops.pop();
        }

        else {
            while(!ops.empty() && precedence(ops.top()) >= precedence(expr[i])){
                a = nums.top();
                nums.pop();
                b = nums.top();
                nums.pop();

                nums.push(applyOp(b, a, ops.top()));
                ops.pop();
            }

            ops.push(expr[i]);
        }
    }

    while(!ops.empty() && precedence(ops.top()) >= precedence(expr[i])){
                a = nums.top();
                nums.pop();

                b = nums.top();
                nums.pop();

                nums.push(applyOp(b, a, ops.top()));
                ops.pop();
            }

    return nums.top();
}
