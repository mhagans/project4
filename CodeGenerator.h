//
// Created by Marcus on 4/12/2015.
//

#ifndef PROJECT4_CODEGENERATOR_H
#define PROJECT4_CODEGENERATOR_H

#include <iostream>
#include <string>
#include "LexicalAnalyzer.hpp"
#include "cstdlib"
#include <vector>
#include <queue>
#include <deque>

using  namespace std;

enum{PLUS, SUB, MULT, DIV, GT, LT, GTEQ, LTEQ, EQUAL, ISEQUAL, NTEQ, ARRAY};

class CodeGenerator {
public:
    CodeGenerator();
    void FunctionLine(string type, string id, int params);
    void FunctionEnd(string id);
    void VarAllocation(string id);
    void VarAllocation(string id, string num);
    void printParam();
    void Evaluate(queue<string> evalQue);
    void ReturnEval(queue<string> retnQue);
    void ArithimiticFunction(string operandOne, string operandTwo, int operatorID);
    void PrintStmt();
    void WhileReturn();
    void IfFunction();
    void ElseFunction();
    void ArgPrint(queue<string> argQue, int numberOfArgs);
    void FactorPrint(queue<string> factorQue, int argCount);
    int currentFunction;
    int lineIndex;
    string currentFunctionID;
    bool inIfStmt;
    bool inElseStmt;
    int ifJumpValue;

private:

    int tempVarIndex;
    int *jumpPointer;


    deque<string> printQue;
    stack<string> operandQue;
    stack<string> operatorQue;

};


#endif //PROJECT4_CODEGENERATOR_H
