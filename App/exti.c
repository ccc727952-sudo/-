#include "exti.h"
#include "led.h"


void exti_init(){
    //配置NVIC 中断源  中断优先级
     // 1.开启AFIO时钟，EXTI配置必须
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //PA15默认是JTAG的JTDI，必须关闭JTAG(保留SWD)才能当普通IO/EXTI用
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    //按键接GND，配置为上拉输入
    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Mode = GPIO_Mode_IPU;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    gpioInit.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_15;
    GPIO_Init(GPIOA, &gpioInit);

    NVIC_InitTypeDef nvicInit;
    nvicInit.NVIC_IRQChannel=EXTI9_5_IRQn;//中断信号源
    nvicInit.NVIC_IRQChannelPreemptionPriority=3;//抢占式优先级
    nvicInit.NVIC_IRQChannelSubPriority=2;//响应式优先级
    nvicInit.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&nvicInit);

    nvicInit.NVIC_IRQChannel=EXTI15_10_IRQn;//中断信号源
    NVIC_Init(&nvicInit);


    //GPIO_EXTILineConfig 选择 GPIO 管脚用作外部中断线路
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
    //中断信号 ---外部中断  GPIO触发信号
    EXTI_InitTypeDef extiInit;
    extiInit.EXTI_Line=EXTI_Line6|EXTI_Line7|EXTI_Line8; //中断线路
    extiInit.EXTI_Mode=EXTI_Mode_Interrupt;//中断触发
    extiInit.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发 按键按下的时候 电平状态从高变低
    extiInit.EXTI_LineCmd=ENABLE;
    EXTI_Init(&extiInit);

    extiInit.EXTI_Line=EXTI_Line15;
    EXTI_Init(&extiInit);

}

//EXTI9_5_IRQn中断信号的处理函数
void EXTI9_5_IRQHandler(){
    delay_ms(10);//消抖
    if(EXTI_GetITStatus(EXTI_Line6)) {EXTI_ClearITPendingBit(EXTI_Line6); if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==0){LED4=!LED4;Servo_SetAngle(0);}}
    if(EXTI_GetITStatus(EXTI_Line7)) {EXTI_ClearITPendingBit(EXTI_Line7); if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)==0){LED3=!LED3;Servo_SetAngle(90);}}
    if(EXTI_GetITStatus(EXTI_Line8)) {EXTI_ClearITPendingBit(EXTI_Line8); if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0){LED2=!LED2;Servo_SetAngle(180);}}
}

//EXTI15_10_IRQn 中断信号的处理函数
void EXTI15_10_IRQHandler(){
    delay_ms(10);//消抖
    if(EXTI_GetITStatus(EXTI_Line15)) {EXTI_ClearITPendingBit(EXTI_Line15); if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0){LED1=!LED1;Servo_SetAngle(45);}}
}