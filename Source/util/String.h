#ifndef XERINTERPRETER_STRING_H
#define XERINTERPRETER_STRING_H

#include <vector>
#include <string>
#include <cstring>

namespace Xer {

    struct StringIntern {
        const char* str;
        size_t len;

        bool Equals(const std::string &other) const {
            if(this->len != other.length())
                return false;
            return strcmp(this->str, other.c_str()) == 0;
        }
    };

    class String {
        StringIntern intern;
        static std::vector<StringIntern> interns;
    public:
        explicit String(const std::string &src);

        bool Equals(String other);
        long Length();

    };

}

#endif //XERINTERPRETER_STRING_H
