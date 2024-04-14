
#ifndef AP_H_
#define AP_H_

#include "config.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_mac.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_wifi_types.h"

#define MODULE_TAG_AP "WiFi softAP:"

#define ESP_AP_SSID      "NODE:"
#define ESP_AP_PASS      "Base@2024"
#define ESP_WIFI_CHANNEL   1
#define MAX_STA_CONN       4

#define AP_WAIT_TIME_S     30

esp_err_t WiFi_Init_AP( void );

#endif