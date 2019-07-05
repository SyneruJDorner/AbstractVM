#ifndef TABLES_H
#define TABLES_H

class tables
{
public:
    //static std::string truncate(std::string str, size_t width, bool show_ellipsis, std::string ellipsis);
    static void InsertEntry(std::string item, size_t width, std::string seperator, bool endSeperator, bool heading, std::string alignment);
    static void PrintRow(std::string msg);
};

#endif