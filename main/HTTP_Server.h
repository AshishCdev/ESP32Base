#ifndef HTTP_S_H_
#define HTTP_S_H_

#include "config.h"
#include "esp_http_server.h"
#include "esp_http_client.h"

#define MODULE_TAG_HTTP_S           "file_server:"

#define POST_PERIOD_S               10

#define POST_URL                    "http://eggsmart-api-production.up.railway.app/api/data"

esp_err_t start_http_server( void );

void post_sensor_values(void* arg);

#endif