#include "servoMotor.h"

// 初始化函数：配置PA2为TIM2_CH3的PWM输出
void Servo_PWM_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    // 1. 使能时钟
    // 使能定时器TIM2时钟 (APB1总线)[reference:7]
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // 使能GPIOA时钟 (APB2总线)[reference:8]
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // 2. 配置GPIO引脚 (PA2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    // 设置为复用推挽输出模式[reference:9]
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 配置定时器时基
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;      // 自动重装载值 (ARR)，决定PWM周期 20ms[reference:10]
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;      // 预分频器 (PSC)，得到1us的计数频率[reference:11]
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式[reference:12]
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 4. 配置PWM输出通道 (TIM2_CH3)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;   // PWM模式1[reference:13]
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能输出[reference:14]
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 输出极性为高电平有效[reference:15]
    TIM_OCInitStructure.TIM_Pulse = 0;                  // 初始比较值 (CCR)[reference:16]
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);            // 注意：通道3使用 OC3Init[reference:17]

    // 5. 使能预装载寄存器
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);   // 使能TIM2_CH3的预装载寄存器[reference:18]
    TIM_ARRPreloadConfig(TIM2, ENABLE);                 // 使能自动重装载预装载寄存器[reference:19]

    // 6. 使能定时器
    TIM_Cmd(TIM2, ENABLE);                              // 启动TIM2[reference:20]
}

// 控制函数：设置舵机角度 (0° ~ 180°)
// 输入：angle 0~180
void Servo_SetAngle(uint8_t angle) {
    uint16_t pulse_width;
    
    // 将0-180°映射到 500-2500 (对应0.5ms-2.5ms高电平)
    // 公式: pulse = 500 + (angle * 2000) / 180
    // 注意：为防止超出范围，对angle进行限制
    if (angle > 180) angle = 180;
    
    pulse_width = 500 + (uint16_t)((uint32_t)angle * 2000 / 180);
    
    // 通过TIM2的通道3设置比较值 (CCR)[reference:21]
    TIM_SetCompare3(TIM2, pulse_width);
}
