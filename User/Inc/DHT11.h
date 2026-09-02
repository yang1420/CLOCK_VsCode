#ifndef DHT11_H
#define DHT11_H
#include "gpio.h"

#define DHT11_DATA_H HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin, GPIO_PIN_SET)
#define DHT11_DATA_L HAL_GPIO_WritePin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin, GPIO_PIN_RESET)

#define DHT11_DATA_READ HAL_GPIO_ReadPin(DHT11_DATA_GPIO_Port, DHT11_DATA_Pin)



//
//@brief:DHT11模块，上电后1s才能使用
//

void Inf_DHT11_Init(void);

//
//@brief:获取DHT11模块的温度和湿度数据,只保留温湿度数据
//
void Inf_DHT11_get_data(int8_t *temperature, int8_t *humidity);
#endif // DHT11_H