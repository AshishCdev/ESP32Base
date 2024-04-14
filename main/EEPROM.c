#include "config.h"
#include "nvs_flash.h"

uint8_t SSIDgw[128];
uint8_t PASSgw[128];
uint8_t ADMINpass[128];

LOCAL esp_err_t EEPROM_Write( nvs_handle_t my_handle, const char *key, const char* value ) {
    
    esp_err_t err = nvs_set_str(my_handle, key, value);
    printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

    // Commit written value.
    // After setting any values, nvs_commit() must be called to ensure changes are written
    // to flash storage. Implementations may write to storage at other times,
    // but this is not guaranteed.
    if( ESP_OK == err ) {
        printf("Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
    }

    return err;
}

esp_err_t EEPROM_Init( void ) {

    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    nvs_handle_t my_handle;
    
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK( err );
    
    err = nvs_open("storage", NVS_READWRITE, &my_handle);

    if (err != ESP_OK) {
        printf(FAIL_COL"Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else { 
        err = nvs_get_str(my_handle, "ssid", SSIDgw, strlen((char *)SSIDgw) );
        err = nvs_get_str(my_handle, "password", PASSgw, strlen((char *)PASSgw) ); 
        err = nvs_get_str(my_handle, "adminpass", ADMINpass, strlen((char *)ADMINpass) ); 
    }

    switch (err) {
        case ESP_OK:
            printf("SSID information has been read succuessfully\n");
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            printf("The ssid value is not initialized yet!\nUsing the default ones\n");
            strcpy(SSIDgw, SSIDgwDefault);
            strcpy(PASSgw, PASSgwDefault);
            strcpy(ADMINpass, ADMINpassDefault);
            fflush( stdout );
            break;
        default :
            printf(FAIL_COL"Error (%s) reading!\n"PASS_COL, esp_err_to_name(err));
    }

    nvs_close( my_handle );

    return err;
}