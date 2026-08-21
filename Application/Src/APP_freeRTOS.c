#include "App_freeRTOS.h"
#include "Com_debug.h"
//
//Just a test task;
//
void task1(void *pvParameters)
{
    (void)pvParameters; // unused
    while (1)
    {
        debug_printf("Task 1 is running\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000 ms
    }
}

void App_freeRTOS_Init(void)
{
    ///1 create tasks
    xTaskCreate(task1, "Task 1", 128, NULL, 1, NULL);
    // 2 start scheduler
    vTaskStartScheduler();
}