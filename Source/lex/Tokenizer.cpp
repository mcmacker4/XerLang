//
// Created by McMacker4 on 06/05/2018.
//

#include "Tokenizer.h"

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

    std::vector<char> operators = { // NOLINT
            // IMPORTANT TO KEEP ASCII VALUE SORTED
            '!', '%', '&', '*', '+', '-', '/', '<', '=', '>', '^', '|'
    };

    int IgnoreSpaces(std::string &line, int pos) {
        while(isspace(line[pos]))
            pos++;
        return pos;
    }

    bool IsOperator(char c) {
        return Util::BinSearchChar(operators, c) >= 0;
    }

    int ReadOperator(std::string &line, int pos, std::string &value) {
        while(pos < line.length() && IsOperator(line[pos]))
            value += line[pos++];
        return pos;
    }

    int ReadName(std::string &line, int pos, std::string &value) {
        assert(isalpha(line[pos]) || line[pos] == '_');
        while(line[pos] == '_' || isalnum(line[pos]))
            value += line[pos++];
        return pos;
    }

    int ReadNumber(std::string &line, int pos, int ln, std::string &value) {
        assert(isdigit(line[pos]) || line[pos] == '.');
        bool decimalPoint = false;
        while(pos < line.length() && (isdigit(line[pos]) || line[pos] == '.')) {
            if(line[pos] == '.') {
                if(decimalPoint)
                    throw Err::UnexpectedTokenException(line[pos], ln, pos + 1);
                decimalPoint = true;
            }
            value += line[pos++];
        }
        return pos;
    }

    int ReadChar(std::string &line, int pos, int ln, std::string &value) {
        assert(line[pos] == '\'');
        pos++;
        char c = line[pos++];
        if(c == '\\') {
            try {
                c = escapes.at(line[pos++]);
            } catch (std::out_of_range &ex) {
                throw Err::UnexpectedTokenException(line[pos], ln, pos + 1);
            }

        }
        value += c;
        assert(line[pos] == '\'');
        return ++pos;
    }

    int ReadString(std::string &line, int pos, int ln, std::string &value) {
        assert(line[pos] == '\"');
        pos++;
        while(pos < line.length() && line[pos] != '\"') {
            char c = line[pos++];
            if (c == '\\') {
                try {
                    c = escapes.at(line[pos++]);
                } catch(std::out_of_range &err) {
                    throw Err::UnexpectedTokenException(line[pos], ln, pos + 1);
                }
            }
            value += c;
        }
        assert(line[pos] == '\"');
        return ++pos;
    }

    int NextToken(std::string &line, int pos, int ln, Token &outToken) {
        std::string value;
        switch(line[pos]) {
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
                pos = ReadName(line, pos, value);
                outToken = { NAME, value };
                break;
            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case '.': {
                pos = ReadNumber(line, pos, ln, value);
                outToken = { NUMBER, value };
                break;
            }
            case '!': case '%': case '&': case '*': case '+': case '-':
            case '/': case '<': case '=': case '>': case '^': case '|': {
                pos = ReadOperator(line, pos, value);
                outToken = { OPERATOR, value };
                break;
            }
            case '\'': {
                pos = ReadChar(line, pos, ln, value);
                outToken = { CHARACTER, value };
                break;
            }
            case '"': {
                pos = ReadString(line, pos, ln, value);
                outToken = { STRING, value };
                break;
            }
            default: {
                int c = line[pos++];
                value += (char) c;
                outToken = { (TokenType) c, value };
                break;
            }
        }
        return pos;
    }

    std::vector<Token> Tokenize(std::ifstream &stream) {
        std::string line;
        Token token;
        std::vector<Token> tokens;
        int ln = 0;
        while(!stream.eof()) {
            std::getline(stream, line);
            int pos = IgnoreSpaces(line, 0);
            ln++;
            while(pos < line.length()) {
                pos = NextToken(line, pos, ln, token);
                tokens.push_back(token);
                if(pos < line.length())
                    pos = IgnoreSpaces(line, pos);
            }
        }
        return tokens;
    }

}}