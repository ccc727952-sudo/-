#include "adc_temp.h"

void ADC_init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    ADC_TempSensorVrefintCmd(ENABLE);//打开ADC内部温度传感器
    ADC_InitTypeDef adcInit;
    adcInit.ADC_Mode = ADC_Mode_Independent;
    adcInit.ADC_ScanConvMode = DISABLE;
    adcInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adcInit.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    adcInit.ADC_DataAlign = ADC_DataAlign_Right;
    adcInit.ADC_NbrOfChannel = 1;
    //adcInit.ADC_Resolution = ADC_Resolution_12b;
    ADC_Init(ADC1,&adcInit);
    ADC_Cmd(ADC1,ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));


    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能或者失能指定的ADC的软件转换启动功能
}

u16 get_adc_value(u8 channel,u8 tims){
    ADC_RegularChannelConfig(ADC1,channel,1,ADC_SampleTime_239Cycles5);
    u32 temp=0;
    for(u8 i = 0; i < tims; i++){
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);    
        while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));     
        temp += ADC_GetConversionValue(ADC1);
        delay_ms(5);
    }
    return temp / tims;
}