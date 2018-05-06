//
// Created by McMacker4 on 06/05/2018.
//

#include "Tokenizer.h"

#include <iostream>

namespace Xer { namespace Lex {

    static std::map<char, char> escapes = { // NOLINT
            { 'a', '\a' },
            { 'b', '\b' },
            { 'f', '\f' },
            { 'n', '\n' },
            { 'r', '\r' },
            { 't', '\t' },
            { 'v', '\v' },
            { '\\', '\\' },
            { '\'', '\'' },
            { '"', '\"' },
            { '?', '\?' }
    };

    void IgnoreSpaces(std::ifstream &stream) {
        std::cout << "Ignoring Whitespaces." << std::endl;
        while(isspace(stream.peek()))
            stream.get();
    }

    void ReadName(std::ifstream &stream, std::string &value) {
        assert(isalpha(stream.peek()) || stream.peek() == '_');
        std::cout << "Reading Name" << std::endl;
        while(isalnum(stream.peek()))
            value += (char) stream.get();
    }

    void ReadNumber(std::ifstream &stream, std::string &value) {
        assert(isdigit(stream.peek()));
        std::cout << "Reading Number" << std::endl;
        while(isdigit(stream.peek()))
            value += (char) stream.get();
    }

    void ReadChar(std::ifstream &stream, std::string &value) {
        assert(stream.get() == '\'');
        std::cout << "Reading Char" << std::endl;
        int c = stream.get();
        if(c == '\\')
            c = escapes[stream.get()];
        value += (char) c;
        assert(stream.get() == '\'');
    }

    void ReadString(std::ifstream &stream, std::string &value) {
        assert(stream.get() == '\"');
        std::cout << "Reading String" << std::endl;
        while(stream.peek() != '\"') {
            int c = stream.get();
            if (c == '\\')
                c = escapes[stream.get()];
            value += (char) c;
        }
        assert(stream.get() == '\"');
    }

    Token NextToken(std::ifstream &stream) {
        std::cout << "Reading token." << std::endl;
        std::string value;
        switch(stream.peek()) {
            case 'a': case 'b': case 'c': case 'd': case 'e':
            case 'f': case 'g': case 'h': case 'i': case 'j':
            case 'k': case 'l': case 'm': case 'n': case 'o':
            case 'p': case 'q': case 'r': case 's': case 't':
            case 'u': case 'v': case 'w': case 'x': case 'y':
            case 'z': case 'A': case 'B': case 'C': case 'D':
            case 'E': case 'F': case 'G': case 'H': case 'I':
            case 'J': case 'K': case 'L': case 'M': case 'N':
            case 'O': case 'P': case 'Q': case 'R': case 'S':
            case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z': case '_': {
                ReadName(stream, value);
                return Token { NAME, value };
            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': {
                ReadNumber(stream, value);
                return Token { NUMBER, value };
            }
            case '\'': {
                ReadChar(stream, value);
                return Token { CHARACTER, value };
            }
            case '"': {
                ReadString(stream, value);
                return Token { STRING, value };
            }
            default: {
                int c = stream.get();
                value += (char) c;
                return Token { (TokenType) c, value };
            }
        }
    }

    std::vector<Token> Tokenize(std::ifstream &stream) {
        std::vector<Token> tokens;
        IgnoreSpaces(stream);
        while(!stream.eof()) {
            Token token = NextToken(stream);
            tokens.push_back(token);
            IgnoreSpaces(stream);
        }
        return tokens;
    }

}}