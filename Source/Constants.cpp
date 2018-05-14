#include "Constants.h"

namespace Xer { namespace Const {

        std::vector<char> opChars = { // NOLINT
                '!', '%', '&', '*', '+', '-', '/', '<', '=', '>', '^', '|'
        };

        std::vector<String> keywordList = { // NOLINT
                "var",
                "int",
                "char"
        };

        std::vector<String> operatorList = { // NOLINT
                //L0
                "||",
                //L1
                "&&",
                //L2
                "==", "!=", "<", "<=", ">", ">=",
                //L3
                "+", "-", "|", "^",
                //L4
                "*", "/", "%", "<<", ">>", "&"
        };

        namespace Keywords {

            String VAR = "var"; // NOLINT
            String INT = "int"; // NOLINT
            String CHAR = "char"; // NOLINT

        }

}}