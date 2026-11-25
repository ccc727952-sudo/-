#include "adc_temp.h"

void ADC_init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//使能ADC1时钟
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    ADC_TempSensorVrefintCmd(ENABLE);//打开ADC内部温度传感器
    ADC_InitTypeDef adcInit;
    adcInit.ADC_Mode = ADC_Mode_Independent;//独立模式，单通道转换
    adcInit.ADC_ScanConvMode = DISABLE;//单通道转换，不开启扫描转换模式
    adcInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发转换，不开启外部触发转换
    adcInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发转换，不开启外部触发转换
    adcInit.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
    adcInit.ADC_NbrOfChannel = 1;//单通道转换，不开启扫描转换模式
    //adcInit.ADC_Resolution = ADC_Resolution_12b;
    ADC_Init(ADC1,&adcInit);//初始化ADC1
    ADC_Cmd(ADC1,ENABLE);//使能ADC1

    ADC_ResetCalibration(ADC1);//复位ADC1校准寄存器
    while(ADC_GetCalibrationStatus(ADC1));//等待校准完成
    ADC_StartCalibration(ADC1);//启动ADC1校准
    while(ADC_GetCalibrationStatus(ADC1));//等待校准完成

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的ADC的软件转换启动功能
}

u16 get_adc_value(u8 channel,u8 tims){
    ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_239Cycles5);//配置ADC1的通道，采样时间为239个周期
    u32 temp=0;
    for(u8 i = 0; i < tims; i++){//循环tims次，获取tims个转换值
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);    
        while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));     
        temp += ADC_GetConversionValue(ADC1);
        delay_ms(5);
    }
    return temp / tims;
}