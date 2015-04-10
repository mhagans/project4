CFLAGS = -std=c++11

p2: main.o LexicalAnalyzer.o SyntaxAnalyzer.o
	g++ -o p2 main.o LexicalAnalyzer.o SyntaxAnalyzer.o
	
main.o: main.cpp
	g++ -c main.cpp
	
LexicalAnalyzer.o: LexicalAnalyzer.cpp LexicalAnalyzer.hpp
	g++ -c LexicalAnalyzer.cpp

SyntaxAnalyzer.o: SyntaxAnalyzer.cpp SyntaxAnalyzer.hpp
	g++ -c SyntaxAnalyzer.cpp