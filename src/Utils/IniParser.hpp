#ifndef INIPARSER_HPP
#define INIPARSER_HPP


#include <string>
#include <map>
#include <sstream>

class IniParser
{
public:
    IniParser();

template <class T>
T IniParser::get(const std::string& key, const T& default_value) const
{
    std::istringstream iss(get(key));
    T value;
    if (iss >> value)
        return value;
    return default_value;
}


template <class T>
void IniParser::set(const std::string& key, const T& value)
{
    if (cursor_ != NULL)
    {
        std::ostringstream oss;
        oss << value;
        (*cursor_)[key] = oss.str();
    }
}

#endif // INIPARSER_HPP
