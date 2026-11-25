#define MUSIC_C
#include "music.h"
#include "beep.h"
#include "key.h"

u8 KeyNum;
/*----------------------------------------------------------------------------------*/


void PlayMusic(int num,uc16 music[])
{//第一个参数为音符个数，第二个参数为一个数组（包含频率和持续时间）
 
    u16 i,e;
	
    for (i=1;i<num;i++)
	{//音符个数
		if(music[i] != 0)
		for(e=0;e<music[i*2]*music[i*2+1]/1000;e++)
		{//计算持续时间
 
			beep_on();
 
			delay_us(465000/music[i*2]);
 
			beep_off();
 
			delay_us(500000/music[i*2]);
 
		}
		delay_ms(50);
		if(music[i] == 0) delay_ms(150);
		KeyNum=key_scan(1);
		if(KeyNum == 2)
		{	
			beep_off();
			break;
		}
    }
 
}