cmake_minimum_required(VERSION 3.1)
project(Project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp )
add_executable(Project4 ${SOURCE_FILES} LexicalAnalyzer.cpp SyntaxAnalyzer.cpp CodeGenerator.cpp CodeGenerator.h)