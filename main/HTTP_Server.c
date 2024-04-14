
#include "config.h"
#include "HTTP_Server.h"
#include "RTC.h"
#include "cJSON.h"

httpd_handle_t server = NULL;

esp_err_t get_handler(httpd_req_t *req) {
    const char resp[] = "Hello, World!";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_uri_t http_uri = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_handler,
    .user_ctx = NULL
};

void post_sensor_values(void* arg) {
    
    while (1) {
        vTaskDelay(POST_PERIOD_S * 1000 / portTICK_PERIOD_MS);

        cJSON *root = cJSON_CreateObject();

        // Add logic for the sensor input
        cJSON_AddNumberToObject(root, "temperature", 0xffff);
        cJSON_AddNumberToObject(root, "humidity", 0xffff);
        cJSON_AddNumberToObject(root, "lightIndex", 0xffff);
        
        char *post_data = cJSON_Print(root);

        esp_http_client_config_t config = {
            .url = POST_URL,
            .method = HTTP_METHOD_POST,
        };
        esp_http_client_handle_t client = esp_http_client_init(&config);

        esp_http_client_set_header(client, "Content-Type", "application/json");
        esp_http_client_set_post_field(client, post_data, strlen(post_data));

        esp_err_t err = esp_http_client_perform(client);
        if (err == ESP_OK) {
            printf("HTTP POST request sent successfully\n");
        } else {
            printf("HTTP POST request failed: %s\n", esp_err_to_name(err));
        }

        esp_http_client_cleanup(client);
        cJSON_Delete(root);
        free(post_data);
    }
}

esp_err_t start_http_server( void ) 
{

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_start(&server, &config);
    httpd_register_uri_handler(server, &http_uri);

    return ESP_OK;
}