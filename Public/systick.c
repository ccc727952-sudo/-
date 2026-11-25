#include "systick.h"

static u8 fac_us;
static u16 fac_ms;

void systick_init(){
	//1.设置时钟源 默认是系统时钟72Mhz
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//系统时钟打8分频
	//2.计算1us嘀嗒次数
	fac_us = 72/8; // 9
	//3.计算1ms嘀嗒的次数
	fac_ms = fac_us*1000; //9000
}


//延迟多少us
void delay_us(u32 us){
	//假设调用处  delay_us(1000);
	//计算1000us对应的嘀嗒次数
	SysTick->LOAD =fac_us*us;
	//清空一下val寄存器
	SysTick->VAL=0x00;
	//开始计时 控制寄存器的0位设置1
	/*
		1101 0010
	| 0000 0001  	
	-------------
		1101 0011
	
		1101 0010
	& 0000 0001  	
	-------------
		0000 0000
		3&5 
		011
		101
	
	*/
	//不影响其他位只是把最低位设置为1 --开始计时
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	//及时检查计时是否结束
	u32 temp;
	do{
		//获取控制寄存器的值
		temp=SysTick->CTRL;
		//(temp&0x01)已经开始计时状态
		//
	}while((temp&0x01) && !(temp&0x01<<16));
	//结束本轮计时  在不影响其他bit的情况把最低位变为0
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	//清空一下val寄存器
	SysTick->VAL=0x00;

}
/*
//延迟多少ms
void delay_ms(u16 ms){
	//假设调用处  delay_us(1000);
	//计算1000us对应的嘀嗒次数
	SysTick->LOAD =fac_ms*ms;
	//清空一下val寄存器
	SysTick->VAL=0x00;
	//开始计时 控制寄存器的0位设置1
	//不影响其他位只是把最低位设置为1 --开始计时
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	//及时检查计时是否结束
	u32 temp;
	do{
		//获取控制寄存器的值
		temp=SysTick->CTRL;
		//(temp&0x01)已经开始计时状态
		//
	}while((temp&0x01) && !(temp&0x01<<16));
	//结束本轮计时  在不影响其他bit的情况把最低位变为0
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	//清空一下val寄存器
	SysTick->VAL=0x00;
}*/

void delay_ms(u16 ms){
	while(ms--){
		delay_us(1000);
	}
}

