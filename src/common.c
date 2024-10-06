#include "common.h"
#include "../include/linux_info.h"
#include "../include/windows_info.h"

void get_system_info(SystemInfo *info) {
#ifdef _WIN32
    get_windows_info(info);
#endif
#ifdef __unix__
    get_linux_info(info);
#endif
}


void print_system_info(const SystemInfo *info) {
    printf("\033[1;32mOperating System Version: \033[0m%s\n", info->os_version);
    printf("\033[1;32mKernel Version: \033[0m%s\n", info->kernel_version);
    printf("\033[1;32mBoot Time: \033[0m%ld seconds or %ld days %ld hours %ld minutes %ld seconds\n", info->boot_time,info->boot_time/DAY,info->boot_time%DAY/HOUR,info->boot_time%HOUR/MINUTE,info->boot_time%MINUTE);
    printf("\033[1;32mCurrent User: \033[0m%s\n", info->current_user);
    printf("\033[1;32mCurrent Time: \033[0m%s\n",info->current_time);
    
    printf("\033[1;32mCPU Model: \033[0m%s\n", info->cpu_model);
    printf("\033[1;32mCPU Cores: \033[0m%d\n", info->cpu_cores);
    printf("\033[1;32mCPU Usage: \033[0m%.2f%%\n", info->cpu_usage);
    printf("\033[1;32mLoad Average (1min, 5min, 15min): \033[0m%.2f, %.2f, %.2f\n", info->load_average_1min, info->load_average_5min, info->load_average_15min);
    printf("\033[1;32mCPU Frequency: \033[0m%.2f MHz = %.2f GHz\n", info->cpu_frequency,info->cpu_frequency/1e3);

    printf("\033[1;32mTotal Memory: \033[0m%lu KB = %lu MB = %lu GB\n", info->total_memory / KBYTES,info->total_memory / MBYTES,info->total_memory / GBYTES);
    printf("\033[1;32mFree Memory: \033[0m%lu KB = %lu MB = %lu GB\n", info->free_memory / KBYTES,info->free_memory / MBYTES,info->free_memory / GBYTES);
    printf("\033[1;32mMemory Usage: \033[0m%.2f%%\n", info->memory_usage);

    printf("\033[1;32mTotal Disk Space: \033[0m%lu KB = %lu MB = %lu GB\n", info->total_disk / KBYTES,info->total_disk / MBYTES,info->total_disk / GBYTES);
    printf("\033[1;32mFree Disk Space: \033[0m%lu KB = %lu MB = %lu GB\n", info->free_disk / KBYTES,info->free_disk / MBYTES,info->free_disk / GBYTES);
    printf("\033[1;32mDisk Usage: \033[0m%.2f%%\n", info->disk_usage);

    printf("\033[1;32mIP Address: \033[0m%s\n", info->ip_address);
    printf("\033[1;32mMAC Address: \033[0m%s\n", info->mac_address);
    
    // Multiline strings
    printf("\033[1;32mNetwork Interfaces: \033[0m\n%s\n", info->network_interfaces);
    printf("\r\033[1;32mRunning Processes: \033[0m\n%s\n", info->processes);

}


/*
Thats printf color codes:
begin with:     
\033[ args1 ; args2 ; args3 m   
end with:       
\033[0m
e.g: printf("\033[1;32m Contents \033[m");

**Parameter 1: Represents the background color**
- **Background color range: 40 - 49**
  - 40: Black
  - 41: Dark Red
  - 42: Green
  - 43: Yellow
  - 44: Blue
  - 45: Purple
  - 46: Dark Green
  - 47: White

**Parameter 2: Represents the font color**
- **Font color range: 30 - 39**
  - 30: Black
  - 31: Red
  - 32: Green
  - 33: Yellow
  - 34: Blue
  - 35: Purple
  - 36: Dark Green
  - 37: White
  - 38: Underline on default foreground color
  - 39: Turn off underline on default background color

**Parameter 3: Represents the display effect (can also be placed in the position of Parameter 1 when Parameter 1 is not needed)**
- 0: Turn off all attributes
- 1: Set high brightness
- 2: Dim (reduce) display
- 4: Underline
- 5: Blink
- 7: Reverse display
- 8: Hide
- 30 -- \33[37: Set foreground color
- 40 -- \33[47: Set background color
- nA: Move cursor up n lines
- nB: Move cursor down n lines
- nC: Move cursor right n lines
- nD: Move cursor left n lines
- y;xH: Set cursor position
- 2J: Clear screen
- K: Clear from cursor to end of line
- s: Save cursor position
- u: Restore cursor position
- ?25l: Hide cursor
- ?25h: Show cursor
*/