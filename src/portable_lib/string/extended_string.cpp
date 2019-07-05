#include "../portable_lib.hpp"

std::string extended_string::truncate(std::string str, size_t width, bool show_ellipsis, std::string ellipsis)
{
    if (str.length() > width)
    {
        if (show_ellipsis)
            return str.substr(0, width) + ellipsis;
        else
            return str.substr(0, width);
    }
    return str;
}

std::string extended_string::stringToUpper(std::string inputStr)
{
    std::string ret;
    for(unsigned int i = 0; i < inputStr.length(); i++)
    {
        ret += std::toupper(inputStr[i]);
    }
    return ret;
}