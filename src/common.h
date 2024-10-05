#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

// Common defines
#define  kMaxInfoBuffer 256
#define  lMaxInfoBuffer 1024
#define  lBuffer 4096
#define  GBYTES  1073741824    
#define  MBYTES  1048576    
#define  KBYTES  1024    
#define  DKBYTES 1024.0
#define  DMBYTES 1048576.0
#define  DGBYTES 1073741824.0
#define  DAY 86400
#define  HOUR 3600
#define  MINUTE 60
#define  SECOND 1

// Include platform-specific headers
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
#endif

#ifdef __unix__
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_packet.h> 
#include <pwd.h>
#include <fcntl.h>
#include <linux/hdreg.h>
#include <sys/resource.h>
#include <malloc.h>
#include <dirent.h>
#include <ctype.h>
#endif

/*
 * Structure: SystemInfo
 * ----------------------
 * Represents the system information collected by the program.
 *
 * Fields:
 *   os_version - Operating system version.
 *   kernel_version - Kernel version.
 *   cpu_model - CPU model name.
 *   cpu_cores - Number of CPU cores.
 *   cpu_frequency - CPU frequency in MHz.
 *   total_memory - Total system memory in KB.
 *   free_memory - Available memory in KB.
 *   memory_usage - Memory usage percentage.
 *   total_disk - Total disk space in KB.
 *   free_disk - Available disk space in KB.
 *   disk_usage - Disk usage percentage.
 *   ip_address - IP address in the format xxx.xxx.xxx.xxx.
 *   mac_address - MAC address in the format xx:xx:xx:xx:xx:xx.
 *   boot_time - System boot time in seconds since epoch.
 *   current_user - Current logged-in user.
 *   load_average_1min - Load average for the last 1 minute.
 *   load_average_5min - Load average for the last 5 minutes.
 *   load_average_15min - Load average for the last 15 minutes.
 *   cpu_usage - CPU usage percentage.
 *   network_interfaces - List of network interfaces.
 *   processes - List of running processes.
 */
typedef struct {
    char os_version[kMaxInfoBuffer];          // System version
    char kernel_version[kMaxInfoBuffer];      // Kernel version
    char cpu_model[kMaxInfoBuffer];           // CPU model 
    int cpu_cores;                            // Number of CPU cores 
    double cpu_frequency;                     // Frequency of CPU (MHz)
    unsigned long total_memory;               // Total memory (KB)
    unsigned long free_memory;                // Available memory (KB)
    double memory_usage;                      // Memory usage percentage
    unsigned long total_disk;                 // Total disk space (KB)
    unsigned long free_disk;                  // Available disk space (KB)
    double disk_usage;                        // Disk usage percentage
    char ip_address[kMaxInfoBuffer];          // IP address （xxx.xxx.xxx.xxx）
    char mac_address[kMaxInfoBuffer];         // MAC address （xx:xx:xx:xx:xx:xx）
    unsigned long boot_time;                  // Boot time (Seconds since epoch)
    char current_user[kMaxInfoBuffer];        // Current user （username）
    double load_average_1min;                 // load average in 1 minute 
    double load_average_5min;                 // load average in 5 minutes 
    double load_average_15min;                // load average in 15 minutes
    double cpu_usage;                         // CPU usage percentage
    char network_interfaces[lMaxInfoBuffer];  // List of network interfaces
    char processes[lBuffer];           // List of running processes
} SystemInfo;

/*
 * Function: get_system_info
 * -------------------------
 * Retrieves system information and populates the SystemInfo structure.
 * This function works on both Win32 and Unix systems.
 *
 * Parameters:
 *   info - Pointer to the SystemInfo structure to be populated.
 *
 * Notes:
 *   - On Win32 systems, it calls get_windows_info(SystemInfo *info).
 *   - On Unix systems, it calls get_linux_info(SystemInfo *info).
 */
void get_system_info(SystemInfo *info);

/*
 * Function: print_system_info
 * ----------------------------
 * Prints the system information stored in the SystemInfo structure.
 *
 * Parameters:
 *   info - Pointer to the SystemInfo structure containing the system information.
 *
 * The format of the output is as follows:
 *     - Operating System Version
 *     - Kernel Version
 *     - Boot Time
 *     - Current User
 *     - Load Average (1min, 5min, 15min)
 *     - CPU Model
 *     - CPU Cores
 *     - CPU Frequency
 *     - Total Memory
 *     - Free Memory
 *     - Memory Usage
 *     - Total Disk Space
 *     - Free Disk Space
 *     - Disk Usage
 *     - IP Address
 *     - MAC Address
 *     - CPU Usage
 *     - Network Interfaces
 *     - Running Processes `TOBEDONE`
 */
void print_system_info(const SystemInfo *info);
// Picture printing
void print_head_pic(void);
#endif // COMMON_H

/*
 * The following commands are equivalent to the system information retrieval methods used in this program:
 * - cat /proc/stat
 * - cat /proc/meminfo
 * - cat /proc/cpuinfo
 * - cat /proc/diskstats
 * - cat /proc/net/dev
 */