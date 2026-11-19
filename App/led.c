#include "led.h"

void led_init(){
    //1.初始化时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode=GPIO_Mode_Out_PP;
    initDef.GPIO_Speed=GPIO_Speed_50MHz;
    initDef.GPIO_Pin=LED1_GPIO_Pin|LED2_GPIO_Pin|LED3_GPIO_Pin|LED4_GPIO_Pin|
                     LED5_GPIO_Pin|LED6_GPIO_Pin|LED7_GPIO_Pin|LED8_GPIO_Pin;
    GPIO_Init(LED_GPIO_PORT,&initDef);
    //默认都不亮 
    LED1=1;  LED2=1;  LED3=1;  LED4=1; LED5=1; LED6=1; LED7=1;  LED8=1;

}


//全部 亮
void led_on(){
    /*
        解决思路:
            方案一: 使用位带操作 全部设置 0
            方案二:
                8颗灯 对应 8个bit位
                0000 0000  依次写入到 pin_0  pin_1 ... pin_7
                0000 0000 =u8; 
    */
    for (u8 i = 0; i < 8; i++)
    {
        //每执行一次 往对应的bit位里面写一个0进去
        GPIO_WriteBit(LED_GPIO_PORT,GPIO_Pin_0<<i,Bit_RESET);

    }
    

}
//全部 灭
void led_off(){
    for (u8 i = 0; i < 8; i++)
    {
        //每执行一次 往对应的bit位里面写一个0进去
        GPIO_WriteBit(LED_GPIO_PORT,GPIO_Pin_0<<i,Bit_SET);

    }

}


//跑马灯
/*
    思路:
        ~0000 0001     1111 1110 
        ~0000 0010     1111 1101     
        ~0000 0100     1111 1011    
        ~0000 1000     1111 0111  
                       0000 0001  
    此处函数解决把一个8个bit的数据写到对应 pin_0 ~ pin7    


*/

void led_marquee(u8 data){
    // 1111 1110 
    //1.处理的bit位数量是8
    for (u8 i = 0; i <8; i++)
    {
        //判断要处理的bit位是高电平还是低电平
        if (data&0x01)//高电平
        {
            GPIO_WriteBit(LED_GPIO_PORT,GPIO_Pin_0<<i,Bit_SET);
        }else{//最低位是低电平

            GPIO_WriteBit(LED_GPIO_PORT,GPIO_Pin_0<<i,Bit_RESET);
        }        
        //每处理一个bit位 丢弃最低位
        data>>=1;//第一次循环结束   0111 1111   第二次循环结束   0011 1111
    }
}


void led_run(){
    

    for (u8 i = 0; i < 8; i++)
    {
        led_marquee(~(0x01<<i));
        delay_ms(100);
    }
    

}


void led_smart(){
    LED1=0;
    delay_ms(100);
    LED1=1;
    LED2=0;
    delay_ms(100);
    LED2=1;
    LED3=0;
    delay_ms(100);
    LED3=1;
    LED4=0;
    delay_ms(100);
    LED4=1;
    LED5=0;
    delay_ms(100);
    LED5=1;
    LED6=0;
    delay_ms(100);
    LED6=1;
    LED7=0;
    delay_ms(100);
    LED7=1;
    LED8=0;
    delay_ms(100);
    LED8=1;
    LED1=0;

}