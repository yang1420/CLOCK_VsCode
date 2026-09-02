#include "DHT11.h"
#include "freeRTOS.h"
#include "task.h"
#include "DS1302z.h"
#include "Com_debug.h"

//用于存储每次读取的值
uint8_t data[5]={0};
//
            
//@brief:DHT11模块，上电后1s才能使用
//
void Inf_DHT11_Init(void)
{
    DHT11_DATA_H; // 将DATA引脚设置为高电平
    vTaskDelay(pdMS_TO_TICKS(1000)); // 上电后延迟1s
}

//
//@brief:获取DHT11模块的温度和湿度数据,只保留温湿度数据
//
void Inf_DHT11_get_data(int8_t *temperature, int8_t *humidity)
{
    int8_t temp=0;
    int8_t hum=0;
    //1.发送起始信号，拉低引脚18-30ms
    DHT11_DATA_L; // 拉低DATA引脚
    vTaskDelay(pdMS_TO_TICKS(20)); // 延迟20ms
    DHT11_DATA_H; // 拉高DATA引脚

    //2. 接收DHT11的响应信号，回顾高低电平时间有意义吗？ => 没有， 唯一的英语是释放资源
    //CPU到点了在回来看看引脚（时间不足1ms，释放也没意义）
    //如果DHT11坏了，不能返回响应信号，写一个超时的逻辑
    uint32_t timeout =0xffffff;
    while(DHT11_DATA_READ == GPIO_PIN_SET && timeout--) // 等待DHT11拉低引脚
    {
        //等待响应信号拉低
    }
     while(DHT11_DATA_READ == GPIO_PIN_RESET && timeout--) // 等待DHT11拉高引脚
    {
        //发送低电平的响应信号，会持续83us
        //等待响应信号拉高
    }
     while(DHT11_DATA_READ == GPIO_PIN_SET && timeout--) // 等待DHT11拉低引脚
    {
        //发送高电平的响应信号，会持续87us
        //等待响应信号拉低
    }
    //3.判断是不是超时了
    if(timeout == 0)
    {
        //超时处理
        debug_printf("DHT11响应超时\r\n");
        return;
    }

    //4.接收数据，数据格式5个字节，高位在前
    // uint8_t humidity_int = 0;
    // uint8_t humidity_frac = 0;
    // uint8_t temperature_int = 0;
    // uint8_t temperature_frac = 0;
    // uint8_t checksum = 0;
    //接收5个字节的数据
    // for(uint8_t i = 0; i < 8; i++)
    // {
    //     //第一个字节是湿度整数部分
    //     //4.1首先是54us的低电平信号
    //     uint32_t timeout2 = 0xffffff;
    //     while(DHT11_DATA_READ == GPIO_PIN_RESET ) // 等待DHT11拉高引脚
    //     {
    //         //等待低电平结束
    //     }
    //     //4.2延时一个27-68us，使用40us
    //     Inf_Delay_us(40);

    //     if(DHT11_DATA_READ == GPIO_PIN_SET)
    //     {
    //         //如果引脚为高电平，表示接收到的是1
    //         humidity_int |= (1 << (7 - i)); // 将对应位设置为1、
    //         //等待拉低，进入下一轮
    //         while(DHT11_DATA_READ == GPIO_PIN_SET)
    //         {
    //             //等待高电平结束
    //         }
    //     }

    //     else
    //     {
    //         //如果引脚为低电平，表示接收到的是0
    //        //可以不需要写，因为默认是0
    //     }
    // }

    //使用双重循环写一遍代码，表示循环5次
    for(uint8_t i = 0; i < 5; i++)
    {
        data[i] = 0; // 初始化当前字节为0
        for(uint8_t j = 0; j < 8; j++)
        {
            //等待拉高读取数据
            while(DHT11_DATA_READ == GPIO_PIN_RESET)
            {
                //等待低电平结束
            }
            //延时一个27-68us，使用40us
            Inf_Delay_us(40);
            if(DHT11_DATA_READ == GPIO_PIN_SET)
            {
                //读取数据是1，写入到数据中
                data[i] |= (1 << (7 - j)); // 将对应位设置为1
                //等待拉低，进入下一轮
                while(DHT11_DATA_READ == GPIO_PIN_SET)
                {
                    //等待高电平结束
                }
            }
            else
            {
                //读取数据是0，不需要做任何操作，因为默认是0
            }
        }   
    }
    //5.校验数据
    uint32_t sum= data[0] + data[1] + data[2] + data[3];
    if((uint8_t)sum == data[4])
    {
        //通过校验，可以赋值
        hum=data[0]; // 湿度整数部分

        //温度整数部分
        temp=data[2]; // 温度整数部分
        if(data[3] & 0x80)
        {
            //温度是负数
            temp = -temp;
        }
        //赋值返回
        *temperature = temp;
        *humidity = hum;
    }
    else
    {
        //校验失败，数据不可信
        debug_printf("DHT11数据校验失败\r\n");
    }

}