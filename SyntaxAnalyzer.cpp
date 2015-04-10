#include "SyntaxAnalyzer.hpp"
#include <iostream>
#include <vector>
#include <sstream>


//using namespace std;

SyntaxAnalyzer::SyntaxAnalyzer(vector<string> input) {
    exitString  = "Incorrect Syntax Exiting Program Current Token: " + currentToken;
    tokenArray = input;
    index = 0;
    exitString = "Incorrect Syntax Exiting Program CURRENT TOKEN: " + currentToken;

    for (int i = 0; i < tokenArray.size(); ++i) {
        cout << tokenArray[i] << endl;
    }
}

SyntaxAnalyzer::~SyntaxAnalyzer() {
}

void SyntaxAnalyzer::setNewInput(string in) {


}

void SyntaxAnalyzer::syntax() {
    Splitter();
    program();

    if(currentToken =="$"){
        cout << "Syntax is correct" <<endl;
    }else {
        cout << "Failed to compile at Token: " << currentToken << endl;
    }

}

void SyntaxAnalyzer::program(){
    //cout << "inside program call"<< endl;
    declarationList();

}

void SyntaxAnalyzer::declarationList(){
   // cout << "inside declarationList call"<< endl;
    declaration();
    if (currentClass == EMPTY) {
        FailExit();

    }
    declarationListPrime();
    if (currentClass == EMPTY){
        ;
    }
    //cout <<"LEAVING DECLARATIONLIST CALL"<<endl;
    //TokenStmt();
}

void SyntaxAnalyzer::declaration(){
   // cout<<"inside declaration call"<<endl;
   // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
    typeSpecific();
    if (currentClass != EMPTY) {
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        if(currentClass == ID) {
           // cout<< "inside declaratoin ID check"<<endl;
            Splitter();
           // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            declarationPrime();
        }else {
            //cout<<"inside declartion fail ID check"<<endl;
            FailExit();
        }
    }
   // cout<<"LEAVING DECLARATION CALL"<<endl;
    //TokenStmt();
}

void SyntaxAnalyzer::declarationListPrime(){
   // cout<<"inside declarationListPrime call"<<endl;
    tempToken = currentToken;
    tempClass = currentClass;

    declaration();
    if (currentClass == EMPTY) {
        currentClass = tempClass;
        currentToken = tempToken;

    }else {
        declarationListPrime();
    }
   // cout<<"LEAVING DECLARATIONLISTPRIME CALL"<<endl;
}

void SyntaxAnalyzer::declarationPrime() {
   // cout<<"inside declarationPrime call"<<endl;
    declarationPrimeFactor();
    if (currentClass == EMPTY) {
        currentClass = tempClass;
        currentToken = tempToken;
        if (currentToken == "(") {
            Splitter();
            params();
            if (currentToken == ")") {
                Splitter();
                compoundStmt();
            }
        }else {
            FailExit();
        }
    }
   // cout<<"LEAVING DECLARATIONPRIME CALL"<<endl;

}

void SyntaxAnalyzer::declarationPrimeFactor() {
    /*cout<< "inside declarationPrimeFactor"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if (currentToken == ";") {
        Splitter();
    }else{
        //cout <<"inside declarationPrimeFactor else statement"<<endl;
        if(currentToken == "[") {
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            if (currentClass == INT) {
                //cout << "inside declarationPrimeFactor NUM check"<<endl;
                Splitter();
                if (currentToken == "]") {
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    Splitter();
                    if (currentToken == ";") {
                       // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                        Splitter();
                       // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    }else {
                        FailExit();
                    }
                } else {
                    FailExit();
                }
            } else {
                FailExit();
            }
        } else {
            tempToken = currentToken;
            tempClass = currentClass;
            currentClass = EMPTY;
        }
    }
    //cout<<"LEAVING DECLARATOINPRIMEFACTOR CALL"<<endl;
   // TokenStmt();

}

void SyntaxAnalyzer::typeSpecific(){
    /*cout << "inside typeSpecific call"<<endl;

    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if(currentToken == "int"){
       // cout<< "inside typeSpecific  int if statement"<<endl;
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
    }else {
        if(currentToken == "float") {
           // cout<< "inside typeSpecific float if statement"<<endl;
            Splitter();
           // cout <<"tokens: " << currentToken << " " <<currentClass<< endl;
        } else {
            if(currentToken == "void") {
               // cout<< "inside typeSpecific void if statement"<<endl;
                Splitter();
               // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            }else {
                // Set Empty variable
               // cout<<"inside typeSpecific fail else statement"<<endl;
               // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                isEmpty();
            }
        }

    }
    //cout<<"leaving TYPESPECIFIC CALL"<<endl;

}

void SyntaxAnalyzer::params() {
    /*cout <<"inside params call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if (currentToken == "int") {
        Splitter();
        if (currentClass == ID) {
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            paramPrime();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            paramListPrime();
            if (currentClass == EMPTY) {
                currentClass = tempClass;
                currentToken = tempToken;
            }
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;

        } else {
            FailExit();
        }
    }else {
        if (currentToken=="void") {
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            paramsPrime();
           // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

        }else {
            if(currentToken == "float") {
                if (currentClass == ID) {
                    Splitter();
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    paramPrime();
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
                    paramListPrime();
                    if (currentClass == EMPTY) {
                        currentClass = tempClass;
                        currentToken = tempToken;
                    }
                    //cout <<"tokens: " << currentToken << " " << currentClass<< endl;

                } else {
                    FailExit();
                }
            }
        }
    }
}

void SyntaxAnalyzer::paramsPrime(){
    /*cout <<"inside paramsPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/

    if(currentClass == ID) {
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        paramPrime();
       // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        paramListPrime();
        if (currentClass == EMPTY) {
            currentClass = tempClass;
            currentToken = tempToken;
        }
       // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

    }

}

void SyntaxAnalyzer::paramListPrime(){
    /*cout << "inside paramListPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if (currentToken == ",") {
        Splitter();
       // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        param();
        if (currentClass == EMPTY) {
            FailExit();
        }else {
            paramListPrime();
            if (currentClass == EMPTY) {
                currentClass = tempClass;
                currentToken = tempToken;
            }
        }
    }else{
        tempClass = currentClass;
        tempToken = currentToken;
        currentClass = EMPTY;
    }

}

void SyntaxAnalyzer::param(){
    /*cout <<"inside Param call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    typeSpecific();
    if (currentClass != EMPTY) {
        if (currentClass == ID) {
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            Splitter();
           // cout <<"tokens: " << currentToken << " " << currentClass<< endl;

        }else {
            FailExit();

        }
    }


}

void SyntaxAnalyzer::paramPrime(){
    /*cout << "inside paramPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if(currentToken =="[") {
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        if (currentToken =="]") {
            Splitter();
        } else {
            FailExit();
        }
    }

}

void SyntaxAnalyzer::compoundStmt(){
    /*cout << "inside compoundStmt call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    if (currentToken == "{") {
        Splitter();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        localDeclarationsPrime();
       // cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        EmptyCheck();
        //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
        statementListPrime();
        EmptyCheck();
        // Need to check if empty is ok for statementLIst
        if (currentToken == "}") {
            Splitter();
           // TokenStmt();
        }else {
            FailExit();
        }
    }else {
        isEmpty();
    }

}
// May be able to Delete this Method
void SyntaxAnalyzer::localDeclarations(){
    localDeclarationsPrime();

}

void SyntaxAnalyzer::localDeclarationsPrime(){
    //cout<<"inside localDeclarationsPrime call"<<endl;

    typeSpecific();
    if (currentClass != EMPTY) {
        if (currentClass == ID) {
            Splitter();
            //cout <<"tokens: " << currentToken << " " << currentClass<< endl;
            declarationPrimeFactor();
            if (currentClass == EMPTY) {
                FailExit();
            }
            localDeclarationsPrime();
            EmptyCheck();
        }else {
            FailExit();
        }
    }
    //cout<<"LEAVING LOCALdECLARATIONSpRIME"<<endl;

}
// May be able to Delete this Method
void SyntaxAnalyzer::statementList(){

}

void SyntaxAnalyzer::statementListPrime(){
   /* cout<<"inside statementListPrime call"<<endl;
    cout <<"tokens: " << currentToken << " " << currentClass<< endl;*/
    statement();
    if (currentClass != EMPTY) {
        statementListPrime();
        EmptyCheck();
    }else {
        EmptyCheck();
    }


   //cout<<"LEAVING STATEMENTLISTPrime"<<endl;
}

void SyntaxAnalyzer::statement(){
    //cout<<"inside statement call"<<endl;
   // TokenStmt();
    expressionStmt();
    if (currentClass == EMPTY) {
        EmptyCheck();
        compoundStmt();
        if (currentClass == EMPTY) {
            EmptyCheck();
            selectionStmt();
            if (currentClass == EMPTY) {
                EmptyCheck();
                iterationStmt();
                if (currentClass == EMPTY) {
                    EmptyCheck();
                    returnStmt();

                }
            }
        }
    }
    //cout<<"LEAVING STATEMENT CALL"<<endl;
}

void SyntaxAnalyzer::expressionStmt(){
   /* cout<<"inside expressionStmt call"<<endl;
    TokenStmt();*/
    expression();
    if (currentClass != EMPTY) {
        if (currentToken == ";") {
           // TokenStmt();
            Splitter();
           // TokenStmt();
        }
    }else {
        EmptyCheck();
        if (currentToken == ";") {
           // TokenStmt();
            Splitter();
           // TokenStmt();
        }else {
            isEmpty();
        }
    }
   // cout<<"LEAVING EXPRESSIONSTMT"<<endl;

}

void SyntaxAnalyzer::selectionStmt(){
    //cout<<"inside selectionStmt call"<<endl;
   // TokenStmt();
    if (currentToken == "if") {
        Splitter();
       // TokenStmt();
        if (currentToken == "(") {
            Splitter();
          //  TokenStmt();
            expression();
           // cout<<"PASSED EXPRESSION IN SELECTIONSTMT"<<endl;
            //TokenStmt();
            if (currentClass != EMPTY) {
                //cout<<"CHECKING FOR  ) "<<endl;
                if (currentToken == ")") {
                   // cout<<"CHECKING FOR )"<<endl;
                    Splitter();
                   // TokenStmt();
                    statement();
                   // cout<<"CHECKING TO SEE IF EMPTY OR ELSE IS HERE"<<endl;
                   // TokenStmt();
                    if (currentClass == EMPTY) {
                        FailExit();
                    }else {
                        selectionStmtPrime();
                        EmptyCheck();
                    }
                }
            }else {
                FailExit();
            }
        }else {
            FailExit();
        }

    }else {
        isEmpty();
    }
    /*cout<<"LEAVING SELECTIONSTMT"<<endl;
    TokenStmt();*/

}

void SyntaxAnalyzer::selectionStmtPrime(){
    /*cout << "inside selectionStmtPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == "else") {
        Splitter();
       // TokenStmt();
        statement();
        if (currentClass == EMPTY) {
            FailExit();
        }
    }else {
        isEmpty();
    }
    /*cout<<"LEAVING SELECTIONSTMTPRIME"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::iterationStmt(){
    /*cout<<"inside iteratoinStmt call"<<endl;
    TokenStmt();*/
    if (currentToken == "while") {
        Splitter();
       // TokenStmt();
        if (currentToken == "(") {
            Splitter();
           // TokenStmt();
            expression();
            if (currentClass != EMPTY) {
                if (currentToken == ")") {
                    Splitter();
                   // TokenStmt();
                    statement();
                    EmptyCheck();
                } else {
                    FailExit();
                }
            }
            else {
                FailExit();
            }

        }
    }else {
        isEmpty();
    }
   // cout<<"LEAVING ITERATIONsTMT"<<endl;
}

void SyntaxAnalyzer::returnStmt(){
    /*cout<<"inside returnStmt call"<<endl;
    TokenStmt();*/
    if (currentToken == "return") {
        Splitter();
       // TokenStmt();
        returnStmtPrime();
        if (currentClass == EMPTY) {
            FailExit();
        }

    }else {
        isEmpty();
    }
    //cout<<"LEAVING RETURNSTMT"<<endl;
   // TokenStmt();
}

void SyntaxAnalyzer::returnStmtPrime(){
    /*cout<<"inside returnStmtPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == ";") {
        Splitter();
       // TokenStmt();

    } else {
        expression();
        //cout<<"CHECK TO SEE IF RETURNSTMTPRIME CAN MOVE"<<endl;
        //TokenStmt();
        if (currentToken == ";") {
            Splitter();
            //TokenStmt();
        }else {
            FailExit();
        }
    }

    /*cout<<"LEAVING RETURNSTMTPRIME"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::expression() {
   // cout<<"inside expression Call"<<endl;

    if (currentClass == ID) {
        /*cout<<"INSIDE EXPRESSION id CHECK"<<endl;
        TokenStmt();*/
        Splitter();
        //TokenStmt();
        expressionFactor();
        //TokenStmt();
        EmptyCheck();

    }else {
        if (currentToken == "(") {
           // TokenStmt();
            Splitter();
            expression();
            if (currentClass == EMPTY) {
                FailExit();
            }else {
                if (currentToken == ")") {
                    Splitter();
                    //TokenStmt();
                    termPrime();
                    EmptyCheck();
                    additiveExpressionPrime();
                    EmptyCheck();
                    simpleExpressionPrime();
                    EmptyCheck();

                }
            }
        }else {
            if (currentClass == INT) {
                Splitter();
                //TokenStmt();
                termPrime();
                EmptyCheck();
                additiveExpressionPrime();
                EmptyCheck();
                simpleExpressionPrime();
                EmptyCheck();

            }else {
                if (currentClass == FLOAT) {
                    Splitter();
                    //TokenStmt();
                    termPrime();
                    EmptyCheck();
                    additiveExpressionPrime();
                    EmptyCheck();
                    simpleExpressionPrime();
                    EmptyCheck();

                }else {
                    isEmpty();
                }

            }
        }
    }
    /*cout<<"leaving expression"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::expressionFactor(){
    //cout<<"inside expressionFactor call"<< endl;
    expressionPrime();
    EmptyCheck();
    if (currentToken == "=") {
        Splitter();
       // TokenStmt();
        expression();
        if (currentClass == EMPTY) {
            FailExit();
        }

    }else {
        factorPrime();
        EmptyCheck();
        termPrime();
        EmptyCheck();
        additiveExpressionPrime();
        EmptyCheck();
        simpleExpressionPrime();
        EmptyCheck();
    }
    /*cout<<"leaving expressionFactor"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::expressionPrime(){
    /*cout<<"inside expressionPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == "[") {
        Splitter();
       // TokenStmt();
        expression();
        if (currentClass == EMPTY) {
            FailExit();
        }else {
            if (currentToken == "]") {
                Splitter();
                //TokenStmt();
            } else {
                FailExit();
            }
        }
    }else {
        isEmpty();
    }

}

void SyntaxAnalyzer::simpleExpressionPrime(){
    /*cout<<"inside simpleExpressionPrime()"<<endl;
    TokenStmt();*/
    relop();
    if (currentClass != EMPTY) {
        //cout<<"inside simpleExpressionPrime EMPTY"<<endl;
        additiveExpression();
       // cout<<"passed additiveExpression in simpleExpression"<<endl;
        //TokenStmt();
        EmptyCheck();
        //cout<<"checking tokens after additive"<<endl;
        //TokenStmt();
        if (currentClass == EMPTY) {
            //cout<<"inside simpeleExpressionPrime Fail"<<endl;
            FailExit();
        }
    }/*else {
        cout<<"CHECKING<<<<<<<<"<<endl;
       // TokenStmt();
        isEmpty();
       // TokenStmt();
    }*/
    /*cout<<"leaving simpleExpressionPrime"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::relop() {
    /*cout<<"inside relop call"<<endl;
    TokenStmt();*/
    if (currentToken == "<=") {
        Splitter();
        //TokenStmt();

    }else {
        if (currentToken == "<") {
            Splitter();
            //TokenStmt();

        }else {
            if (currentToken == ">") {
                Splitter();
                //TokenStmt();

            }else {
                if (currentToken == ">=") {
                    Splitter();
                    //TokenStmt();

                }else {
                    if (currentToken == "==") {
                        Splitter();
                        //TokenStmt();

                    }else {
                        if (currentToken == "!=") {
                            Splitter();
                            //TokenStmt();

                        }else {
                            isEmpty();
                        }
                    }
                }
            }

        }
    }
    /*cout<<"leaving relop call"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::additiveExpression(){
    /*cout<<"inside additiveExpression Call"<<endl;
    TokenStmt();*/
    term();
    if (currentClass != EMPTY) {
        //cout<<"inside additiveExpression EMPTY check"<<endl;
        additiveExpressionPrime();
       //cout<<"Passed addtiiveExpressionPrime in addtiveExpression"<<endl;
        EmptyCheck();
    }
    /*cout<<"LEAVING ADDITIVEEXPRESSION"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::additiveExpressionPrime(){
    /*cout<<"inside additiveExpressionPrime call"<<endl;
    TokenStmt();*/
    addop();
    if (currentClass != EMPTY) {
       // cout<<"inside additiveExpressionPrime empty check"<<endl;
        term();
        if (currentClass != EMPTY) {
            additiveExpressionPrime();
           // cout<<"inside additiveExpressionPrime term check"<<endl;
            EmptyCheck();
        }else {
           // cout<<"inside additiveExpression Fail check"<<endl;
            //FailExit();
        }
    }
    /*cout<<"leaving additiveExpressionPrime"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::addop(){
   /* cout<<"inside addop call"<<endl;
    TokenStmt();*/
    if (currentToken == "+") {
        Splitter();
        //TokenStmt();
    }else {
        if (currentToken == "-") {
            Splitter();
            //TokenStmt();
        }else {
            /*cout<<"inside empty of addop"<<endl;
            TokenStmt();*/
            isEmpty();
          //  TokenStmt();
        }
    }
    /*cout<<"leaving addop"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::term(){
    /*cout<<"inside term call"<<endl;
    TokenStmt();*/
    factor();
    if (currentClass != EMPTY) {
        termPrime();
        EmptyCheck();
    }else {
        FailExit();
    }
    /*cout<<"leaving term()"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::termPrime(){
    /*cout<<"inside termPrime"<<endl;
    TokenStmt();*/
    mulop();
    if (currentClass != EMPTY) {
       // TokenStmt();
        factor();
        if (currentClass != EMPTY) {
           // TokenStmt();
            termPrime();
            EmptyCheck();
        }else {
            FailExit();
        }
    }
   /* cout<<"leaving termPrime"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::mulop(){
    /*cout<<"inside mulop call"<<endl;
    TokenStmt();*/
    if (currentToken == "*") {
        Splitter();
       // TokenStmt();
    }else {
        if (currentToken == "/") {
            Splitter();
            //TokenStmt();
        } else {
            isEmpty();
        }
    }
   /* cout<<"leaving mulop"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::factor(){
    /*cout<<"inside factor call"<<endl;
    TokenStmt();*/
    if (currentToken == "(") {
       // cout<<"inside factor ( if statement"<<endl;
        Splitter();
        //TokenStmt();
        expression();
        if (currentClass == EMPTY) {
            FailExit();
        }else {
            if (currentToken == ")") {
                //cout<<"inside factor ) if statement"<<endl;
                Splitter();
                //TokenStmt();
            }else {
                FailExit();
            }
        }
    }else {
        if (currentClass == INT) {
            Splitter();
            //TokenStmt();
        }else {
            if (currentClass == FLOAT) {
                Splitter();
                //TokenStmt();
            }else {
                if (currentClass == ID) {
                    Splitter();
                   // TokenStmt();
                    factorPrime();
                    EmptyCheck();
                }else{
                    isEmpty();
                }
            }
        }
    }
    /*cout<<"LEAVING FACTOR"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::factorPrime(){
    /*cout<<"inside factorPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == "(") {
        Splitter();
      //  TokenStmt();
        args();

        if (currentToken == ")") {
            Splitter();
          //  TokenStmt();
        }
    }else {
        expressionPrime();
        EmptyCheck();

    }
    /*cout<<"LEAVING FACTORPRIME"<<endl;
    TokenStmt();*/
}

void SyntaxAnalyzer::args(){
    /*cout<<"inside args call"<<endl;
    TokenStmt();*/
    expression();
    if (currentClass != EMPTY) {
        argsPrime();
        EmptyCheck();
    }
    //cout<<"leaving args call"<<endl;
}

void SyntaxAnalyzer::argsPrime(){
    /*cout<<"inside argsPrime call"<<endl;
    TokenStmt();*/
    if (currentToken == ",") {
        Splitter();
        expression();
       // TokenStmt();
        if (currentClass == EMPTY) {
            FailExit();
        }
        argsPrime();
        EmptyCheck();
    }else {
        isEmpty();
    }
    //cout<<"leaving argsPrime"<<endl;
}

void SyntaxAnalyzer::Splitter() {
    string buf;
    stringstream ss(tokenArray[index]);
    vector<string> splitToken;



    while (ss >> buf) {
        splitToken.push_back(buf);
    }

    if (splitToken.size()> 1) {
        stringstream convert(splitToken[1]);
        currentToken = splitToken[0];
        convert >> currentClass;
        //cout << "Split Tokens: " << currentToken << " " << currentClass <<endl;
    } else {
        currentToken = splitToken[0];

    }
    index++;
}

void SyntaxAnalyzer::FailExit() {
    cout << exitString << endl;
    exit(1);
}

void SyntaxAnalyzer::EmptyCheck() {
    if (currentClass == EMPTY) {
        currentClass = tempClass;
        currentToken = tempToken;
    }
}

void SyntaxAnalyzer::TokenStmt() {
    cout <<"tokens: " << currentToken << " " << currentClass << endl;
}

void SyntaxAnalyzer::isEmpty() {
    tempToken = currentToken;
    tempClass = currentClass;
    currentClass = EMPTY;
}