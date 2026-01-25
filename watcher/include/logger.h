#pragma once
#include <string>
#include <windows.h>

void initLogger();
void logEvent(DWORD action, const std::wstring &fileName);
void closeLogger();
