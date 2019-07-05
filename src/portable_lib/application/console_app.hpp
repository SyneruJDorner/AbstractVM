#ifndef CONSOLE_APP_H
#define CONSOLE_APP_H

#include <stdlib.h>

class console_app
{
public:
    //static std::string truncate(std::string str, size_t width, bool show_ellipsis, std::string ellipsis);
    static void ClearWindow();
    static void Kill();
};

#endif