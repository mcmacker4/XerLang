cmake_minimum_required(VERSION 3.6)
project(XerInterpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(XerInterpreter Source/Main.cpp Source/lex/Tokenizer.cpp Source/lex/Tokenizer.h Source/err/Exceptions.h)