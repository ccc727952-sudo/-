#ifndef __USART1_H__
#define __USART1_H__

#include "stm32f10x.h"
#define USART1_BUF_LEN 1024  //接收缓冲区长度

void USART1_Init(u32 baudrate);

#endif