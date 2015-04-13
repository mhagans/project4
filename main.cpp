#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#if !defined(P1)

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <time.h>
#include "LexicalAnalyzer.hpp"
#include "SyntaxAnalyzer.hpp"

using namespace std;

string tokenConverter(int t);

int main(int argc, char **argv) {
    string filename;
    string fileLine;
   /* time_t startTime;
    time_t endTime;*/

    if(argc < 2){
        cout << "Invalid number of arugments entered"<<endl;
        return 0;
    }else{
        filename = argv[1];
    }

    cout<<"***************** Intermediate Code Generation*****************"<<endl;
    cout<<"---------------------------------------------------------------"<< endl;

    int token = SPACE;


   fstream FILE;
    FILE.open(filename.c_str());
    getline(FILE, fileLine);


   /* time(&startTime);
    cout<<"Start Time: "<< startTime <<endl;*/
    if(FILE.is_open()){
        LexicalAnalyzer LA(fileLine);

        while(token != STOP){
            token = LA.lex();
            if(token == STOP){
            }else{
                /* if(token == ID){
                     cout << tokenConverter(token) <<":\t" <<LA.lexenum<< " DEPTH: " << LA.depth << endl;
                 }else{
                     cout << tokenConverter(token) <<":\t" <<LA.lexenum<< endl;
                 }*/

                stringstream convert;
                convert << token;

                LA.array.push_back(LA.lexenum + " " + convert.str());
            }

        }

        do {
            getline(FILE, fileLine);
            LA.setNewInput(fileLine);
            token = SPACE;

            while(token != STOP){
                token = LA.lex();
                if(token == STOP){
                }else{
                   /* if(token == ID){
                        cout << tokenConverter(token) <<":\t" <<LA.lexenum<< " DEPTH: " << LA.depth << endl;
                    }else{
                        cout << tokenConverter(token) <<":\t" <<LA.lexenum<< endl;
                    }*/

                    stringstream convert;
                    convert << token;


                    LA.array.push_back(LA.lexenum + " " + convert.str());
                }

            }



        }while(!FILE.eof());
        //FILE.close();
       // LA.array.push_back(LA.lexenum + " " + convert.str());

        LA.array.push_back("$");

        /*for (int i = 0; i < LA.array.size(); ++i) {
            cout<< LA.array[i] << endl;
        }*/

        SyntaxAnalyzer SA(LA.array);
        SA.syntax();
       // time(&endTime);
       // cout<<"EndTime: "<< endTime<<endl;
        //cout<<"Total Run Time: "<< difftime(endTime, startTime)<<endl;

    }else{
        cout << "Unable to open " << filename <<endl;
    }


    return 0;
}
string tokenConverter(int t){
    switch (t){
        case SPACE:
            return "SPACE";
        case LETTER:
            return "LETTER";
        case DIGIT:
            return "DIGIT";
        case ID:
            return "ID";
        case INT:
            return "INT";
        case ERROR:
            return "ERROR";
        case STOP:
            return "STOP";
        case FLOAT:
            return "FLOAT";
        case SYMBOL:
            return "SYMBOL";
        case KEYWORD:
            return "KEYWORD";

        default:
            return "UNKOWN";
    }
    return 0;
}


#endif
#pragma clang diagnostic pop