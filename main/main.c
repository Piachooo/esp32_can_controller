#include "driver/gpio.h"
#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void uart_init(){
    //Initialize configuration structures using macro initializers
    twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_17, GPIO_NUM_16, TWAI_MODE_LISTEN_ONLY);
    twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
    twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

    //Install TWAI driver
    if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK) {
        printf("Driver installed\n");
    } else {
        printf("Failed to install driver\n");
        return;
    }
        //Start TWAI driver
    if (twai_start() == ESP_OK) {
        printf("Driver started\n");
    } else {
        printf("Failed to start driver\n");
        return;
    }
}

void can_receive_task(){
    twai_message_t message;
        if(twai_receive(&message, pdMS_TO_TICKS(100)) == ESP_OK){
            printf("Typ     : %lu", message.identifier);
            printf("\n");
            printf("Typ     : %03lX", message.identifier);
            printf("\n");
            printf("Dlugosc : %u", message.data_length_code);
            printf("\n");
            printf("Wartosc :");
            for(int i = 0; i < message.data_length_code; i++){
                printf(" %03u", message.data[i]);
            }
            printf("\n");
            printf("Wartosc :");
            for(int i = 0; i < message.data_length_code; i++){
                printf(" %02X", message.data[i]);
            }
            printf("\n");
        }
        printf("\n");
        vTaskDelete(NULL);
}

void app_main(void){
    uart_init();
    while(1){
        xTaskCreate(&can_receive_task, "can_receive_task", 4096, NULL, 5, NULL);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
