//
// Created by McMacker4 on 06/05/2018.
//

#include "Tokenizer.h"
#include "../Constants.h"

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

    void IgnoreSpaces(std::string &line, int &pos) {
        while(isspace(line[pos]))
            pos++;
    }

    bool IsOperatorChar(char c) {
        for(auto op : Const::opChars) {
            if(c == op)
                return true;
        }
        return false;
    }

    bool IsKeyword(String str) {
        for(auto kw : Const::keywordList) {
            if(str == kw)
                return true;
        }
        return false;
    }

    void ReadOperator(std::string &line, int &pos, std::string &value) {
        while(pos < line.length() && IsOperatorChar(line[pos]))
            value += line[pos++];
    }

    void ReadName(std::string &line, int &pos, std::string &value) {
        assert(isalpha(line[pos]) || line[pos] == '_');
        while(line[pos] == '_' || isalnum(line[pos]))
            value += line[pos++];
    }

    void ReadNumber(std::string &line, int &pos, int ln, std::string &value) {
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
    }

    void ReadChar(std::string &line, int &pos, int ln, std::string &value) {
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
        ++pos;
    }

    void ReadString(std::string &line, int &pos, int ln, std::string &value) {
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
        ++pos;
    }

    Token NextToken(std::string &line, int &pos, int ln) {
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
                ReadName(line, pos, value);
                String str = String(value);
                return Token { IsKeyword(str) ? KEYWORD : NAME, str };
            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': {
                ReadNumber(line, pos, ln, value);
                return Token { NUMBER, String(value) };
            }
            case '!': case '%': case '&': case '*': case '+': case '-':
            case '/': case '<': case '=': case '>': case '^': case '|': {
                ReadOperator(line, pos, value);
                return Token { OPERATOR, String(value) };
            }
            case '\'': {
                ReadChar(line, pos, ln, value);
                return Token { CHARACTER, String(value) };
            }
            case '"': {
                ReadString(line, pos, ln, value);
                return Token { STRING, String(value) };
            }
            default: {
                int c = line[pos++];
                value += (char) c;
                return Token { (TokenType) c, String(value) };
            }
        }
    }

    std::deque<Token> Tokenize(std::ifstream &stream) {
        std::string line;
        std::deque<Token> tokens;
        int ln = 0;
        while(!stream.eof()) {
            int pos = 0;
            std::getline(stream, line);
            IgnoreSpaces(line, pos);
            ln++;
            while(pos < line.length()) {
                Token token = NextToken(line, pos, ln);
                tokens.push_back(token);
                if(pos < line.length())
                    IgnoreSpaces(line, pos);
            }
        }
        return tokens;
    }

    String TokenTypeToName(TokenType type) {
        static String strings[] = {
                "NAME",
                "KEYWORD",
                "NUMBER",
                "CHARACTER",
                "STRING",
                "OPERATOR"
        };
        if(type < NAME)
            return String(std::to_string((char) type));
        else
            return strings[type - NAME];
    }

}}