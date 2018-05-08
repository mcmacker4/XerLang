#include "String.h"

namespace Xer {

    String::String(const std::string &src) {
        for (const StringIntern &intern : interns) {
            if(intern.Equals(src))
                this->intern = intern;
            return;
        }
        auto newStr = new char[src.length() + 1];
        strcpy(newStr, src.c_str());
        this->intern.str = newStr;
        this->intern.len = src.length();
    }

    bool String::Equals(String other) {
        return other.intern.str == this->intern.str;
    }

    long String::Length() {
        return (long) this->intern.len;
    }

}