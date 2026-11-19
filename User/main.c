#include "stm32f10x.h"
#include "system.h"
#include "systick.h"
#include "key.h"
#include "usart1.h"
#include "stdio.h"
#include "adc_temp.h"
#include "lcd.h"
#include "image.h"


int fputc(int ch, FILE *f){
	// send_byte((uint8_t)ch);
	USART_SendData(USART1, (uint8_t)ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	return ch;
}


int main(void)
{
	systick_init();
	key_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	USART1_Init(115200);
	printf("hello world\n");
	
	lcd_init();				//LCD初始化，内部会先清屏为白色
	lcd_show_line(RED);		//在y=10处画一条红线
	lcd_show_picture(gImage_image2);	//显示图片

	while(1){

	}
		
}
