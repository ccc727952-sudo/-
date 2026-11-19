#ifndef _MOTOR_H
#define _MOTOR_H
#include "system.h"
#include "stm32f10x.h"
#include "systick.h"

#define MOTOR_GPIO_PORT GPIOB
//控制正反转线路
#define AIN_PIN1 GPIO_Pin_0
#define AIN_PIN2 GPIO_Pin_1
//休眠
#define SLEEP_PIN GPIO_Pin_10
//状态反馈
#define FAULT_PIN GPIO_Pin_11



#define AIN1_BIT PBout(0)
#define AIN2_BIT PBout(1)
#define SLEEP_BIT PBout(10)
#define FAULT_BIT PBin(11)




void motor_init();


void DRV8833_Enable(void);
void DRV8833_Disable(void);
uint8_t DRV8833_IsFault(void);  // 1=故障, 0=正常

void M1_Forward(void);
void M1_Backward(void);
void M1_Brake(void);    // 刹车：AIN1=1, AIN2=1 快速停机
void M1_Coast(void);    // 自由滑行：AIN1=0, AIN2=0 慢慢停


#endif