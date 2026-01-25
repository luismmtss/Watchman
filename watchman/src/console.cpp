#include "console.h"

void setColor(Color color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (color)
    {
    case Color::GREEN:
        SetConsoleTextAttribute(hConsole,
                                FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;

    case Color::RED:
        SetConsoleTextAttribute(hConsole,
                                FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;

    case Color::YELLOW:
        SetConsoleTextAttribute(hConsole,
                                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;

    default:
        SetConsoleTextAttribute(hConsole,
                                FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    }
}
