#include "jkey.h"
#include "stdio.h"
#include "usart1.h"

void jkey_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}


u8 jkey_scan(void)
{
    H1=0;H2=0;H3=0;H4=0;
    if(L1==0||L2==0||L3==0||L4==0){
        delay_ms(10);
        H1=0;H2=1;H3=1;H4=1;
        if(L1==0){while(L1==0); printf("1\n");return 1;}
        if(L2==0){while(L2==0); printf("2\n");return 2;}
        if(L3==0){while(L3==0); printf("3\n");return 3;}
        if(L4==0){while(L4==0); printf("4\n");return 4;}
        
        H1=1;H2=0;H3=1;H4=1;
        if(L1==0){while(L1==0); printf("5\n");return 5;}
        if(L2==0){while(L2==0); printf("6\n");return 6;}
        if(L3==0){while(L3==0); printf("7\n");return 7;}
        if(L4==0){while(L4==0); printf("8\n");return 8;}

        H1=1;H2=1;H3=0;H4=1;
        if(L1==0){while(L1==0); printf("9\n");return 9;}
        if(L2==0){while(L2==0); printf("10\n");return 10;}
        if(L3==0){while(L3==0); printf("11\n");return 11;}
        if(L4==0){while(L4==0); printf("12\n");return 12;}

        H1=1;H2=1;H3=1;H4=0;
        if(L1==0){while(L1==0);printf("13\n");return 13;}
        if(L2==0){while(L2==0); printf("14\n");return 14;}
        if(L3==0){while(L3==0); printf("15\n");return 15;}
        if(L4==0){while(L4==0); printf("16\n");return 16;}
    }
    return 0;
}