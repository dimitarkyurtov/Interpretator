#include "Interpreter.h"

Interpreter::Interpreter(){
    paramsPtr = Variables::getInstance();
    funcsPtr = Functions::getInstance();
}

Interpreter* Interpreter::getInstance()
{
    if (!instance){
        instance = new Interpreter;
    }
      return instance;
}

void Interpreter::persistParam(const std::string& param){
    ulint value;
    std::cin >> value;
    paramsPtr->persist(param, value);
}

void Interpreter::defineFunction(const std::string& funcName, const std::string& expr, const std::vector<std::string>& vars){
    Function* f = new Function(expr, vars);
    funcsPtr->persist(funcName, f);
}

void Interpreter::print(const std::string& expr, std::ostream& stream = std::cout){
    Expression* e = new Expression(expr);
    stream << e->evaluate() << std::endl;
}

void Interpreter::interpret(std::ifstream& file, std::ostream& stream = std::cout){
    std::string line;
    std::string command;
    std::string param;
    std::string params;
    std::string funcName;
    unsigned j;
    unsigned row = 0;
    unsigned col;
    while(std::getline (file,line)) {
        // Output the text from the file
        row ++;
        col = 0;
        command = "";
        param="";
        while(line[col] != '=' && line[col] != ' '){
            command += line[col];
            col ++;
        }

        if(command.compare("read") == 0){
            while(line[col] == ' '){
                col++;
            }

            while(paramsPtr->isCharacter(line[col])){
                param += line[col];
                col++;
            }

            if(line[col] != ';'){
                std::cerr << "wrong syntax at " << row << " " << col+1 << "!" << std::endl;
            }
            this->persistParam(param);
        } else if(command.compare("print") == 0){
            while(line[col] != ';'){
                    while(line[col] == ' '){
                        col++;
                    }
                if(line[col] != ';'){
                    param += line[col];
                    col++;
                }
            }
            this->print(param, stream);
        }
        else if(command.find('[') <= command.size()){
            while(line[col] == ' '){
                col++;
            }
            if(line[col] != '='){
                std::cerr << "wrong syntax at " << row << " " << col+1 << "!" << std::endl;
            }else {
                col ++;
                while(line[col] == ' '){
                    col++;
                }
                while(line[col] != ';'){
                    if(line[col] == ' '){
                        while(line[col] == ' '){
                            col++;
                        }
                    }
                    param += line[col];
                    col++;
                }
            }
            funcName = command.substr(0, command.find('['));
            params = command.substr(command.find('['));
            j = 1;
            std::string word;
            std::vector<std::string> vars;
            while(params[j] != ']'){
                word = "";
                while(params[j] != ',' && params[j] != ']'){
                    word += params[j];
                    j++;
                }
                vars.push_back(word);
                if(params[j] != ']'){
                    j++;
                }
            }
            this->defineFunction(funcName, param, vars);
        } else{
            while(line[col] == ' '){
                        col++;
            }
            col++;
            while(line[col] != ';'){
                    while(line[col] == ' '){
                        col++;
                    }
                if(line[col] != ';'){
                    param += line[col];
                    col++;
                }
            }
            Expression e = Expression(param);
            paramsPtr->persist(command, e.evaluate());
        }
    }
}
