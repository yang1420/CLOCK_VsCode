#include "App_freeRTOS.h"
#include "Com_debug.h"
#include "Key.h"
#include "touch.h"
#include "mic.h"
#include "DS1302z.h"
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
       //测速实时时钟
       DS1302Z_Write_Byte(DS1302Z_CONTROL_REG, 0x00);  // 关闭写保护

       DS1302Z_Write_Byte(DS1302Z_YEAR_REG, 0x26);
       uint8_t year = DS1302Z_Read_Byte(DS1302Z_YEAR_REG);
       debug_printf("Current year: 0x%02X\r\n", year);
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