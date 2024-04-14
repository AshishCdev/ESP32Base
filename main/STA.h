#ifndef STA_H
#define STA_H

#include "config.h"
#include "esp_event.h"
#include "esp_wifi.h"

#define ESP_MAXIMUM_RETRY                       5
#define ESP_WIFI_SAE_MODE                       WPA3_SAE_PWE_BOTH
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD       WIFI_AUTH_WPA2_PSK

void wifi_init_sta(void);

#endif