#ifndef XERINTERPRETER_EXCEPTIONS_H
#define XERINTERPRETER_EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>
#include <sstream>

namespace Xer { namespace Err {

    enum ExceptionType {
        EXCEPTION,
        UNEXPECTED_TOKEN
    };

    class Exception : public std::exception {
    public:
        const std::string message;
        const ExceptionType type;
        explicit Exception(std::string message)
                : message(std::move(message)), type(EXCEPTION) {}
        Exception(std::string message, ExceptionType type)
                : message(std::move(message)), type(type) {}
    };

    class UnexpectedTokenException : public Exception {
    public:
        const char token;
        const int line;
        const int position;
        UnexpectedTokenException(char token, int line, int position)
                : Exception(GenerateMessage(token, line, position), UNEXPECTED_TOKEN),
                  token(token), line(line), position(position) {}
    private:
        static std::string GenerateMessage(char token, int line, int position) {
            std::ostringstream stream;
            stream << "Unexpected Token \"" << token << "\" (" << line << ":" << position << ")";
            return stream.str();
        }
    };

}}

#endif //XERINTERPRETER_EXCEPTIONS_H
