// Simple helper functions to serialise and deserialise enum classes

#pragma once

#include <array>
#include <exception>
#include <string>

namespace EnumMapping {
    
// I like exceptions, you might feel differently
class UnknownValueException : public std::runtime_error {
public:
    UnknownValueException(const std::string& name):std::runtime_error("Unknown value: " + name) {};
    UnknownValueException(int value):std::runtime_error("Unknown name for enum value: " + std::to_string(value)) {};
};

template<class T>
struct NameValuePair {
    using value_type = T;
    const T value;
    const char* const name;
};

// Templated helper functions.
// Mapping is some type of standard container that supports find_if()
// V is the type of the enum whose value we wish to look up
template<class Mapping, class V>
std::string getNameForValue(Mapping a, V value) {
    auto pos = std::find_if(std::begin(a), std::end(a), [&value](const typename Mapping::value_type& t){
        return (t.value == value);
    });
    if (pos != std::end(a)) {
        return pos->name;
    }
    
    throw UnknownValueException(static_cast<int>(value));
    // or return some default value here
    // return Mapping::value_type::value_type();
}

template<class Mapping>
typename Mapping::value_type::value_type getValueForName(Mapping a, const std::string& name)
{
    auto pos = std::find_if(std::begin(a), std::end(a), [&name](const typename Mapping::value_type& t){
        return (t.name == name);
    });
    if (pos != std::end(a)) {
        return pos->value;
    }
    
    throw UnknownValueException(name);
    // or return an empty string, whatever works for you
}
    
}

