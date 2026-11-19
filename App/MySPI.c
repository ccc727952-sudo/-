#include "MySPI.h"

/**
  * 函    数：SPI写SS引脚电平，SS仍由软件模拟
  * 参    数：BitValue 协议层传入的当前需要写入SS的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SS为低电平，当BitValue为1时，需要置SS为高电平
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOD, GPIO_Pin_11, (BitAction)BitValue);		//根据BitValue，设置CS(PD11)引脚的电平
}

/**
  * 函    数：SPI写SCK引脚电平
  * 参    数：BitValue 需要写入SCL的电平，范围0~1
  * 返 回 值：无
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_3, (BitAction)BitValue);		//根据BitValue，设置SCL(PB3)引脚的电平
}

/**
  * 函    数：SPI写MOSI引脚电平
  * 参    数：BitValue 需要写入SDA的电平，范围0~1
  * 返 回 值：无
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)BitValue);		//根据BitValue，设置SDA(PB5)引脚的电平
}

/**
  * 函    数：SPI初始化
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//开启GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//开启GPIOD的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//开启AFIO时钟，重映射寄存器才能写入
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	//PB3默认为JTDO，需关闭JTAG(保留SWD)才能当普通IO使用
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//将PB3(SCL)和PB5(SDA)初始化为推挽输出
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					//将PD11(CS)初始化为推挽输出
	
	/*软件SPI无需配置SPI外设，时序由MySPI_SwapByte模拟*/
	
	/*设置默认电平*/
	MySPI_W_SS(1);											//CS默认高电平
	MySPI_W_SCK(0);											//SCL默认低电平(模式0空闲电平)
}

/**
  * 函    数：SPI起始
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);				//拉低SS，开始时序
}

/**
  * 函    数：SPI终止
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);				//拉高SS，终止时序
}

/**
  * 函    数：SPI交换传输一个字节，使用SPI模式0
  * 参    数：ByteSend 要发送的一个字节
  * 返 回 值：接收的一个字节
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i;
	
	for (i = 0; i < 8; i ++)									//循环8次，依次发送8位
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i));					//SDA输出当前最高位
		MySPI_W_SCK(1);											//SCL拉高，从机在上升沿采样
		MySPI_W_SCK(0);											//SCL拉低，准备发送下一位
	}
	
	return 0x00;											//TFT屏只写不读，返回0
}
