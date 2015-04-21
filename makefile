CFLAGS = -std=c++11

p4: main.o LexicalAnalyzer.o SyntaxAnalyzer.o CodeGenerator.o
	g++ -o p4 main.o LexicalAnalyzer.o CodeGenerator.o SyntaxAnalyzer.o
	
main.o: main.cpp
	g++ -c main.cpp
	
CodeGenerator.o: CodeGenerator.cpp 
	g++ -c CodeGenerator.cpp
	
LexicalAnalyzer.o: LexicalAnalyzer.cpp LexicalAnalyzer.hpp
	g++ -c LexicalAnalyzer.cpp

SyntaxAnalyzer.o: SyntaxAnalyzer.cpp SyntaxAnalyzer.hpp
	g++ -c SyntaxAnalyzer.cpp

