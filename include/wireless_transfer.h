#pragma once
#include <stdbool.h>

#ifndef WIFI_SSID
#define WIFI_SSID "PicoHotspot"
#endif

#ifndef WIFI_PASS
#define WIFI_PASS "pico1234"
#endif

#ifndef DEST_IP
#define DEST_IP "2607:fb90:ad1d:8986:189a:77ea:9f2c:5b14"
#endif

#ifndef DEST_PORT
#define DEST_PORT 5005
#endif

bool wireless_init(void);
bool wireless_send_row(float t, const float quat[3][4]);
void wireless_deinit(void);