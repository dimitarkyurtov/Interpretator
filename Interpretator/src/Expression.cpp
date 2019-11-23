#include "Expression.h"
#include<stack>

Expression::Expression(){

}

Expression::Expression(const std::string& str){
    std::string err = isValid(str);
    if(err != ""){
        std::cerr << err << std::endl;
    } else
        expr = str;
}

const std::string Expression::isValid(const std::string& expr){
    std::string err = "";
    return err;
}

ulint Expression::evaluate(){
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

        else if(Variables::getInstance()->isCharacter(expr[i])){
            std::string val;

            while(i < size && Variables::getInstance()->isCharacter(expr[i])){

                val += expr[i];
                i++;
            }

            if(Variables::getInstance()->isPresent(val)){
                nums.push(Variables::getInstance()->params[val]);
            } else{
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
            std::vector<ulint> vars;
            std::string word;
            while(expr[i] != ']'){
                word = "";
                if(Variables::getInstance()->isCharacter(expr[i])){
                    while(Variables::getInstance()->isCharacter(expr[i])){
                        word += expr[i];
                        i++;
                    }
                    if(Variables::getInstance()->isPresent(word)){
                        vars.push_back(Variables::getInstance()->at(word));
                    } else {
                        std::cerr << "No variable called " << word << " defined yet" << std::endl;
                    }
                }
                if(isNumber(expr[i])){
                    ulint val = 0;

                    while(i < size && isNumber(expr[i])){

                        val = (val*10) + (expr[i]-'0');
                        i++;
                    }
                    vars.push_back(val);
                    i--;
                }
                if(expr[i] != ']'){
                   i++;
                }
            }
            i++;

            if(Functions::getInstance()->isPresent(val)){
                nums.push(Functions::getInstance()->at(val)->call(vars));
            } else{
                std::cerr << "No function called " << val << " defined yet" << std::endl;
                return 0;
            }

            i--;
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
