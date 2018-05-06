#include <iostream>

#include "./lex/Tokenizer.h"

using namespace Xer;

int main() {

    std::ifstream stream;
    stream.open("./example.xer", std::ifstream::in);
    if(stream.is_open()) {
        std::cout << "File Open: " << std::endl;
        auto tokens = Lex::Tokenize(stream);
        for (auto &token : tokens) {
            std::cout << token.type << ": " << token.value << std::endl;
        }
    } else {
        std::cerr << "Could not open file." << std::endl;
    }

    return 0;

}