#ifndef KEY_H
#define KEY_H
#include "Com_debug.h"
#include "gpio.h"

typedef enum 
{
  KEY_NONE = 0,
  KEY_TIME_SET,       // represents a key press event, short press
  KEY_TIME_SET_LONG,  // represents a long key press event,long time press(3s)
  KEY_UP,             // 上调
  KEY_DOWN,           // 下调
  KEY_ALARM_SET,      // 时钟设置
  KEY_ALARM_SET_LONG, // 时钟设置长按
  KEY_ALARM_EN,       // 开启时钟
  KEY_ALARM_5,        // 5天闹钟

} Key_type_value;


typedef enum
{
    LED_OFF = 0,
    LED_ON,
}LED_ON_Type_value;

typedef enum
{
    LIGHT_OFF = 0,
    LIGHT_ON,

}LIGHT_Type_value;


/**
    @brief  :硬件初始化一般需要初始化方法，对应着GPIO引脚的初始化
*/
void Inf_Key_Init(void);

uint8_t Inf_getkey_long_press(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);



//@brief  :获取按键值,一次读取一个值，读取当前是否是按键被按下的状态，
//          返回值为Key_type_value类型，返回KEY_NONE表示没有按键被按下，返回其他值表示对应的按键被按下
Key_type_value Inf_get_Key_Value(void);


//@brief  :获取LED灯的状态，返回值为LED_ON_Type_value类型，返回LED_OFF表示LED灯关闭，返回LED_ON表示LED灯开启
LED_ON_Type_value Inf_get_LED_Value(void);



//获取灯的状态，返回值为LIGHT_Type_value类型，返回LIGHT_OFF表示灯关闭，返回LIGHT_ON表示灯开启
LIGHT_Type_value Inf_get_Light_Value(void);
#endif /* KEY_H */
