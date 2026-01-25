#include <iostream>
#include "watcher.h"
#include "logger.h"

int main()
{
    std::wstring path;

    std::wcout << L"Enter directory to watch: ";
    std::getline(std::wcin, path);

    if (!validateDirectory(path))
    {
        std::wcerr << L"Invalid directory path\n";
        return 1;
    }

    initLogger();
    startWatching(path);
    return 0;
}
