#include "common.h"
#define WINDOWS_INFO_H

int main(int argc, char** argv) {
    SystemInfo info;
    print_head_pic();
    get_system_info(&info);
    print_system_info(&info);
    return 0;
}