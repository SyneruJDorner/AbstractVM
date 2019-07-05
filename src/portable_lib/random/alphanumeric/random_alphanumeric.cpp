#include "../../portable_lib.hpp"

std::string random_alphanumeric::random_aplha(size_t length)
{
    char str[length];
    static const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i < length; ++i)
    {
        str[i] = alphanum[random_numbers::randomRange(1, 62) % (sizeof(alphanum) - 1)];
    }

    str[length] = '\0';
    return str;
}