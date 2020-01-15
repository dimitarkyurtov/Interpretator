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

bigint Function::call(const std::vector<bigint>& vals){
    if(paramsCount == vals.size()){
        unsigned i = 0;
        for(auto x : vars){
            vars[x.first] = vals[i];
            i++;
        }
        return evaluate();
    } else {
            std::cerr << "Not enough arguments provided\n expected: " << paramsCount << "\n provided: " << vals.size() << std::endl;
        return bigint("0");
    }
}

bigint Function::evaluate(){
    std::stack<char> ops;
    std::stack<bigint> nums;
    unsigned i;
    bigint a;
    bigint b;
    unsigned size = expr.size();
    for(i = 0; i < size; i ++){
        if(expr[i] == '('){
            ops.push(expr[i]);
        }

        else if(isNumber(expr[i])){
            std::string val;

            while(i < size && isNumber(expr[i])){

                val += expr[i];
                i++;
            }

            bigint val2(val);
            nums.push(val2);
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
                    std::cerr << "No variable called " << val << " defined yet" << std::endl;
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
            std::vector<bigint> vars;
            while(expr[i] != ']'){
                if(isNumber(expr[i])){
                    std::string val;

                    while(i < size && isNumber(expr[i])){

                        val += expr[i];
                        i++;
                    }

                    bigint val2(val);
                    vars.push_back(val2);
                    i--;
                }
                i++;
            }
            i++;

            if(Functions::getInstance()->isPresent(val)){
                nums.push(Functions::getInstance()->at(val)->call(vars));
            } else{
                std::cerr << "No function called " << val << " defined yet" << std::endl;
                return 0;
            }

            i--;
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
