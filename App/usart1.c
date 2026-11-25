#include "usart1.h"


void usart1_init(u32 baud){
    //1.时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    //usart1的数据收发 PA9/PA10
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef gpioInitDef;
    gpioInitDef.GPIO_Mode=GPIO_Mode_AF_PP;
    gpioInitDef.GPIO_Pin=GPIO_Pin_9;//TX
    gpioInitDef.GPIO_Speed=GPIO_Speed_50MHz;
    //初始化GPIO
    GPIO_Init(GPIOA,&gpioInitDef);
    gpioInitDef.GPIO_Mode=GPIO_Mode_IN_FLOATING;//浮空输出
    gpioInitDef.GPIO_Pin=GPIO_Pin_10;//RX   
    GPIO_Init(GPIOA,&gpioInitDef);


    //初始化usart1
    USART_InitTypeDef usartInit;
    usartInit.USART_BaudRate=baud;//波特率
    usartInit.USART_WordLength=USART_WordLength_8b;//数据帧长度
    usartInit.USART_StopBits=USART_StopBits_1;//1个停止位
    usartInit.USART_Parity=USART_Parity_No;//不开启奇偶校验
    usartInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件流控制
    usartInit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//收发模式
    USART_Init(USART1,&usartInit);
    //使能
    USART_Cmd(USART1,ENABLE);

    //使能中断
    //USART_IT_TC 传输完成触发中断
    USART_ClearFlag(USART1, USART_FLAG_TC);
    //接收完成中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

    NVIC_InitTypeDef nvicInit;
    nvicInit.NVIC_IRQChannel=USART1_IRQn;
    nvicInit.NVIC_IRQChannelCmd=ENABLE;
    nvicInit.NVIC_IRQChannelPreemptionPriority=3;
    nvicInit.NVIC_IRQChannelSubPriority=2;
    NVIC_Init(&nvicInit);


}

//准备一个数组 缓存数据--等数据接收完毕以后 再返回数据
u16 USART1_RX_BUF[USART1_REC_LEN];
/*
u16  0000 0000 0000 0000  
认为连续接收到 \r\n 数据接收完毕 
\r = 13 回车  0x0D
\n = 10 换行  0x0A
USART1_RX_STA最高位的两个bit的作用1

如果接收到 \r                 0100 0000 0000 0000  = 0x4000
如果接收到 \r的下一个字符是\n  1000 0000 0000 0000  = 0x8000

USART1_RX_STA其他bit位的作用
记录接收到的下一个字节存放到u16数组的位置

*/
u16 USART1_RX_STA=0;


#if 0//不加回调函数
//写中断服务处理函数
void USART1_IRQHandler(){
    //监听对应的中断触发信号
    u16 data;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
    {
        //接收消息 --不能输出打印
        data=  USART_ReceiveData(USART1);
        if ((USART1_RX_STA&0x8000)==0)//数据接收还未完成
        {
            //判断是否已经接收到\r
            if (USART1_RX_STA&0x4000)//已经接收到一个\r
            {
                if (data!=0x0a) {
                    USART1_RX_STA=0;//重新开始从第一个位置开始放数据
                }else{//数据接收完毕
                    USART1_RX_STA|=0x8000;
                }
                                  
            }else{//还没接收到\r

                //当前的数据是不是 \r
                if(data==0x0d)USART1_RX_STA|=0x4000;
                else{
                    //正常的数据
                    //0100 0000 0000 0011
                    USART1_RX_BUF[USART1_RX_STA&0x3FFF]=data;
                    USART1_RX_STA++;
                    if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
                }
            }           
        }              
    }

}
#endif
#if 1//加回调函数
// 全局回调函数指针，初始为NULL
USART1_RxCallback usart1_rx_callback = NULL;

// 实现回调注册函数
void USART1_RegisterRxCallback(USART1_RxCallback callback) {
    usart1_rx_callback = callback;
}

// 中断服务函数
void USART1_IRQHandler(){
    u16 data;

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
    {
        data=  USART_ReceiveData(USART1);
        if ((USART1_RX_STA&0x8000)==0)//数据接收还未完成
        {
            if (USART1_RX_STA&0x4000)//已经接收到一个\r
            {
                if (data!=0x0a) {
                    USART1_RX_STA=0;//重新开始从第一个位置开始放数据
                }else{//数据接收完毕
                    USART1_RX_STA|=0x8000;

                    // 调用回调函数（传递数据长度和缓冲区指针）
                    if(usart1_rx_callback) {
                        u16 len = USART1_RX_STA & 0x3FFF; // 提取低14位作为数据长度
                        usart1_rx_callback(len, USART1_RX_BUF);
                    }
                    USART1_RX_STA = 0;
                }
                                  
            }else{//还没接收到\r

                if(data==0x0d)USART1_RX_STA|=0x4000;
                else{
                    USART1_RX_BUF[USART1_RX_STA&0x3FFF]=data;
                    USART1_RX_STA++;
                    if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
                }
            }           
        }              
    }

}
#endif 



// 重定向 printf 到 USART1
int fputc(int ch, FILE *f)
{
    //发送数据到串口
    USART_SendData(USART1, (uint8_t)ch);

    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

    return ch;
}
