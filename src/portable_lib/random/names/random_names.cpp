#include "../../portable_lib.hpp"

std::string* random_names::GenerateNames(int amount)
{
    std::string *names = new std::string[amount];
    std::string male_names = random_names::GetMaleNames();
    int totalEntries = 0;
    int counter;

    for (unsigned long i = 0; i < male_names.length(); i++)
    {
        if (male_names[i] == '\n')
            totalEntries++;
    }

    for (int j = 0; j < amount; j++)
    {
        int randomNum = random_numbers::randomRange(0, totalEntries);
        (void)randomNum;
        std::string recievedName = "";
        counter = 0;

        for (unsigned long i = 0; i < male_names.length(); i++)
        {
            if (male_names[i] == '\n')
            {
                counter++;

                if (counter == randomNum)
                {
                    int word_len = i + 1;
                    while (male_names[word_len] != '\n')
                    {
                        recievedName += male_names[word_len];
                        word_len++;
                    }
                }
            }
        }

        names[j] = recievedName;
    }
    return names;
}


std::string* random_names::GenerateSurnames(int amount)
{
    std::string *surnames[amount];
    return *surnames;
}

std::string* random_names::GenerateNamesAndSurnames(int amount)
{
    std::string *fullname[amount];
    return *fullname;
}