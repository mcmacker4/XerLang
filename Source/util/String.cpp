#include "String.h"

namespace Util {

//Constructors

    String::String(const char *data) {
        //String length
        size_t length = strlen(data);
        //Find the intern
        intern = FindIntern(data, length);
        //If intern not found
        if(intern == nullptr)
            //Allocate new intern
            intern = NewIntern(data, length);
    }

//Class methods

    unsigned long String::Length() const {
        return (unsigned long) intern->length;
    }

    bool String::Equals(String &other) const {
        return intern == other.intern;
    }

    bool String::Equals(const char *data) const {
        return strcmp(intern->data, data) == 0;
    }

//Static Methods

    std::vector<StringIntern*> String::interns = std::vector<StringIntern*>();

    StringIntern* String::FindIntern(const char *data, size_t length) {
        //For each saved intern
        for(auto intern : interns) {
            //Compare length first, then actual data
            if(intern->length == length && strcmp(data, intern->data) == 0)
                //If everything is the same, return intern pointer
                return intern;
        }
        //String not found
        return nullptr;
    }

    StringIntern* String::NewIntern(const char *data, size_t length) {
        //Allocate char array
        auto str = new char[length + 1];
        //Copy char array
        strcpy(str, data);
        str[length] = 0;
        //Allocate new StringIntern
        auto strIntern = new StringIntern;
        strIntern->length = length;
        strIntern->data = str;
        //Add to interns vector
        interns.push_back(strIntern);
        //Return StringIntern*
        return strIntern;
    }

}