#include "usart1.h"

void USART1_Init(u32 baudrate)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Pin = GPIO_Pin_9;//tx pin9, rx pin10
    gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;//将tx pin9设置为复用推挽模式，用于发送数据位
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpioInit);
    gpioInit.GPIO_Pin = GPIO_Pin_10;
    gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;//将rx pin10设置为输入浮空模式，用于接收数据位
    GPIO_Init(GPIOA,&gpioInit);

    USART_InitTypeDef usartInit;
    usartInit.USART_BaudRate = baudrate;
    usartInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usartInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usartInit.USART_Parity = USART_Parity_No;
    usartInit.USART_StopBits = USART_StopBits_1;
    usartInit.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&usartInit);
    USART_Cmd(USART1,ENABLE);

    USART_ClearFlag(USART1,USART_FLAG_RXNE);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//USART_IT_RXNE:接收数据寄存器不为空中断
    NVIC_InitTypeDef nvicInit;
    nvicInit.NVIC_IRQChannel = USART1_IRQn;
    nvicInit.NVIC_IRQChannelPreemptionPriority = 0;//0:最高优先级
    nvicInit.NVIC_IRQChannelSubPriority = 0;//0:最高子优先级
    nvicInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicInit);
}


//准备一个数组，用于存储接收的数据
u16 USART1_RX_BUF[USART1_BUF_LEN];
/*
认为连续接收到\r\n为一个完整的字符串
\r:回车符  0x0D
\n:换行符  0x0A

USART1_RX_STA

*/
u16 USART1_RX_STA = 0;

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
    {
        u16 data = USART_ReceiveData(USART1);
        if((USART1_RX_STA & 0x8000) == 0){
            if(USART1_RX_STA == 0x4000){
                if(data!=0x0A){
                    USART1_RX_STA = 0;
                }else{
                    USART1_RX_STA = 0x8000 | USART1_RX_STA;
                }
            }else{
                if(data==0x0D){
                    USART1_RX_STA |= 0x4000;
                }else{
                    USART1_RX_BUF[USART1_RX_STA&0x3FFF] = data;
                    USART1_RX_STA++;
                    if(USART1_RX_STA > USART1_BUF_LEN-1){
                        USART1_RX_STA=0;
                    }
                }
            }
        }
        USART_SendData(USART1,data);
    }
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}