#ifndef _KEY_H
#define _KEY_H
#include "system.h"
#include "stm32f10x.h"
#include "systick.h"

#define KEY_GPIO_PORT GPIOA
#define KEY1_PIN GPIO_Pin_15
#define KEY2_PIN GPIO_Pin_8
#define KEY3_PIN GPIO_Pin_7
#define KEY4_PIN GPIO_Pin_6

#define KEY1 PAin(15)
#define KEY2 PAin(8)
#define KEY3 PAin(7)
#define KEY4 PAin(6)



void key_init();

/**
 * @param mode :模式选择 0:一次  1:检测多次
 * 
 * @return 返回值 0代表没有任何按键按下
 *         1:key1
 *         2:key2
 *         3:key3
 *         4:key4  
 */
u8 key_scan(u8 mode);




#endif