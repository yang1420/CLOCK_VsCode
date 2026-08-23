#include "key.h"
#include "FreeRTOS.h"
#include "task.h"




void Inf_Key_Init(void)
{
    //Already invoke by the MX_GPIO_Init() function in the main.c file, so no need to initialize again here.

}
//
//@brief:获取指定按键是否被按下
//uint8_t =1 表示按下，=0表示没有按下
uint8_t Inf_getkey_press(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
     if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)==GPIO_PIN_RESET)
    {
        //1.1:debounce
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 10 ms
        if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)==GPIO_PIN_RESET)
        {
            //1.2:wait for release
            while(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)==GPIO_PIN_RESET)
            {
                vTaskDelay(pdMS_TO_TICKS(1)); // Delay for 1 ms
            }
            return 1;
        }
    }
    return 0;
}


//@brief  :获取按键值,一次读取一个值，读取当前是否是按键被按下的状态，
//          返回值为Key_type_value类型，返回KEY_NONE表示没有按键被按下，返回其他值表示对应的按键被按下
Key_type_value Inf_get_Key_Value(void)
{
    // check short press =>按键的值默认是1，按下才是0 =>抬起才生效
   if(Inf_getkey_press(UP_GPIO_Port, UP_Pin)==1)
   {
     return KEY_UP;
   }
    elseif(Inf_getkey_press(DOWN_GPIO_Port, DOWN_Pin)==1)
    {
        return KEY_DOWN;
    }
    else if(Inf_getkey_press(Alarm_EN_GPIO_Port, Alarm_EN_Pin)==1)
    {
        return KEY_ALARM_EN;
    }
    else if(Inf_getkey_press(Alarm_5_GPIO_Port, Alarm_5_Pin)==1)
    {
        return KEY_ALARM_5;
    }
    

    //check long press


    //No key pressed
    return KEY_NONE;
}



//@brief  :获取LED灯的状态，返回值为LED_ON_Type_value类型，返回LED_OFF表示LED灯关闭，返回LED_ON表示LED灯开启
LED_ON_Type_value Inf_get_LED_Value(void);



//获取灯的状态，返回值为LIGHT_Type_value类型，返回LINE_OFF表示灯关闭，返回LINE_ON表示灯开启
LIGHT_Type_value Inf_get_Light_Value(void);