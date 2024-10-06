#include "../src/common.h"
// TODO : Test on windows
#ifndef WINDOWS_INFO_H
#define WINDOWS_INFO_H

#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <psapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#define DIV 1048576 
#define WIDTH 7
void get_windows_info(SystemInfo *info);
#endif // _WIN32
#endif // WINDOWS_INFO_H
 