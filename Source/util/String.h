#ifndef XERINTERPRETER_STRING_H
#define XERINTERPRETER_STRING_H

#include <cstring>
#include <vector>

namespace Util {

    struct StringIntern {
        size_t length;
        const char* data;
    };

    class String {
        StringIntern* intern;
        static StringIntern *FindIntern(const char* data, size_t length);
        static StringIntern *NewIntern(const char* data, size_t length);
        static std::vector<StringIntern*> interns;
    public:
        String(const char* data); // NOLINT

        unsigned long Length() const;

        bool Equals(String &other) const;
        bool Equals(const char* data) const;
    };

}

#endif //XERINTERPRETER_STRING_H
