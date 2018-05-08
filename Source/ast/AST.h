#ifndef XERINTERPRETER_AST_H
#define XERINTERPRETER_AST_H

#include <utility>
#include <vector>
#include <string>

namespace Xer { namespace Ast {

    //predeclarations
    class Statement;

    /**
     * Variable type
     */
    enum Type {
        INTEGER
    };

    /**
     * Operators
     */
    enum BinaryOperator {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        LESS_THAN,
        GREATER_THAN,
        AND,
        OR,
        BIT_AND,
        BIT_OR,
        BIT_XOR
    };

    enum UnaryOperator {
        MINUS,
        NEGATE
    };

    /**
     * Tree Node
     * @tparam T
     */
    template <class T>
    class Node<T> {
        std::vector<T> children;
    public:
        const T& GetChild(long n);
        void PushChild(T &child);
        long ChildCount();
    };

    /**
     * Abstract Syntax Tree
     */
    class AST : public Node<Statement> {
        std::string fileName;
    public:
        explicit AST(std::string fileName) : fileName(std::move(fileName)) {}
    };

    /**
     * Value
     */
    class Value {
    public:
        Value() = default;
    };

    /**
     * Expression
     */
    class Expression : public Value {
    public:
        Expression() = default;
    };

    /**
     * BinaryOperation
     */
    class BinaryOperation : public Expression {
        Value left;
        Value right;
        BinaryOperator op;
    public:
        BinaryOperation(Value left, Value right, BinaryOperator op)
                : left(left), right(right), op(op) {}
    };

    /**
     * UnaryOperator
     */
    class UnaryOperation : public Expression {
        Value value;
        UnaryOperator op;
    public:
        UnaryOperation(Value value, UnaryOperator op)
                : value(value), op(op) {}
    };

    /**
     * Literal
     */
    class Literal : public Value {
        std::string value;
    public:
        explicit Literal(std::string value)
                : value(std::move(value)) {}
    };

    class Variable : public Value {
        std::string name;
    public:
        explicit Variable(std::string name)
                : name(std::move(name)) {}
    };

    /**
     * Statement
     */
    class Statement {
    public:
        Statement() = default;
        virtual ~Statement() = default;
    };

    /**
     * Declaration extends Statement
     */
    class Declaration : public Statement {
        Type type;
        Value value;
        std::string varName;
    public:
        Declaration(std::string varName, Value value)
                : varName(std::move(varName)), type(INTEGER), value(value) {}
    };

    /**
     * Assignment extends Statement
     */
    class Assignment : public Statement {
        Value value;
        std::string varName;
    public:
        Assignment(std::string varName, Value value)
                : varName(std::move(varName)), value(value) {}
    };

}}

#endif //XERINTERPRETER_AST_H
