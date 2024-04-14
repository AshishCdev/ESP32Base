#include "EEPROM.h"
#include "AP.h"
#include "STA.h"
#include "esp_wifi.h"
#include "HTTP_Server.h"
// #include "OTA.h"

#define APP_MAIN_TAG "APP_MAIN:"

extern bool isStationConnected;

void app_main(void)
{
    esp_err_t lastOperation = ESP_FAIL;
    uint8_t ap_active_timer = AP_WAIT_TIME_S;
    
    /************************************************** EEPROM INIT ****************************************/
    lastOperation = EEPROM_Init();

    xTaskCreate(post_sensor_values, "sensor_post_task", 4096, NULL, 5, NULL);

    if( ESP_OK == lastOperation ) {
        // xTaskCreate(&ota_update_task, "ota_task", 8192, NULL, 9, NULL);
        lastOperation = start_http_server();
    } else printf(FAIL_COL"Could not Initialize the EEPROM\n");

    if( ESP_OK == lastOperation ) {
        wifi_init_sta();
    } else printf(FAIL_COL"EEPROM initialization failed.\n");

    // Wait for connection
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    while ( true )
    {
        /* If esp is connected to no where */
        if (esp_wifi_connect() != ESP_OK) {
            
            printf(FAIL_COL"Not connected to the wifi. Swithing to the Access point mode.\n");
            lastOperation = WiFi_Init_AP();

            while( true ){
                
                if( isStationConnected ) {
                    ap_active_timer --;
                    printf(FAIL_COL"Access point mode active for %d seconds.\n", ap_active_timer);
                } else {
                    printf(FAIL_COL"Waiting for SSID information.\n");
                }
                
                if ( ap_active_timer <= 0U )
                {
                    printf(FAIL_COL"AP timeout! rebooting the ESP device.\n");
                    vTaskDelay(pdMS_TO_TICKS(2000));
                    esp_restart();
                }
                
            };
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf(BLUE_COL"Available heap:["PURP_COL"%u"TEST_COL"]\n"PASS_COL, heap_caps_get_free_size(MALLOC_CAP_8BIT) );
        
    }
}