#ifndef TOUCH_H
#define TOUCH_H
#include "gpio.h"

typedef enum
{
    TOUCH_NONE = 0,
    TOUCH_PRESS,      
   
} Touch_type_value;
//
//@brief:获取当前触摸开关的值
//
Touch_type_value Inf_get_Touch_Value(void);

#endif /* TOUCH_H */