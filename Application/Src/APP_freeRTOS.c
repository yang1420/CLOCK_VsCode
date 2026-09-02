#include "App_freeRTOS.h"
#include "Com_debug.h"
#include "Key.h"
#include "touch.h"
#include "mic.h"
#include "DS1302z.h"
#include "DHT11.h"
//
//Just a test task;
//
void task1(void *pvParameters)
{
    (void)pvParameters; // unused
    while (1)
    {
       
        //vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
}
void task2(void *pvParameters)
{
    (void)pvParameters; // unused
    Inf_DHT11_Init(); // Initialize DHT11 module
    while (1)
    {
        debug_printf("Starting DHT11 data read\r\n");
        int8_t temperature = 0;
        int8_t humidity = 0;
        Inf_DHT11_get_data(&temperature, &humidity);
        debug_printf("Temperature: %d, Humidity: %d\r\n", temperature, humidity);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
}

void App_freeRTOS_Init(void)
{
    ///1 create tasks
   // xTaskCreate(task1, "Task 1", 128, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 128, NULL, 1, NULL);
    // 2 start scheduler
    vTaskStartScheduler();
}