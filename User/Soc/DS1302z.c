#include "DS1302z.h"

void Inf_DS1302Z_Delay_us(uint32_t us)
{
    // Assuming the system clock is 72 MHz, each iteration of the loop takes approximately 1/72,000,000 seconds.
    // To achieve a delay of 'us' microseconds, we need to loop for 'us * (72 / 1)' iterations.
    // This is a rough approximation and may need calibration based on the actual clock speed and compiler optimizations.

     uint32_t count = us * 7; // Adjust this factor based on your clock speed
    while (count--)
    {
        __NOP(); // No Operation - prevents the compiler from optimizing the loop away
    }
}

//读取一个寄存器的值
uint8_t DS1302Z_Read_Byte(uint8_t reg_addr)
{
    //确保是一个读指令，最低位置1
    reg_addr |=(0x01);
    uint8_t data = 0;
    //1.初始化引脚
    DS_RST_H;
    DS_CLK_L;
    //2.拉高RST引脚，准备发送指令，，要延迟最少4us
    DS_RST_H;
    Inf_DS1302Z_Delay_us(5);
    //3.循环8次，低位优先发送指令
    //准备数据，然后在SCLK在上升沿的时候读取数据
    for (int i = 0; i < 8; i++)
    {
        if(reg_addr & (1<<i))
        {
            DS_IO_H;
        }
        else
        {
            DS_IO_L;
        }
        DS_CLK_H;
        Inf_DS1302Z_Delay_us(1);

        //4.重置时钟引脚，准备发送第二次数据
        DS_CLK_L;
    }  
    //5.接收数据  
    //读取点要释放IO
    DS_IO_H;//拉高释放，因为是OPEN_DRAIN输出模式
    for (uint8_t i = 0; i < 8; i++)
    {
       
        data |= (DS_IO_READ << i);
        if(i<7)
        {
            DS_CLK_H;
            DS_CLK_L;
        }
      
    }
    //6.拉低RST引脚，结束通信
    DS_RST_L;

    return data;
}

//写入一个寄存器的值
void DS1302Z_Write_Byte(uint8_t reg_addr, uint8_t data)
{
    //初始的地址确认 =>确认是一个写指令,最低位置写0
    reg_addr &=(0xfe);

    //1.初始化引脚DS_CLK_L,DS_IO_L,DS_RST_L;
    DS_RST_L;
    DS_CLK_L;
    
    //2.拉高RST引脚，准备发送指令
    DS_RST_H;
    Inf_DS1302Z_Delay_us(5);
    //3.循环8次，低位优先发送指令
    for (int i = 0; i < 8; i++)
    {
        if(reg_addr & (1<<i))
        {
            DS_IO_H;
        }
        else
        {
            DS_IO_L;
        }
        DS_CLK_H;
        Inf_DS1302Z_Delay_us(1);
        DS_CLK_L;
    }
    //4.准备写数据
    for(uint8_t i=0;i<8;i++)
    {
        if(data & (1<<i))
        {
            DS_IO_H;
        }
        else
        {
            DS_IO_L;
        }
        DS_CLK_H;
        Inf_DS1302Z_Delay_us(1);
        DS_CLK_L;
    }
    //5.拉低RST引脚，结束通信
    DS_RST_L;
}