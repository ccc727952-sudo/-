#include "motor.h"

void motor_init(){
    //1.初始化时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode=GPIO_Mode_Out_PP;
    initDef.GPIO_Speed=GPIO_Speed_50MHz;
    initDef.GPIO_Pin=AIN_PIN1|AIN_PIN2|SLEEP_PIN;
    GPIO_Init(MOTOR_GPIO_PORT,&initDef);
    //默认让 电机停止转动
    GPIO_WriteBit(MOTOR_GPIO_PORT,AIN_PIN1|AIN_PIN2|SLEEP_PIN,Bit_RESET);

    //故障线路初始化
    initDef.GPIO_Mode=GPIO_Mode_IPU;
    initDef.GPIO_Pin=FAULT_PIN;
    GPIO_Init(MOTOR_GPIO_PORT,&initDef);


}


void DRV8833_Enable(void){
    //设置高电平启动
    SLEEP_BIT=1;

}
void DRV8833_Disable(void){
    SLEEP_BIT=0;
}
uint8_t DRV8833_IsFault(void){  // 1=故障, 0=正常
    return FAULT_BIT==0?1:0;

}
void M1_Forward(void){
   
    AIN1_BIT=0;
    AIN2_BIT=1;

}
void M1_Backward(void){
    AIN1_BIT=1;
    AIN2_BIT=0;

}
void M1_Brake(void){    // 刹车：AIN1=1, AIN2=1 快速停机
    AIN1_BIT=1;
    AIN2_BIT=1;
}    
void M1_Coast(void){    // 自由滑行：AIN1=0, AIN2=0 慢慢停
    AIN1_BIT=0;
    AIN2_BIT=0;

}    