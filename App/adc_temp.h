#ifndef __ADC_TEMP_H__
#define __ADC_TEMP_H__
#include "stm32f10x.h"
#include "systick.h"

void ADC_init();

u16 get_adc_value(u8 channel,u8 tims);

#endif
