#pragma once
#include <string>

struct Config
{
    std::string logFile;
    bool colorOutput;
};

Config loadConfig(const std::string &path);
