#include "App_freeRTOS.h"
#include "Com_debug.h"
#include "Key.h"
//
//Just a test task;
//
void task1(void *pvParameters)
{
    (void)pvParameters; // unused
    while (1)
    {
        //debug_printf("Task 1 is running\n");

        //测速按键短按的逻辑
        Key_type_value key_value = Inf_get_Key_Value();
        if (key_value != KEY_NONE)
        {
            debug_printf("Key pressed: %d\n", key_value);
        }
        //vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
}
void task2(void *pvParameters)
{
    (void)pvParameters; // unused
    while (1)
    {
        //测试拨动开关
        if(Inf_get_LED_Value()==LED_ON)
        {
            debug_printf("LED is ON\n");
        }
        else
        {
            debug_printf("LED is OFF\n");
        }
        if(Inf_get_Light_Value()==LIGHT_ON)
        {
            debug_printf("常量模式\n");
        }
        else
        {
            debug_printf("声控模式\n");
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