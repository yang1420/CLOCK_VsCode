#ifndef NV020D_H
#define NV020D_H
#include "gpio.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DS1302z.h"
#include "Com_debug.h"


#define NV020D_CLK_H HAL_GPIO_WritePin(NVD_CLK_GPIO_Port, NVD_CLK_Pin, GPIO_PIN_SET)
#define NV020D_CLK_L HAL_GPIO_WritePin(NVD_CLK_GPIO_Port, NVD_CLK_Pin, GPIO_PIN_RESET)

#define NV020D_DATA_H HAL_GPIO_WritePin(NVD_SDA_GPIO_Port, NVD_SDA_Pin, GPIO_PIN_SET)
#define NV020D_DATA_L HAL_GPIO_WritePin(NVD_SDA_GPIO_Port, NVD_SDA_Pin, GPIO_PIN_RESET)

#define NV020D_BUSY_READ HAL_GPIO_ReadPin(NVD_BUSY_GPIO_Port, NVD_BUSY_Pin)



/** @brief NV020D initialization function

  * @return None
  */
void NV020D_Init(void);

//
//@brief: send a command to NV020D
//
void NV020D_send_cmd(uint8_t cmd);


#endif