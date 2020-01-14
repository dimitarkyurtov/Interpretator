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
    delete f;
}

void Interpreter::print(const std::string& expr, std::ostream& stream = std::cout){
    Expression e = Expression(expr);
    stream << e.evaluate() << std::endl;
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
    unsigned pos = 0;
    unsigned counter = 0;
    unsigned sizze = 0;
    unsigned tellg = 0;
    unsigned rows = 0;
    unsigned ifFlag = 1;
    unsigned elseFlag = 0;
    unsigned whileFlag = 0;
    while(std::getline (file,line)) {
        rows ++;
    }
    file.clear();
    file.seekg(0, file.beg);
    while(std::getline (file,line)) {
        sizze = line.size();
        std::cout << line << std::endl;
        std::cout << whileFlag << std::endl;
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        // Output the text from the file
        row ++;
        col = 0;
        counter = 0;
        while(line[col] == ' '){
            col ++;
            counter ++;
        }
        if(line[col] == ']' && whileFlag > 0){
            whileFlag --;
            if(whileFlag == 0){
                tellg -= sizze + 2;
            }
            row ++;
            file.clear();
            file.seekg(pos, file.beg);/*
            std::getline(file,line);
        std::cout << line << std::endl;
            sizze = line.size();
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());*/
            col = 0;
        }
        else if(line[col] == '}' && elseFlag > 0){
            elseFlag --;
            row ++;
            /*if(whileFlag == 0){
                tellg += sizze +2;
            }/*
            std::getline (file,line);
        std::cout << line << std::endl;
            sizze = line.size();
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());*/
            col = 0;
        }

        else if(line[col] == '>' && ifFlag > 0){
            std::cout <<"ifflag: " << ifFlag << std::endl;
            ifFlag --;
            row ++;
            /*if(whileFlag == 0){
                tellg += sizze +2;
            }/*
            std::getline (file,line);
            sizze = line.size();
        std::cout << line << std::endl;
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());*/
            col = 0;
        } else{
        command = "";
        param="";
        while(line[col] != '=' && line[col] != '('&& line[col] != '<'&& line[col] != '{'){
            command += line[col];
            col ++;
        }
        if (command.compare("if") == 0){
            while(line[col] == ' '){
                col++;
            }
            if(line[col] != '('){
                std::cerr << "wrong syntax at " << row << " " << col+1 << ", expected ( !" << std::endl;
            }
            col ++;
            while(line[col] != ')'){
                while(line[col] == ' '){
                    col++;
                }
                param += line[col];
                col++;
            }
            col ++;
            while(line[col] == ' '){
                col++;
            }
            if(line[col] != '<'){
                std::cerr << "wrong syntax at " << row << " " << col+1 << ", expected { !" << std::endl;
            }
            Expression e = Expression(param);
            if(e.evaluate() == 0){
                     if(whileFlag == 0){
                            tellg += sizze +2;
                        }
                while(line[col] != '>'){
                        std::getline (file,line);
                        if(whileFlag == 0){
                            sizze = line.size();
                            tellg += sizze +2;
                        }

                        row ++;
                        col = 0;
                        while(line[col] == ' '){
                            col++;
                        }
                    }
                    if(whileFlag == 0){
                        tellg -= sizze +2;
                        }
                    elseFlag ++;
                }
            else {
                ifFlag ++;
            }
        }
        else if(command.compare("else") == 0){
            while(line[col] == ' '){
                col++;
            }
            if(line[col] != '{'){
                std::cerr << "wrong syntax at " << row << " " << col+1 << "!" << std::endl;
            }
            if(elseFlag == 0){
                col = 0;
                if(whileFlag == 0){
                            tellg += sizze +2;
                        }
                while(line[col] != '}'){
                    std::getline (file,line);
                    if(whileFlag == 0){
                            sizze = line.size();
                            tellg += sizze +2;
                        }
                    row ++;
                    col = 0;
                    while(line[col] == ' '){
                        col++;
                    }
                }
                if(whileFlag == 0){
                            tellg -= sizze +2;
                        }
            }
        }
        else if(command.compare("while") == 0){
            while(line[col] == ' '){
                col++;
            }
            file.clear();
            pos = tellg;
            std::cout <<"Pos: " << pos << std::endl;
                if(line[col] != '('){
                    std::cerr << "wrong syntax at " << row << " " << col+1 << ", expected ( !" << std::endl;
                }
                col ++;
                while(line[col] != ')'){
                    while(line[col] == ' '){
                        col++;
                    }
                    param += line[col];
                    col++;
                }
                col ++;
                while(line[col] == ' '){
                    col++;
                }
                if(line[col] != '['){
                    std::cerr << "wrong syntax at " << row << " " << col+1 << ", expected { !" << std::endl;
                }
                Expression e = Expression(param);
                if(e.evaluate() == 0){
                    tellg += sizze +2;
                    while(line[col] != ']'){
                            std::getline (file,line);
                            sizze = line.size();
                            tellg += sizze +2;
                            row ++;
                            col = 0;
                            while(line[col] == ' '){
                                col++;
                            }
                        }
                    tellg -= sizze + 2;
                    }
                else {
                    whileFlag ++;
                }
        }
        else if(command.compare("read") == 0){
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
            col ++;
            while(line[col] != ')'){
                    while(line[col] == ' '){
                        col++;
                    }
                if(line[col] != ')'){
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
        if(whileFlag == 0){
            tellg += sizze + 2;
        }
    }
    file.close();
}
