#if !defined(_SA_)
#define _SA_

#include <iostream>
#include <string>
#include "LexicalAnalyzer.hpp"
#include "CodeGenerator.h"
#include "cstdlib"
#include <vector>



class SyntaxAnalyzer {
    public:
    void syntax();
    void setNewInput(string in);
    SyntaxAnalyzer(vector<string> input);
    virtual ~SyntaxAnalyzer();
    int index;
    vector<string> tokenArray;
    string currentToken;
    string tempToken;
    int tempClass;
    int currentClass;
    string exitString;





    private:
    void program();
    void declarationList();
    void declarationListPrime();
    void declaration();
    void declarationPrime();
    void declarationPrimeFactor();
    void typeSpecific();
    void params();
    void paramsPrime();
    void paramListPrime();
    void param();
    void paramPrime();
    void compoundStmt();
    void localDeclarations();
    void localDeclarationsPrime();
    void statementList();
    void statementListPrime();
    void statement();
    void expressionStmt();
    void selectionStmt();
    void selectionStmtPrime();
    void iterationStmt();
    void returnStmt();
    void returnStmtPrime();
    void expression();
    void expressionFactor();
    void expressionPrime();
    void simpleExpressionPrime();
    void relop();
    void additiveExpression();
    void additiveExpressionPrime();
    void addop();
    void term();
    void termPrime();
    void mulop();
    void factor();
    void factorPrime();
    void args();
    void argsPrime();
    void Splitter();

    void FailExit();

    void EmptyCheck();

    void TokenStmt();

    void isEmpty();
};

#endif