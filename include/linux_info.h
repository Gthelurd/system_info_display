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


// struct sysinfo {
// 	__kernel_long_t uptime;		/* Seconds since boot */
// 	__kernel_ulong_t loads[3];	/* 1, 5, and 15 minute load averages */
// 	__kernel_ulong_t totalram;	/* Total usable main memory size */
// 	__kernel_ulong_t freeram;	/* Available memory size */
// 	__kernel_ulong_t sharedram;	/* Amount of shared memory */
// 	__kernel_ulong_t bufferram;	/* Memory used by buffers */
// 	__kernel_ulong_t totalswap;	/* Total swap space size */
// 	__kernel_ulong_t freeswap;	/* swap space still available */
// 	__u16 procs;		   	/* Number of current processes */
// 	__u16 pad;		   	/* Explicit padding for m68k */
// 	__kernel_ulong_t totalhigh;	/* Total high memory size */
// 	__kernel_ulong_t freehigh;	/* Available high memory size */
// 	__u32 mem_unit;			/* Memory unit size in bytes */
// 	char _f[20-2*sizeof(__kernel_ulong_t)-sizeof(__u32)];	/* Padding: libc5 uses this.. */
// };


