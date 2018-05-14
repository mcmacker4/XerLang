#ifndef XERINTERPRETER_CONSTANTS_H
#define XERINTERPRETER_CONSTANTS_H

#include <vector>

#include "util/String.h"

using namespace Util;

namespace Xer { namespace Const {

    extern std::vector<char> opChars;
    extern std::vector<String> keywordList;
    extern std::vector<String> operatorList;

    namespace Keywords {

        extern String VAR;
        extern String INT;
        extern String CHAR;

    }

}}

#endif //XERINTERPRETER_CONSTANTS_H
