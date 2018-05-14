#ifndef XERINTERPRETER_STRING_H
#define XERINTERPRETER_STRING_H

#include <cstring>
#include <string>
#include <vector>
#include <ostream>

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
        explicit String(const std::string &data) : String(data.c_str()) {}

        unsigned long Length() const;

        bool Equals(String &other) const;
        bool Equals(const char* data) const;

        const char* CStr();

        friend bool operator==(String &one, String &two);
        friend bool operator!=(String &one, String &two);
        friend std::ostream &operator<<(std::ostream& stream, const String& string);
    };

}

#endif //XERINTERPRETER_STRING_H
