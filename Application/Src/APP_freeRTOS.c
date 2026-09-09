#include "App_freeRTOS.h"
#include "Com_debug.h"
#include "Key.h"
#include "touch.h"
#include "mic.h"
#include "DS1302z.h"
#include "DHT11.h"
#include "NV020D.h"
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

    NV020D_Init(); // Initialize NV020D module
    while (1)
    {
        debug_printf("Starting DHT11 data read\r\n");
        int8_t temperature = 0;
        int8_t humidity = 0;
        Inf_DHT11_get_data(&temperature, &humidity);
        debug_printf("Temperature: %d, Humidity: %d\r\n", temperature, humidity);
      
        

        NV020D_send_cmd(0x00); // Send command to NV020D to play voice for temperature
        debug_printf("完成发送指令");
        debug_printf("BUSY after wait = %d\r\n", NV020D_BUSY_READ);

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