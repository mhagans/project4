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

void CodeGenerator::Evaluate(queue evalQue) {


}
