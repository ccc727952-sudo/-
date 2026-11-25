#ifndef _beep_H
#define _beep_H
#include "system.h"
#include "stm32f10x.h"

#define BEEP_GPIO_PORT GPIOB
#define BEEP_GPIO_Pin GPIO_Pin_8

#define BEEP PBout(8)

void beep_init();
void beep_on();
void beep_off();


#endif