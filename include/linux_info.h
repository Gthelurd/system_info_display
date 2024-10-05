#include "../src/common.h"
#ifndef LINUX_INFO_H
#define LINUX_INFO_H

#ifdef __unix__
void get_linux_info(SystemInfo *info);
#endif // __unix__
#endif // LINUX_INFO_H

// TODO： explain the struct used in different headers.

// struct ifaddrs
// {
//     struct ifaddrs  *ifa_next;    /* Next item in list */
//     char            *ifa_name;    /* Name of interface */
//     unsigned int     ifa_flags;   /* Flags from SIOCGIFFLAGS */
//     struct sockaddr *ifa_addr;    /* Address of interface */
//     struct sockaddr *ifa_netmask; /* Netmask of interface */
//     union
//     {
//         struct sockaddr *ifu_broadaddr; /* Broadcast address of interface */
//         struct sockaddr *ifu_dstaddr; /* Point-to-point destination address */
//     } ifa_ifu;
//     #define              ifa_broadaddr ifa_ifu.ifu_broadaddr
//     #define              ifa_dstaddr   ifa_ifu.ifu_dstaddr
//     void            *ifa_data;    /* Address-specific data */
// };

