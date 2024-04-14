#ifndef EEPROM_H_
#define EEPROM_H_

#include "config.h"
#include "nvs_flash.h"
#include "nvs.h"

#define    MODULE_TAG_EEPROM                  "EEPROM:"

esp_err_t EEPROM_Init( void );

#endif