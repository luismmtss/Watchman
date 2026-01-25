#include "watcher.h"
#include "logger.h"
#include <windows.h>
#include <iostream>
#include <atomic>

static std::atomic<bool> keepRunning(true);
static HANDLE g_dirHandle = nullptr;

const wchar_t *actionToString(DWORD action)
{
    switch (action)
    {
    case FILE_ACTION_ADDED:
        return L"CREATED";
    case FILE_ACTION_REMOVED:
        return L"DELETED";
    case FILE_ACTION_MODIFIED:
        return L"MODIFIED";
    case FILE_ACTION_RENAMED_OLD_NAME:
        return L"RENAMED_FROM";
    case FILE_ACTION_RENAMED_NEW_NAME:
        return L"RENAMED_TO";
    default:
        return L"UNKNOWN";
    }
}

bool validateDirectory(const std::wstring &path)
{
    if (path.empty())
    {
        std::wcerr << L"Path is empty\n";
        return false;
    }

    DWORD attrs = GetFileAttributesW(path.c_str());

    if (attrs == INVALID_FILE_ATTRIBUTES)
    {
        std::wcerr << L"Path does not exist\n";
        return false;
    }

    if (!(attrs & FILE_ATTRIBUTE_DIRECTORY))
    {
        std::wcerr << L"Path is not a directory\n";
        return false;
    }

    return true;
}

BOOL WINAPI consoleHandler(DWORD signal)
{
    if (signal == CTRL_C_EVENT)
    {
        std::wcout << L"\nStopping watcher...\n";
        keepRunning = false;

        if (g_dirHandle)
        {
            CancelIoEx(g_dirHandle, NULL);
            CloseHandle(g_dirHandle);
            g_dirHandle = nullptr;
        }

        closeLogger();
        return TRUE;
    }
    return FALSE;
}

void startWatching(const std::wstring &path)
{
    HANDLE dir = CreateFileW(
        path.c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL);

    if (dir == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"Failed to open directory\n";
        return;
    }

    SetConsoleCtrlHandler(consoleHandler, TRUE);
    g_dirHandle = dir;

    BYTE buffer[4096];
    DWORD bytesReturned;

    while (keepRunning)
    {
        ReadDirectoryChangesW(
            dir,
            buffer,
            sizeof(buffer),
            TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME |
                FILE_NOTIFY_CHANGE_DIR_NAME |
                FILE_NOTIFY_CHANGE_LAST_WRITE,
            &bytesReturned,
            NULL,
            NULL);
        if (!keepRunning)
            break;

        FILE_NOTIFY_INFORMATION *info =
            (FILE_NOTIFY_INFORMATION *)buffer;

        while (true)
        {
            std::wstring fileName(
                info->FileName,
                info->FileNameLength / sizeof(WCHAR));

            std::wcout << L"["
                       << actionToString(info->Action)
                       << L"] "
                       << fileName
                       << L"\n";

            logEvent(info->Action, fileName);

            if (info->NextEntryOffset == 0)
                break;

            info = (FILE_NOTIFY_INFORMATION *)((BYTE *)info + info->NextEntryOffset);
        }
    }
}
