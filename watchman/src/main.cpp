#include <iostream>
#include <fstream>
#include <string>
#include "config.h"
#include "console.h"

#include <ctime>

std::string formatTime(long long timestamp)
{
    std::time_t t = static_cast<std::time_t>(timestamp);
    std::tm localTime{};
    localtime_s(&localTime, &t);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer),
                  "%Y-%m-%d %H:%M:%S",
                  &localTime);

    return buffer;
}

Color colorForAction(const std::string &action)
{
    if (action == "CREATED")
        return Color::GREEN;
    if (action == "DELETED")
        return Color::RED;
    if (action == "MODIFIED")
        return Color::YELLOW;
    return Color::DEFAULT;
}

int main()
{
    Config cfg = loadConfig("config/watchman.ini");

    std::ifstream log(cfg.logFile);
    if (!log.is_open())
    {
        std::cerr << "Failed to open log file\n";
        return 1;
    }

    std::string line;
    while (std::getline(log, line))
    {
        if (line.find("\"action\"") != std::string::npos &&
            line.find("\"file\"") != std::string::npos)
        {
            size_t tPos = line.find("\"timestamp\"");
            tPos = line.find(":", tPos) + 1;
            size_t tEnd = line.find(",", tPos);
            long long timestamp = std::stoll(line.substr(tPos, tEnd - tPos));

            size_t aPos = line.find("\"action\"");
            aPos = line.find("\"", aPos + 8) + 1;
            size_t aEnd = line.find("\"", aPos);
            std::string action = line.substr(aPos, aEnd - aPos);

            size_t fPos = line.find("\"file\"");
            fPos = line.find("\"", fPos + 6) + 1;
            size_t fEnd = line.find("\"", fPos);
            std::string fileName = line.substr(fPos, fEnd - fPos);

            std::string timeStr = formatTime(timestamp);

            if (cfg.colorOutput)
                setColor(colorForAction(action));

            std::cout << "[" << timeStr << "] "
                      << "[" << action << "] "
                      << fileName << "\n";

            if (cfg.colorOutput)
                setColor(Color::DEFAULT);
        }
    }

    log.close();
    return 0;
}
