#include "mic.h"
#include "gpio.h"


//@brief  :获取麦克风的状态，返回值为Mic_type_value类型，返回MIC_OFF表示麦克风关闭，返回MIC_ON表示麦克风开启
Mic_type_value Inf_get_Mic_Value(void)\
{
    if(HAL_GPIO_ReadPin(MIC_IN_GPIO_Port, MIC_IN_Pin)==GPIO_PIN_RESET)
    {
        return MIC_ON;
    }
    else
    {
        return MIC_OFF;
    }
}