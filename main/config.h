/*
 * config.h
 *
 *  Created on: 12-Dec-2012
 *      Author: Ashish Kushwaha
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <sys/unistd.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <dirent.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "esp_err.h"
#include "esp_random.h"
#include "esp_vfs.h"

#ifdef RTC_CONF_DS3231
#define RTC_CONF "DS3231"
#else 
#define RTC_CONF "RV3032"
#endif

#define LOCAL static
#define PRINT_STACK_USAGE false

/* stdout color */
#define FAIL_COL     					"\033[1;31m"
#define PASS_COL     					"\033[1;32m"
#define RESET_COL    					"\033[0m"
#define TEST_COL     					"\033[1;33m"
#define BLUE_COL                        "\033[1;34m"
#define PURP_COL						"\033[1;35m"
#define CYAN_COL						"\033[1;36m"

#define SSIDgwDefault                   "BASE2024"
#define PASSgwDefault                   "Base@2024"
#define ADMINpassDefault                "Default@2024"

#endif