#include "common.h"
#include "../include/linux_info.h"
#ifdef __unix__

/*
 * Function: get_linux_info
 * ------------------------
 * Retrieves system information for a Linux system and populates the SystemInfo structure.
 *
 * Parameters:
 *   info - Pointer to the SystemInfo structure to be populated.
 *
 * Notes:
 *   - The function caches the system information to avoid redundant calls to system APIs.
 *   - The cached information is stored in the static variable `cached_info`.
 *   - The function uses various system APIs and files to gather information:
 *     - `uname` for OS and kernel version.
 *     - `sysinfo` for memory and uptime information.
 *     - `/proc/cpuinfo` for CPU model, cores, and frequency and average load.
 *     - `/proc/meminfo` for memory usage information.
 *     - `/proc/stat` for CPU usage information.
 *     - `statvfs` for disk space information.
 *     - `getpid` for process ID.
 *     - `getifaddrs` for network interface information (IP and MAC addresses).
 * 
 */
void get_linux_info(SystemInfo *info) {
    static int initialized = 0;
    static SystemInfo cached_info;

    if (!initialized) {
        // OS and kernel version
        struct utsname uname_data;
        uname(&uname_data);
        snprintf(cached_info.os_version, sizeof(cached_info.os_version), "%s %s", uname_data.sysname, uname_data.release);
        snprintf(cached_info.kernel_version, sizeof(cached_info.kernel_version), "%s", uname_data.version);

        // memory and uptime information
        struct sysinfo meminfo;
        sysinfo(&meminfo);
        cached_info.boot_time = meminfo.uptime;
        cached_info.total_memory = meminfo.totalram;
        cached_info.free_memory = meminfo.freeram;
        FILE *meminfo_file = fopen("/proc/meminfo", "r");
        char line[256];
        if (meminfo_file) {
            unsigned long long total_memory, free_memory, buffers, cached;
            fscanf(meminfo_file, "MemTotal: %llu kB\n", &total_memory);
            fscanf(meminfo_file, "MemFree: %llu kB\n", &free_memory);
            fgets(line,sizeof(line),meminfo_file); // Skip "MemAvailable: xx kB\n"
            fscanf(meminfo_file, "Buffers: %llu kB\n", &buffers);
            fscanf(meminfo_file, "Cached: %llu kB\n", &cached);
            cached_info.memory_usage = 100.0 * ((double)(total_memory - free_memory - buffers - cached) / total_memory);
            // printf("%llu %llu %llu %llu %llu\n", total_memory, free_memory, buffers, cached,(total_memory - free_memory - buffers - cached));
            fclose(meminfo_file);
        }
        // below code doesn't work well because mi.uordblks and mi.hblkhd are not accurate
        // struct mallinfo mi = mallinfo();
        // long page_size = sysconf(_SC_PAGESIZE);
        // cached_info.memory_usage = 100.0 * (mi.uordblks + mi.hblkhd) / (cached_info.total_memory * page_size);
        // printf("uordblks:%d,hblkhd:%d,total_mem:%lu,pagesize:%ld\n",mi.uordblks , mi.hblkhd,cached_info.total_memory,page_size);
        double loadavg[3];
        getloadavg(loadavg, 3);
        cached_info.load_average_1min = loadavg[0];
        cached_info.load_average_5min = loadavg[1];
        cached_info.load_average_15min = loadavg[2];
        
        // current user
        struct passwd *pwd;
        uid_t uid = geteuid();
        pwd = getpwuid(uid);
        if (pwd) {
            snprintf(cached_info.current_user, sizeof(cached_info.current_user), "%s", pwd->pw_name);
        }

        // current time
        time_t now;
        struct tm* timeinfo;
        char* buffer = malloc(sizeof(char) * kMaxInfoBuffer);
        time(&now);
        timeinfo = localtime(&now);
        strftime(buffer, kMaxInfoBuffer, "%Y-%m-%d %H:%M:%S", timeinfo);
        snprintf(cached_info.current_time, sizeof(cached_info.current_time), "%s", buffer);

        // CPU info
        FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
        if (cpuinfo) {
            char line[256];
            while (fgets(line, sizeof(line), cpuinfo)) {
                if (strstr(line, "model name")) {
                    sscanf(line, "model name : %[^\n]", cached_info.cpu_model);
                } else if (strstr(line, "cpu cores")) {
                    sscanf(line, "cpu cores : %d", &cached_info.cpu_cores);
                } else if (strstr(line, "cpu MHz")) {
                    sscanf(line, "cpu MHz : %lf", &cached_info.cpu_frequency);
                }
            }
            fclose(cpuinfo);
        }

        // disk usage
        struct statvfs stat;
        if (statvfs("/", &stat) == 0) {
            cached_info.total_disk = stat.f_blocks * stat.f_frsize;
            cached_info.free_disk = stat.f_bfree * stat.f_frsize;
            cached_info.disk_usage = 100.0 * (stat.f_blocks - stat.f_bfree) / stat.f_blocks;
        }

        // IP address
        struct ifaddrs *ifaddr, *ifa;
        if (getifaddrs(&ifaddr) == 0) {
            for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
                    struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
                    inet_ntop(AF_INET, &addr->sin_addr, cached_info.ip_address, sizeof(cached_info.ip_address));
                }
                if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET) {
                    struct sockaddr_ll *addr = (struct sockaddr_ll *)ifa->ifa_addr;
                    snprintf(cached_info.mac_address, sizeof(cached_info.mac_address), "%02x:%02x:%02x:%02x:%02x:%02x",
                             addr->sll_addr[0], addr->sll_addr[1], addr->sll_addr[2],
                             addr->sll_addr[3], addr->sll_addr[4], addr->sll_addr[5]);
                }
            }
            freeifaddrs(ifaddr);
        }

        // CPU Usage
        FILE *cpu_stat = fopen("/proc/stat", "r");
        if (cpu_stat) {
            unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
            fscanf(cpu_stat, "cpu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
                   &user, &nice, &system, &idle, &iowait, &irq, &softirq, &steal, &guest, &guest_nice);
            unsigned long long total_cpu_time = user + nice + system + idle + iowait + irq + softirq + steal;
            cached_info.cpu_usage = 100.0 * (total_cpu_time - idle) / total_cpu_time;
            fclose(cpu_stat);
        }
        // Below code is not working well because system_time is not accurate
        // struct rusage usage;
        // getrusage(RUSAGE_SELF, &usage);
        // struct timespec ts;
        // clock_gettime(CLOCK_MONOTONIC, &ts);
        // double total_time = ts.tv_sec + ts.tv_nsec / 1e9;
        // double user_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / (double)1e6;
        // double system_time = usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / (double)1e6;
        // cached_info.cpu_usage = 100.0 * (double)(user_time + system_time) / (double)total_time;
        // printf("User time: %f, System time: %f, Total time: %f\n", user_time, system_time, total_time);

        // Network Interfaces
        FILE *netdev_file = fopen("/proc/net/dev", "r");
        if (netdev_file) {
            char line[256];
            fgets(line, sizeof(line), netdev_file); // Skip header
            fgets(line, sizeof(line), netdev_file); // Skip header
            while (fgets(line, sizeof(line), netdev_file)) {
                char interface[64];
                unsigned long long rx_bytes, tx_bytes;
                sscanf(line, "%s %llu %*u %*u %*u %*u %*u %*u %*u %llu", interface, &rx_bytes, &tx_bytes);
                snprintf(cached_info.network_interfaces + strlen(cached_info.network_interfaces),
                         sizeof(cached_info.network_interfaces) - strlen(cached_info.network_interfaces),
                         "%s: RX: %llu bytes, TX: %llu bytes\n", interface, rx_bytes, tx_bytes);
            }
            fclose(netdev_file);
        }
        // below codes are not working
        // int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        // if (sockfd >= 0) {
        //     struct ifreq ifr;
        //     strncpy(ifr.ifr_name, "eth0", IFNAMSIZ); // Replace with desired interface
        //     if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) == 0) {
        //         snprintf(cached_info.mac_address, sizeof(cached_info.mac_address), "%02x:%02x:%02x:%02x:%02x:%02x",
        //                  (unsigned char)ifr.ifr_hwaddr.sa_data[0],
        //                  (unsigned char)ifr.ifr_hwaddr.sa_data[1],
        //                  (unsigned char)ifr.ifr_hwaddr.sa_data[2],
        //                  (unsigned char)ifr.ifr_hwaddr.sa_data[3],
        //                  (unsigned char)ifr.ifr_hwaddr.sa_data[4],
        //                  (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
        //     }
        //     close(sockfd);
        // }

        // Process Information
        // pid_t pid = getpid();
        // pid_t ppid = getppid();
        DIR *proc_dir = opendir("/proc");
        if (proc_dir) {
            struct dirent *entry;
            while ((entry = readdir(proc_dir)) != NULL) {
                if (entry->d_type == DT_DIR && isdigit(entry->d_name[0])) {
                    char path[512];  // Increase buffer size to avoid truncation warning
                    snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
                    FILE *stat_file = fopen(path, "r");
                    if (stat_file) {
                        int pid;
                        char comm[256];
                        char state;
                        fscanf(stat_file, "%d %s %c", &pid, comm, &state);
                        // TODO:Store or process process data as needed
                        snprintf(cached_info.processes + strlen(cached_info.processes),
                                sizeof(cached_info.processes) - strlen(cached_info.processes),
                                "PID: %d, Command: %s, State: %c\n", pid, comm, state);
                        fclose(stat_file);
                    }
                }
            }
            closedir(proc_dir);
        }
        initialized = 1;
    }
    *info = cached_info;
}
#endif