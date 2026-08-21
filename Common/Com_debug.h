#ifndef COM_DEBUG_H
#define COM_DEBUG_H

#include "main.h"
#include "usart.h"
#include "stdio.h"
#include "stdarg.h"

//1: define a log open switch, open when debug, close when release

//2：添加前缀， 补全文件名称和行号，方便定位
#define DEBUG_ENABLE 1
#ifdef DEBUG_ENABLE

//统一使用通用的宏去做日志输出
#define debug_printf(format,...) printf("[%s:%d] " format "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug_printf(...)
#endif /* DEBUG_ENABLE */

#endif /* COM_DEBUG_H */