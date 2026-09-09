#include "NV020D.h"

void NV020D_Init(void) {
    // Initialization code for NV020D
    vTaskDelay(pdMS_TO_TICKS(500)); // Example delay for initialization
}

void NV020D_send_byte(uint8_t data) {
    // Code to send a byte of data to NV020D
    // This could involve setting GPIO pins, etc.
    //1.初始化
    NV020D_CLK_H;

    //提前设置好第一个值
    if(data & (1))
    {
        NV020D_DATA_H;
        
    }
    else
    {
        NV020D_DATA_L;
    }
    //NV020D_DATA_H; // Set data line high initially


    //2.发送启示命令
    NV020D_CLK_L;
    if(data == 0xf1)
    
    vTaskDelay(pdMS_TO_TICKS(4)); // Delay for clock low

    for(uint8_t i = 0; i < 8; i++)
    {
        if(data & (1<<i))
        {
            NV020D_DATA_H;
        
        }
        else
        {
            NV020D_DATA_L;
        }
        NV020D_CLK_L;
        //vTaskDelay(pdMS_TO_TICKS(1)); // Delay for clock low
        Inf_Delay_us(400); // Delay for clock low
        NV020D_CLK_H;
        //vTaskDelay(pdMS_TO_TICKS(1)); // Delay for clock high
        Inf_Delay_us(400); // Delay for clock high
    }
    
    NV020D_DATA_H;
}


void NV020D_send_cmd(uint8_t cmd) {
    //等待不忙
    debug_printf("等待上一个结束");
    debug_printf("BUSY before wait = %d\r\n", NV020D_BUSY_READ);

     while(NV020D_BUSY_READ == GPIO_PIN_RESET) {
       vTaskDelay(pdMS_TO_TICKS(10)); // Wait for NV020D to be ready
    }

    vTaskDelay(pdMS_TO_TICKS(100)); //两个指令之间间隔100ms


  


    // Command sending code for NV020D
    NV020D_send_byte(0xf1); // Send the command byte
    //0-0xdf表示播放对应下标位置的语音
    NV020D_send_byte(cmd); // Send the actual command
    NV020D_send_byte(0xf3); // Send a dummy byte if required
    uint8_t sum = (uint8_t)(0xf1 + cmd + 0xf3); // Calculate checksum, left last 8 bits
    NV020D_send_byte(sum); // Send the checksum byte
}
