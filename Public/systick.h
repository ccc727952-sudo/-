#ifndef _H_SYSTICK
#define _H_SYSTICK
#include "stm32f10x.h"


//1.提供一个函数计算1us的嘀嗒数 和1ms的嘀嗒数

void systick_init();

//延迟多少us
void delay_us(u32 us);
//延迟多少ms
void delay_ms(u16 ms);

#endif