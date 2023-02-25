#include "driver/gpio.h"
#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void can_receive_task(void *arg){
    twai_message_t message;
    for(;;){
        if(twai_receive(&message, pdMS_TO_TICKS(1000)) == ESP_OK){
            printf("Odebrano ramke CAN Data: " + message.identifier + message.data_length_code);
            for(int i = 0; i < message.data_length_code; i++){
                printf("%02X ", message.data[i]);
            }
            printf("\n");
        }
    }
}

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

void app_main(void){
    uart_init();
    xTaskCreate(&can_receive_task, "can_receive_task", 4096, NULL, 5, NULL);
    while(1){
        printf("Czekamy na wiadomosc\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
