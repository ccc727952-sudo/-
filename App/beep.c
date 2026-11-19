#include "beep.h"


void beep_init(){
	//1.使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//2.初始化gpio
	GPIO_InitTypeDef initDef;
	initDef.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	initDef.GPIO_Pin=BEEP_GPIO_Pin;
	initDef.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(BEEP_GPIO_PORT,&initDef);
}


