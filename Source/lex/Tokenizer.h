//
// Created by McMacker4 on 06/05/2018.
//

#ifndef XERINTERPRETER_TOKENIZER_H
#define XERINTERPRETER_TOKENIZER_H

#include <deque>
#include <map>
#include <fstream>
#include <memory>
#include <cassert>

#include "../err/Exceptions.h"
#include "../util/String.h"

using namespace Util;

namespace Xer { namespace Lex {

    enum TokenType {
        NAME = 128,
        KEYWORD,
        NUMBER,
        CHARACTER,
        STRING,
        OPERATOR
    };

    struct Token {
        TokenType type;
        String value;
    };

    std::deque<Token> Tokenize(std::ifstream &stream);
    String TokenTypeToName(TokenType type);

}}

#endif //XERINTERPRETER_TOKENIZER_H
