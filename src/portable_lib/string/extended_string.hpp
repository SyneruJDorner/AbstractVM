#ifndef EXTENDED_STRING_H
#define EXTENDED_STRING_H

class extended_string
{
public:
    static std::string truncate(std::string str, size_t width, bool show_ellipsis, std::string ellipsis);
    static std::string stringToUpper(std::string inputStr);
};

#endif