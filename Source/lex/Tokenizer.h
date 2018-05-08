//
// Created by McMacker4 on 06/05/2018.
//

#ifndef XERINTERPRETER_TOKENIZER_H
#define XERINTERPRETER_TOKENIZER_H

#include <queue>
#include <map>
#include <fstream>
#include <memory>
#include <cassert>

#include "../err/Exceptions.h"
#include "../util/Util.h"

namespace Xer { namespace Lex {

    enum TokenType {
        NAME = 128,
        NUMBER,
        CHARACTER,
        STRING,
        OPERATOR
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    std::queue<Token> Tokenize(std::ifstream &stream);

}}

#endif //XERINTERPRETER_TOKENIZER_H
