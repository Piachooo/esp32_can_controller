// #include <stdio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "driver/uart.h"

// #define TXD_PIN 17
// #define RXD_PIN 16

// void  uart_init(void){
//     const uart_config_t uart_config = {
//         .baud_rate = 115200,
//         .data_bits = UART_DATA_8_BITS,
//         .parity = UART_PARITY_DISABLE,
//         .stop_bits = UART_STOP_BITS_1,
//         .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
//     };
//     uart_param_config(UART_NUM_2, &uart_config);
//     uart_set_pin(UART_NUM_2, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
//     uart_driver_install(UART_NUM_2, 1024, 0, 0,NULL, 0);
// }

// void app_main(void)
// {
//     uart_init();
//     while(1)
//     {
//         //uart_write_bytes(UART_NUM_2, (const char*) data, sizeof(data));
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
//}
