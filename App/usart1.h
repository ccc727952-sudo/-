#ifndef _USART1_H
#define _USART1_H
#include "system.h"
#include "stm32f10x.h"
#include "systick.h"
#include "stdio.h"
//缓冲区的大小
#define USART1_REC_LEN  200


void usart1_init(u32 baud);

// 定义串口接收回调函数类型（参数：数据长度、缓冲区指针）
typedef void (*USART1_RxCallback)(u16 len, u16 *buf);

// 声明全局回调函数指针
extern USART1_RxCallback usart1_rx_callback;

// 注册回调函数的接口
void USART1_RegisterRxCallback(USART1_RxCallback callback);

#endif