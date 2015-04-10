#include "LexicalAnalyzer.hpp"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
LexicalAnalyzer::LexicalAnalyzer(string in) : input(in), charClass(ERROR), currentChar(' '), lexenum("") {

    printInput = in;
    depth = 0;
    sKeywords [0] = "if";
    sKeywords [1] = "else";
    sKeywords [2] ="int";
    sKeywords [3] = "return";
    sKeywords [4] = "void";
    sKeywords [5] = "while";
    sKeywords [6] = "float";
    getChar();
}

LexicalAnalyzer::~LexicalAnalyzer() {
}

void LexicalAnalyzer::setNewInput(string in)   {
    input = in;
    printInput = in;
    getChar();
}

void LexicalAnalyzer::linePrint() {

    cout << "INPUT: "<< printInput << endl;
}

bool LexicalAnalyzer::isKeyword(string in){

    bool keyword = false;
    for (int i = 0; i < 7; i++) {
        if(sKeywords[i].compare(in) == 0){
            keyword = true;
            break;
        }
    }
    return keyword;

}

bool LexicalAnalyzer::isSymbol() {
    bool symbol = false;
    if (currentChar == '(' || currentChar == ')' || currentChar == ',' || currentChar =='{' || currentChar == '}' ||
            currentChar == ';' || currentChar == '[' || currentChar == ']' ||
            currentChar == ':' || currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '=' ||
            currentChar == '<' || currentChar == '>' || currentChar == '!'){
        if(currentChar == '{'){

           depth++;
        }
        if(currentChar == '}'){
            depth--;
        }
        symbol = true;
    }
    return symbol;
}

void LexicalAnalyzer::getChar(){

    //cout<<"Current String: "<< input<<endl;
    if(input.size() > 0) {
        currentChar = input[0];
        input.erase(0, 1);
    } else{
        currentChar = '$';
    }
    if(currentChar == '/' && input[0] == '*'){
        xComment.push(1);
        input.erase(0, 1);
        getChar();

    }

    if (!xComment.empty() && currentChar != '$') {

        if (currentChar == '*' && input[0] == '/') {
            xComment.pop();
            currentChar = input[0];
            input.erase(0, 1);

        } else {
            if (currentChar == '/' && input[0] == '*') {
                xComment.push(1);
                input.erase(0, 1);
            }
        }
        getChar();

    }

    charClass = ERROR;


    if((currentChar > 64 && currentChar < 91) || (currentChar > 96 && currentChar < 123))
        charClass = LETTER;

    if(currentChar > 47 && currentChar < 58)
        charClass = DIGIT;

    if(currentChar == ' ' || currentChar == '\t' || currentChar == '\n')
        charClass = SPACE;

    if(currentChar == '$')
        charClass = STOP;

    if(isSymbol()){

        if(currentChar == '/'){

            if(currentChar == '/' && input[0] == '/'){
                while(input.size() > 0){
                    getChar();
                }
                getChar();
            }else{

                charClass = SYMBOL;

            }


        }else{
            charClass = SYMBOL;
        }

    }

}

void LexicalAnalyzer::addChar() {
    lexenum += currentChar;
}

int LexicalAnalyzer::lex() {
    lexenum = "";

    while (charClass == SPACE) getChar();

    if (charClass == ERROR){
        addChar();
        getChar();
        return ERROR;
    }

    if (charClass == STOP){
        return STOP;
    }

    switch (charClass) {
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            return isKeyword(lexenum) ? KEYWORD : ID;
            break;
        case DIGIT:
            addChar();
            getChar();
            isFloat = false;
            if(currentChar == '.'){
                addChar();
                isFloat = true;
                getChar();
                if(currentChar == 'E'){
                    addChar();
                    isFloat = true;
                    getChar();
                    if(currentChar == '+' || currentChar == '-'){
                        addChar();
                        getChar();
                    }
                }
            }
            if(currentChar == 'E'){
                addChar();
                isFloat = true;
                getChar();
                if(currentChar == '+' || currentChar == '-'){
                    addChar();
                    getChar();
                }
            }

            while (charClass == DIGIT) {
                addChar();
                getChar();
                if(currentChar == '.'){
                    addChar();
                    isFloat = true;
                    getChar();
                }
                if(currentChar == 'E'){
                    addChar();
                    isFloat = true;
                    getChar();
                    if(currentChar == '+' || currentChar == '-'){
                        addChar();
                        getChar();
                    }
                }

            }
            if(isFloat){
                isFloat = false;
                return FLOAT;
            }else{
                return INT;
            }

            break;
        case SYMBOL:
            if(currentChar == '<'){
                addChar();
                getChar();
                if(currentChar == '='){
                    addChar();
                    getChar();
                }
            } else{
                if(currentChar == '>'){
                    addChar();
                    getChar();
                    if(currentChar == '='){
                        addChar();
                        getChar();
                    }
                }else{
                    if (currentChar == '='){
                        addChar();
                        getChar();
                        if(currentChar == '='){
                            addChar();
                            getChar();
                        }
                    }else{
                        if(currentChar == '!'){
                            addChar();
                            getChar();
                            if(currentChar == '='){
                                addChar();
                                getChar();
                            }
                        }else{
                            addChar();
                            getChar();
                        }
                    }
                }
            }
            return SYMBOL;
            break;
        default:break;
    }
    return 0;
}
#pragma clang diagnostic pop