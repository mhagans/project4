//
// Created by Marcus on 4/12/2015.
//

#include "CodeGenerator.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;



CodeGenerator::CodeGenerator() {
    lineIndex = 1;
    tempVarIndex = 0;

}

void CodeGenerator::FunctionLine(string type, string id, int params) {

    char buffer[100];
    currentFunctionID = id.c_str();
    sprintf(buffer, "%-9d %-14s %-14s %-14s %-d\n", lineIndex, "func", id.c_str(), type.c_str(), params);

    printf("%s", buffer);
    lineIndex++;

}

void CodeGenerator::printParam() {
    char buffer[100];

    sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "param", " ", " ", " ");

    printf("%s", buffer);
    lineIndex++;
}


void CodeGenerator::VarAllocation(string id) {
    char buffer[100];

    sprintf(buffer, "%-9d %-14s %-14d %-14s %-s\n", lineIndex, "alloc", 4, " ", id.c_str());

    printf("%s", buffer);
    lineIndex++;
}

void CodeGenerator::VarAllocation(string id, string num) {
    char buffer[100];
    int size;
    istringstream(num) >> size;

    sprintf(buffer, "%-9d %-14s %-14d %-14s %-s\n", lineIndex, "alloc", 4, " ", id.c_str());
    printf("%s", buffer);
    lineIndex++;

    for (int i = 0; i < size-1; i++) {
        sprintf(buffer, "%-9d %-14s %-14d %-14s %-s\n", lineIndex, "alloc", 4, " ", " ");
        printf("%s", buffer);
        lineIndex++;
    }
}

void CodeGenerator::Evaluate(queue<string> evalQue) {

    string rightSide;
    string leftSide;
    string firstOperand;
    string secondOperand;
    int operatorID;
    string compareOperator;
    char currentEvalTop;

    do {
        if (evalQue.front()[1] == '$') {
            evalQue.front().erase(evalQue.front().begin()+1);
        }
        currentEvalTop = evalQue.front()[0];


        switch (currentEvalTop) {
            case '-':
            case '+':
                if (operatorQue.empty()) {
                    // Check to see if the stack is empty
                    operatorQue.push(evalQue.front());
                    evalQue.pop();

                }else {
                    // Check to see if a ( is on the top
                    if(operatorQue.top()[0] == '(') {
                        operatorQue.push(evalQue.front());
                    }else {
                        // check to see if there is * or / at the top of stack
                        if (operatorQue.top()[0] == '*' || operatorQue.top()[0] == '/') {
                            secondOperand = operandQue.top();
                            operandQue.pop();
                            firstOperand = operandQue.top();
                            operandQue.pop();
                            // check to see if * or / then Assign a a enum for * or /
                            if(operatorQue.top()[0] == '*') {
                                operatorID = MULT;
                            }else {
                                operatorID = DIV;
                            }

                            ArithimiticFunction(firstOperand, secondOperand, operatorID);
                            operatorQue.push(evalQue.front());

                        }else {
                            // add + or - since no higher precedence is there
                            operatorQue.push(evalQue.front());
                            evalQue.pop();

                        }
                    }
                }
                break;
            case '*':
            case '/':
                if (operatorQue.empty()) {
                    operandQue.push(evalQue.front());
                    evalQue.pop();
                }else {
                    if (operatorQue.top()[0] == '(') {
                        operatorQue.push(evalQue.front());
                        evalQue.pop();

                    }else {
                        operatorQue.push(evalQue.front());
                        evalQue.pop();
                    }
                }
                break;
            case '=':
                operatorQue.push(evalQue.front());
                evalQue.pop();
                break;
            case '(':
                operatorQue.push(evalQue.front());
                evalQue.pop();
                break;
            case ')':
                break;
            case '<':
            case '>':
                if(operatorQue.top()[0] == '*' || operatorQue.top()[0] == '/' || operatorQue.top()[0] == '+' || operatorQue.top()[0] == '-') {
                    secondOperand = operandQue.top();
                    operandQue.pop();
                    firstOperand = operandQue.top();
                    operandQue.pop();
                    char operatorTop = operatorQue.top()[0];
                    operatorQue.pop();

                    switch (operatorTop) {
                        case '+':
                            operatorID = PLUS;
                            break;
                        case '-':
                            operatorID = SUB;
                            break;
                        case '*':
                            operatorID = MULT;
                            break;
                        case '/':
                            operatorID = DIV;
                            break;
                    }

                    ArithimiticFunction(firstOperand, secondOperand, operatorID);
                    operatorQue.push(evalQue.front());
                    evalQue.pop();


                }
                break;

            default:
                operandQue.push(evalQue.front());
                evalQue.pop();
        }
    } while (!evalQue.empty());
    do {
        secondOperand = operandQue.top();
        operandQue.pop();
        firstOperand = operandQue.top();
        operandQue.pop();
        switch (operatorQue.top()[0]) {
            case '+':
                operatorID = PLUS;

                break;
            case '-':
                operatorID = SUB;
                break;
            case '*':
                operatorID = MULT;
                break;
            case '/':
                operatorID = DIV;
                break;
            case '<':
                if(operatorQue.top().compare("<=") == 0) {
                    operatorID = LTEQ;
                } else {
                    operatorID = LT;
                }
                break;
            case '>':
                if(operatorQue.top().compare(">=") == 0) {
                    operatorID = GTEQ;
                } else {
                    operatorID = GT;
                }
                break;
            case '!':
                operatorID = NTEQ;
                break;
            case '=':
                if(operatorQue.top().compare("==") == 0) {
                    operatorID = ISEQUAL;
                } else {
                    operatorID = EQUAL;
                }


                break;
        }

        ArithimiticFunction(firstOperand, secondOperand, operatorID);
        operatorQue.pop();

    } while (!operatorQue.empty());

}

void CodeGenerator::ArithimiticFunction(string operandOne, string operandTwo, int operatorID) {
    char buffer[100];
    int jumpIndex;
    string jumpSign;
    ostringstream convert;
    convert << tempVarIndex;
    string tempID;

    tempID = "_t" + convert.str();

    switch (operatorID) {
        case PLUS:
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "add", operandOne.c_str(), operandTwo.c_str(), tempID.c_str());
            printQue.push_back(buffer);
            operandQue.push(tempID);
            lineIndex++;
            tempVarIndex++;
            break;
        case SUB:
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "sub", operandOne.c_str(), operandTwo.c_str(), tempID.c_str());
            printQue.push_back(buffer);
            operandQue.push(tempID);
            lineIndex++;
            tempVarIndex++;
            break;
        case MULT:
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "mult", operandOne.c_str(), operandTwo.c_str(), tempID.c_str());
            printQue.push_back(buffer);
            operandQue.push(tempID);
            lineIndex++;
            tempVarIndex++;
            break;
        case DIV:
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "div", operandOne.c_str(), operandTwo.c_str(), tempID.c_str());
            printQue.push_back(buffer);
            operandQue.push(tempID);
            lineIndex++;
            tempVarIndex++;
            break;
        case LT:
        case GT:
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "COMP", operandOne.c_str(), operandTwo.c_str(), tempID.c_str());
            printQue.push_back(buffer);
            operandQue.push(tempID);
            lineIndex++;
            tempVarIndex++;

            if (operatorID == GT) {
                jumpSign = "JG";
            }else {
                jumpSign = "JL";
            }
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, jumpSign.c_str(), operandQue.top().c_str(), " ", "$");
            operandQue.pop();
            //printf("%s", buffer);
            printQue.push_back(buffer);
            lineIndex++;
            break;
        case EQUAL:
            sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "assign", operandTwo.c_str(), " ", operandOne.c_str());
            printQue.push_back(buffer);
            lineIndex++;
            break;

        case LTEQ:
        case GTEQ:
            break;
    }

}

void CodeGenerator::PrintStmt() {
    for (deque<string>::iterator it= printQue.begin(); it != printQue.end(); ++it) {
        cout << *it;
    }
    while(!printQue.empty()) {
        printQue.pop_front();
    }

}

void CodeGenerator::WhileReturn() {
    char buffer[100];
    ostringstream convert;
    convert << currentFunction;
    string jumpRe = convert.str();

    sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "JR", " ", " ", jumpRe.c_str());
    printQue.push_back(buffer);
    lineIndex++;

    for (deque<string>::iterator it= printQue.begin(); it != printQue.end(); ++it) {
        ostringstream testNumber;
        string replacement = *it;
        if(replacement[55] == '$') {
            testNumber << lineIndex;

            replacement.replace(54,7, " " + testNumber.str() + "\n");
            printQue.erase(it);
            printQue.insert(it+1, replacement);
            break;
        }
    }



}

void CodeGenerator::FunctionEnd(string id) {
    char buffer[100];

    sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "end", "func", id.c_str(), " ");
    printQue.push_back(buffer);
    lineIndex++;
    PrintStmt();

}

void CodeGenerator::ReturnEval(queue<string> retnQue) {
    queue<string> evalQue;
    bool started = false;
    char buffer[100];

    while(!retnQue.empty()) {
        if(retnQue.front()[0] == '(' && !started) {
            retnQue.pop();
            started = true;
        } else {
            if (retnQue.front()[0] == ')' && started && retnQue.size() == 1) {
                retnQue.pop();
            } else {
                evalQue.push(retnQue.front());
                retnQue.pop();
            }

        }
    }
    Evaluate(evalQue);
    sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "return", " ", " ", operandQue.top().c_str());
    printQue.push_back(buffer);
    operandQue.pop();
    lineIndex++;

}

void CodeGenerator::ArgPrint(queue<string> argQue, int numberOfArgs){

    stack<string> argStack;
    vector<string> args;

    while (!argQue.empty()) {
        argStack.push(argQue.front());
        argQue.pop();
    }

    for (int i = numberOfArgs - 1; i >= 0; i--) {
        args.push_back(argStack.top());
        argStack.pop();
    }
    char buffer[100];
    for (int i = args.size() - 1; i >= 0; i--) {
        sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "arg", " ", " ", args[i].c_str());
        printQue.push_back(buffer);
        lineIndex++;
    }


}

void CodeGenerator::FactorPrint(queue<string> factorQue, int argCount) {
    char buffer[100];
    ostringstream convert;
    convert << tempVarIndex;
    string tempID;
    tempID = "_t" + convert.str();
    string operandOne = factorQue.front().c_str();
    factorQue.pop();
    factorQue.pop();
    string operandTwo = factorQue.front().c_str();
    factorQue.pop();

    sprintf(buffer, "%-9d %-14s %-14s %-14d %-s\n", lineIndex, "call", operandTwo.c_str(), argCount, tempID.c_str());
    printQue.push_back(buffer);
    lineIndex++;
    tempVarIndex++;

    sprintf(buffer, "%-9d %-14s %-14s %-14s %-s\n", lineIndex, "assign", tempID.c_str(), " ", operandOne.c_str());
    printQue.push_back(buffer);
    lineIndex++;
    tempVarIndex++;

}
