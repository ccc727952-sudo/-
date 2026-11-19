#ifndef _LED_H
#define _LED_H
#include "system.h"
#include "stm32f10x.h"
#include "systick.h"

#define LED_GPIO_PORT GPIOF
#define LED1_GPIO_Pin GPIO_Pin_0
#define LED2_GPIO_Pin GPIO_Pin_1
#define LED3_GPIO_Pin GPIO_Pin_2
#define LED4_GPIO_Pin GPIO_Pin_3
#define LED5_GPIO_Pin GPIO_Pin_4
#define LED6_GPIO_Pin GPIO_Pin_5
#define LED7_GPIO_Pin GPIO_Pin_6
#define LED8_GPIO_Pin GPIO_Pin_7

#define LED1 PFout(0)
#define LED2 PFout(1)
#define LED3 PFout(2)
#define LED4 PFout(3)
#define LED5 PFout(4)
#define LED6 PFout(5)
#define LED7 PFout(6)
#define LED8 PFout(7)



void led_init();
//全部 亮
void led_on();
//全部 灭
void led_off();

//跑马灯
void led_marquee(u8 data);

//跑马灯调用代码
void led_run();


void led_smart();

#endif