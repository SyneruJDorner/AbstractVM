#ifndef RANDOM_NAMES_H
#define RANDOM_NAMES_H

class random_names
{
public:
    static std::string* GenerateNames(int amount);
    static std::string* GenerateSurnames(int amount);
    static std::string* GenerateNamesAndSurnames(int amount);
    static void ReadOutMaleNames();
    static std::string GetMaleNames();
    static const char* males;
    static const char* females;
};

#endif