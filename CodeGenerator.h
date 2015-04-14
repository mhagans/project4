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

class CodeGenerator {
public:
    CodeGenerator();
    void FunctionLine(string type, string id, int params);
    void VarAllocation(string id);
    void VarAllocation(string id, string num);
    void printParam();
    void Evaluate(queue evalQue);

private:
    int lineIndex;
    int tempVarIndex;
    vector<string> codeArray;




};


#endif //PROJECT4_CODEGENERATOR_H
