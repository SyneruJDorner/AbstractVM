#include "../../portable_lib.hpp"

std::string currentRow = "";
int columnLength = 0;
std::string VSeperator = "+";

void resetVariables()
{
    columnLength = 0;
    currentRow = "";
    VSeperator = "+";
}

void DetermineVertialLayoutBox(size_t width, bool endSeperator, bool heading)
{
    if (heading == true)
    {
        size_t loopAmount = width;
        if (endSeperator == false)
            loopAmount++;
        
        for (size_t i = 0; i < loopAmount; i++)
        {
            VSeperator += "-";
        }
    } 
}

void tables::InsertEntry(std::string item, size_t width, std::string seperator, bool endSeperator, bool heading, std::string alignment = "left")
{
    int spacesCount = width - item.length();
    DetermineVertialLayoutBox(width, endSeperator, heading);
    currentRow += seperator;

    if (alignment == "right")
        for (int i = 0; i < spacesCount; i++)
        {
            currentRow += " ";
        }

    currentRow += item;

    if (alignment == "left")
        for (int i = 0; i < spacesCount; i++)
        {
            currentRow += " ";
        }

    if (endSeperator == true)
    {
        currentRow += seperator;
        currentRow += "\n";
    }

    if (heading == true)
    columnLength++;
}

void tables::PrintRow(std::string msg = "")
{
    if (msg != "")
    {
        std::cout << msg;
        std::cout << "\n";
    }

    for (int i = 0; i < columnLength; i++)
    {
        if (i == columnLength - 1)
            VSeperator += "+\n";
    }

    std::cout << VSeperator;
    std::cout << currentRow;
    std::cout << VSeperator;
    resetVariables();
}