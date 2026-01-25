#include "config.h"
#include <fstream>
#include <sstream>

Config loadConfig(const std::string &path)
{
    Config cfg;
    cfg.colorOutput = true;

    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '[')
            continue;

        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        // trim spaces (basic)
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));

        if (key == "log_file")
            cfg.logFile = value;

        else if (key == "color_output")
            cfg.colorOutput = (value == "true");
    }

    return cfg;
}
