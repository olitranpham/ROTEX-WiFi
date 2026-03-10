#pragma once

// Bare-metal / no OS
#define NO_SYS 1

// Use RAW APIs (no netconn, no sockets)
#define LWIP_NETCONN 0
#define LWIP_SOCKET  0

// Protocols we need
#define LWIP_IPV4 1
#define LWIP_IPV6 1
#define LWIP_UDP  1
#define LWIP_TCP  0
#define LWIP_ICMP 1

// DHCP/DNS
#define LWIP_DHCP 1
#define LWIP_DNS  1

// IPv6 autoconfig / router advertisement support
#define LWIP_IPV6_AUTOCONFIG 1
#define LWIP_IPV6_SEND_ROUTER_SOLICIT 1
#define LWIP_ND6_ALLOW_RA_UPDATES 1

// Memory
#define MEM_ALIGNMENT 4
#define MEM_SIZE (16 * 1024)

#define MEMP_NUM_PBUF 16
#define PBUF_POOL_SIZE 16
#define PBUF_POOL_BUFSIZE 1700

// Common lwIP settings
#define LWIP_ARP 1
#define LWIP_RAW 1