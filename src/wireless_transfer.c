#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"

#include "wireless_transfer.h"

static struct udp_pcb* udp = NULL;
static ip_addr_t dest_ip;

bool wireless_init(void) {
    if (cyw43_arch_init()) {
        return false;
    }

    cyw43_arch_enable_sta_mode();

    // Connect to Wi-Fi (timeout in ms)
    int rc = cyw43_arch_wifi_connect_timeout_ms(
        WIFI_SSID,
        WIFI_PASS,
        CYW43_AUTH_WPA2_AES_PSK,
        30000
    );
    if (rc) {
        cyw43_arch_deinit();
        return false;
    }

    // Parse destination IP (supports IPv4 or IPv6)
    if (!ipaddr_aton(DEST_IP, &dest_ip)) {
        cyw43_arch_deinit();
        return false;
    }

    // Create UDP PCB matching the destination IP type
    udp = udp_new_ip_type(IP_GET_TYPE(&dest_ip));
    if (!udp) {
        cyw43_arch_deinit();
        return false;
    }

    return true;
}

static bool udp_send_bytes(const void* data, uint16_t len) {
    if (!udp) return false;

    struct pbuf* p = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);
    if (!p) return false;

    memcpy(p->payload, data, len);

    cyw43_arch_lwip_begin();
    err_t e = udp_sendto(udp, p, &dest_ip, (u16_t)DEST_PORT);
    cyw43_arch_lwip_end();

    pbuf_free(p);
    return (e == ERR_OK);
}

bool wireless_send_row(float t, const float quat[3][4]) {
    char msg[256];

    int n = snprintf(
        msg,
        sizeof(msg),
        "%.3f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f,%.6f\n",
        t,
        quat[0][0], quat[0][1], quat[0][2], quat[0][3],
        quat[1][0], quat[1][1], quat[1][2], quat[1][3],
        quat[2][0], quat[2][1], quat[2][2], quat[2][3]
    );

    if (n <= 0) return false;
    if (n >= (int)sizeof(msg)) n = sizeof(msg) - 1;

    return udp_send_bytes(msg, (uint16_t)n);
}

void wireless_deinit(void) {
    if (udp) {
        cyw43_arch_lwip_begin();
        udp_remove(udp);
        cyw43_arch_lwip_end();
        udp = NULL;
    }

    cyw43_arch_deinit();
}