#include "App_freeRTOS.h"
#include "Com_debug.h"
#include "Key.h"
#include "touch.h"
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
        //测速触摸开关
        if (Inf_get_Touch_Value() == TOUCH_PRESS)
        {
             debug_printf("被触摸了\r\n");
        }
        else
        {
             debug_printf("未被触摸\r\n");
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
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