#include "common.h"
#define WINDOWS_INFO_H
#define LINUX_INFO_H
#define LOG_USE_COLOR 1

int main(int argc, char** argv) {
    SystemInfo info;
    print_head_pic;
    // TODO : add your user-arguments code here

    get_system_info(&info);
    print_system_info(&info);
    return 0;
}