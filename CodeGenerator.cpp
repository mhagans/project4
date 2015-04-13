//
// Created by Marcus on 4/12/2015.
//

#include "CodeGenerator.h"
#include <iostream>
#include <string>

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
