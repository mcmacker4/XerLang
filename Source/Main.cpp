#include <iostream>

#include "./lex/Tokenizer.h"

using namespace Xer;

int main() {

    std::ifstream stream;
    std::string fileName("./example.xer");
    stream.open(fileName, std::ifstream::in);
    if(stream.is_open()) {
        try {
            auto tokens = Lex::Tokenize(stream);
            while (!tokens.empty()) {
                auto token = tokens.front();
                std::cout << token.type << ": " << token.value << std::endl;
                tokens.pop();
            }
        } catch (Err::UnexpectedTokenException &ex) {
            std::cout << "Unexpected Token \"" << ex.token << "\" " <<
                      fileName << ":" << ex.line << ":" << ex.position << std::endl;
        }
    } else {
        std::cerr << "Could not open file." << std::endl;
    }

    return 0;

}