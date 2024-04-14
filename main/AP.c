#include "AP.h"

extern char mac[13];
bool isStationConnected = false;


LOCAL void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(MODULE_TAG_AP, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
                 isStationConnected = true;
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(MODULE_TAG_AP, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
                 isStationConnected = false;
    } else {
        isStationConnected = false;
    }
}

esp_err_t WiFi_Init_AP( void )
{ 
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_err_t err = esp_wifi_init( &cfg );

    if ( ESP_OK == err ) {
        err = esp_event_handler_instance_register(WIFI_EVENT,
                                                    ESP_EVENT_ANY_ID,
                                                    &wifi_event_handler,
                                                    NULL,
                                                    NULL);
    }
    
    wifi_config_t wifi_config = {
        .ap = {
            .channel = ESP_WIFI_CHANNEL,
            .password = ESP_AP_PASS,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .pmf_cfg = {
                    .required = true,
            },
        },
    };

    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);
    char apSSID[128];
    sprintf( apSSID, ESP_AP_SSID"%X %X %X %X %X %X", 
                     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]); 
    strcpy( (char*)wifi_config.ap.ssid, apSSID );
    wifi_config.ap.ssid_len = strlen((char*)wifi_config.ap.ssid);

    if (strlen(ESP_AP_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    if ( ESP_OK == err ) {
        err = esp_wifi_set_mode(WIFI_MODE_AP);
    }

    if ( ESP_OK == err ) {
        err = esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    }
    
    if ( ESP_OK == err ) {
        err = esp_wifi_start();
    }
    return err;
}