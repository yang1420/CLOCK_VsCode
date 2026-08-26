#include "App_freeRTOS.h"
#include "Com_debug.h"
#include "Key.h"
#include "touch.h"
#include "mic.h"
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
    while (1)
    {
        if(Inf_get_Mic_Value()==MIC_ON)
        {
            debug_printf("Mic is ON,当前值是1\r\n");
        }
        else
        {
            debug_printf("Mic is OFF,当前值是0\r\n");
        }
      
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 ms
    }
}

void App_freeRTOS_Init(void)
{
    ///1 create tasks
    xTaskCreate(task1, "Task 1", 128, NULL, 1, NULL);
    xTaskCreate(task2, "Task 2", 128, NULL, 1, NULL);
    // 2 start scheduler
    vTaskStartScheduler();
}