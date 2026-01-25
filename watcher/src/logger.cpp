#include "logger.h"
#include <fstream>
#include <ctime>

static bool firstEntry = true;
static const char *LOG_FILE = "logs/changes.json";

void initLogger()
{
    std::ofstream log(LOG_FILE, std::ios::trunc);
    log << "[\n";
    log.close();

    firstEntry = true;
}

std::string actionToString(DWORD action)
{
    switch (action)
    {
    case FILE_ACTION_ADDED:
        return "CREATED";
    case FILE_ACTION_REMOVED:
        return "DELETED";
    case FILE_ACTION_MODIFIED:
        return "MODIFIED";
    case FILE_ACTION_RENAMED_OLD_NAME:
        return "RENAMED_FROM";
    case FILE_ACTION_RENAMED_NEW_NAME:
        return "RENAMED_TO";
    default:
        return "UNKNOWN";
    }
}

void logEvent(DWORD action, const std::wstring &fileName)
{
    std::ofstream log(LOG_FILE, std::ios::app);

    if (!firstEntry)
        log << ",\n";

    std::time_t now = std::time(nullptr);

    log << "  {"
        << "\"timestamp\": " << now << ", "
        << "\"action\": \"" << actionToString(action) << "\", "
        << "\"file\": \"";

    for (wchar_t c : fileName)
        log << (char)c;

    log << "\"}";

    firstEntry = false;
    log.close();
}

void closeLogger()
{
    std::ofstream log(LOG_FILE, std::ios::app);
    log << "\n]\n";
    log.close();
}
