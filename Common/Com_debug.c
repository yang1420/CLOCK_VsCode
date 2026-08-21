#include "Com_debug.h"

// used by syscalls.c's _write() to route printf output over UART1
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}