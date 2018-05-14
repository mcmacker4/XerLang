#include "AST.h"
#include "../Constants.h"

namespace Xer { namespace Parser {

    String ExpectToken(std::deque<Lex::Token> &tokens, Lex::TokenType type) {
        auto token = tokens.front();
        if(token.type != type) {
            std::stringstream stream;
            stream << "Expected " << Lex::TokenTypeToName(type) << " but got '" << token.value << "'.";
            throw SyntaxError(stream.str());
        }
        tokens.pop_front();
        return token.value;
    }

    String ExpectToken(std::deque<Lex::Token> &tokens, String keyword) {
        auto token = tokens.front();
        if(token.type != Lex::KEYWORD || token.value != keyword) {
            std::stringstream stream;
            stream << "Expected '" << keyword << "' but got '" << token.value << "'.";
            throw SyntaxError(stream.str());
        }
        tokens.pop_front();
        return token.value;
    }

    VarType ToType(String str) {
        static String types[] = {
                "INT",
                "CHAR",
                "STRING"
        };
        for(int i = 0; i <= STRING; i++) {
            if(str == types[i])
                return (VarType) i;
        }
        std::stringstream stream;
        stream << "Invalid type '" << str << "'";
        throw SyntaxError(stream.str());
    }

    VarType ReadTypeSpecifier(std::deque<Lex::Token> &tokens) {
        //Expect ':'
        ExpectToken(tokens, (Lex::TokenType) ':');
        //Expect keyword
        auto type = ExpectToken(tokens, Lex::KEYWORD);
        //Convert string to actual type
        return ToType(type);
    }

    Node *ReadVarDeclaration(std::deque<Lex::Token> &tokens) {
        //Consume 'var' token
        tokens.pop_front();
        //Expect a name
        if(!tokens.front().type != Lex::NAME) {
            std::string message = "Expected a name, got ";
            message += tokens.front().value.CStr();
            throw SyntaxError(message);
        }
        //Get name
        String &name = tokens.front().value;
        tokens.pop_front();
        //Expect a type specifier
        VarType type = ReadTypeSpecifier(tokens);
        //Read optional assignment.
        if(tokens.front().type == Lex::OPERATOR) {
            //TODO: Read expression after assignment operator
        } else {
            ExpectToken(tokens, (Lex::TokenType) ';');
        }
    }

    Node *ReadStatement(std::deque<Lex::Token> &tokens) {
        auto token = tokens.front();
        //Check what's coming
        if(token.type == Lex::KEYWORD && token.value == Const::Keywords::VAR) {
            //Read var declaration
            return ReadVarDeclaration(tokens);
        }
        //TODO: Other two options: expression or assignment
    }

    AST Parse(std::deque<Lex::Token> &tokens) {
        AST ast;
    }

}}
