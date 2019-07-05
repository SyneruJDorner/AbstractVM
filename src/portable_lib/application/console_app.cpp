#include "../portable_lib.hpp"

void console_app::ClearWindow()
{
    system("@cls||clear");
}

void console_app::Kill()
{
    ClearWindow();
    exit(0);
}