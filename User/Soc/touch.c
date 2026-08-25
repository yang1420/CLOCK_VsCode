#include "touch.h"


Touch_type_value Inf_get_Touch_Value(void)
{
    // Implementation for getting touch value
    if(HAL_GPIO_ReadPin(TOUCH_GPIO_Port, TOUCH_Pin)==GPIO_PIN_RESET)
    {
        return TOUCH_PRESS;
    }
    else
    {
        return TOUCH_NONE;
    }
}