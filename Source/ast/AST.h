#ifndef XERINTERPRETER_AST_H
#define XERINTERPRETER_AST_H

#include "../util/String.h"
#include "../lex/Tokenizer.h"

using namespace Util;

namespace Xer { namespace Parser {

    enum NodeType {
        UNARY_OPERATION,
        BINARY_OPERATION,
        VAR_DECLARATION,
        ASSIGNMENT,
        VALUE
    };

    enum VarType {
        INT,
        CHAR,
        STRING
    };

    enum Operator {
        //L0
        OR,
        //L1
        AND,
        //L2
        EQ, NEQ, LT, LET, GT, GET,
        //L3
        ADD, SUB, BIT_OR, BIT_XOR,
        //L4
        MUL, DIV, MOD, LSHIFT, RSHIFT, BIT_AND
    };

    struct Node {
        NodeType type;
        explicit Node(NodeType type) : type(type) {}
    };

    struct Statement : public Node {
        explicit Statement(NodeType type) : Node(type) {}
    };

    struct Expression : public Statement {
        explicit Expression(NodeType type) : Statement(type) {}
    };
    struct UnaryOperation : public Expression {
        explicit UnaryOperation() : Expression(UNARY_OPERATION) {}
    };
    struct BinaryOperation : public Expression {
        explicit BinaryOperation() : Expression(BINARY_OPERATION) {}
    };
    struct Value : public Expression {
        String value;
        explicit Value(String value) : Expression(VALUE), value(value) {}
    };

    struct VarDeclaration : public Statement {
        VarType type;
        String name;
        Expression* value;
        VarDeclaration(VarType type, String name, Expression *value)
                : Statement(VAR_DECLARATION), type(type), name(name), value(value) {}
    };

    struct Assignment : public Statement {
        String name;
        Expression* value;
        Assignment(String name, Expression *value)
                : Statement(ASSIGNMENT), name(name), value(value) {}
    };

    struct AST {
        std::vector<Node> nodes;
    };

    AST Parse(std::deque<Lex::Token> tokens);

    class SyntaxError : public std::exception {
    public:
        std::string message;
        explicit SyntaxError(std::string message) : message(std::move(message)) {}
    };

}}

#endif //XERINTERPRETER_AST_H
