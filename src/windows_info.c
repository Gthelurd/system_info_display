#include "common.h"
#include "../include/windows_info.h"
// TODO: test on windows
#ifdef _WIN32
void get_windows_info(SystemInfo *info) {
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((OSVERSIONINFO*)&osvi);
    snprintf(info->os_version, sizeof(info->os_version), "Windows %d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion);

    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    info->cpu_cores = sysinfo.dwNumberOfProcessors;

    MEMORYSTATUSEX meminfo;
    meminfo.dwLength = sizeof(meminfo);
    GlobalMemoryStatusEx(&meminfo);
    info->total_memory = meminfo.ullTotalPhys;
    info->free_memory = meminfo.ullAvailPhys;

    ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
    GetDiskFreeSpaceEx(NULL, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes);
    info->total_disk = totalNumberOfBytes.QuadPart;
    info->free_disk = totalNumberOfFreeBytes.QuadPart;

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) {
        printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) {
            printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (pAdapter->Type == MIB_IF_TYPE_ETHERNET) {
                strncpy(info->ip_address, pAdapter->IpAddressList.IpAddress.String, sizeof(info->ip_address));
                strncpy(info->mac_address, pAdapter->Address, sizeof(info->mac_address));
                break;
            }
            pAdapter = pAdapter->Next;
        }
    } else {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
    }

    if (pAdapterInfo)
        free(pAdapterInfo);
}
#endif