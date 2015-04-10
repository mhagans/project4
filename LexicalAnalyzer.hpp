#if !defined(_LA_)
#define _LA_

#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

enum {DIGIT, LETTER, KEYWORD, ID, INT, FLOAT, ERROR, SPACE, STOP, SYMBOL, EMPTY};

class LexicalAnalyzer{

public:
    char currentChar;
    int charClass;
    string lexenum;
    string printInput;
    string sKeywords [7];
    bool isFloat;
    stack<int> xComment;
    vector<string> array;

private:
    string input;

public:
    int lex();
    bool isKeyword(string in);
    bool isSymbol();
    void setNewInput(string in);
    LexicalAnalyzer(string in="");
    void linePrint();
    virtual ~LexicalAnalyzer();
    int depth;

private:
    void addChar();
    void getChar();
};

#endif