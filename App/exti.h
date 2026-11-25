#ifndef _EXTI_H
#define _EXTI_H
#include "system.h"
#include "stm32f10x.h"
#include "systick.h"

extern void Servo_PWM_Init(void);
extern void Servo_SetAngle(uint8_t angle);

//中断初始化
//使用中断检测按键是否按下  并依次点亮led1-led4
void exti_init();

#endif