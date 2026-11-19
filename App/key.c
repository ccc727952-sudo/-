#include "key.h"





void key_init(){

    //1.时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //2.初始化GPIO
    GPIO_InitTypeDef initDef;
    initDef.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
    initDef.GPIO_Pin=KEY1_PIN|KEY2_PIN|KEY3_PIN|KEY4_PIN;
    initDef.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(KEY_GPIO_PORT,&initDef);

}


u8 key_scan(u8 mode){

   //版本一
   /*
   if (KEY1==0)//按键按下
   {
        delay_ms(10);//消抖
        if (KEY1==0) return 1;      
   }
   if (KEY2==0)//按键按下
   {
        delay_ms(10);//消抖
        if (KEY2==0) return 2;      
   }
   if (KEY3==0)//按键按下
   {
        delay_ms(10);//消抖
        if (KEY3==0) return 3;      
   }
   if (KEY4==0)//按键按下
   {
        delay_ms(10);//消抖
        if (KEY4==0) return 4;      
   }
   */
    //版本二:缩减了篇幅 从按下到松开会检测多次
    /*
    if(KEY1==0||KEY2==0||KEY3==0||KEY4==0){
        delay_ms(10);
        if (KEY1==0) return 1;    
        if (KEY2==0) return 2;  
        if (KEY3==0) return 3; 
        if (KEY4==0) return 4;
    }
    */
    //版本三:从按下到松开只是检测一次
    /*
    static u8 flag=1;

    if(flag  && (KEY1==0||KEY2==0||KEY3==0||KEY4==0)){
        delay_ms(10);
        flag=0;
        if (KEY1==0) return 1;    
        if (KEY2==0) return 2;  
        if (KEY3==0) return 3; 
        if (KEY4==0) return 4;
    }else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1){
        flag=1;
    }
    */
    //版本四:从按下到松开 检测一次还是多次选择权交给用户
    static u8 flag=1;
    if(mode) flag = 1;
    if(flag  && (KEY1==0||KEY2==0||KEY3==0||KEY4==0)){
        delay_ms(10);
        flag=0;
        if (KEY1==0) return 1;    
        if (KEY2==0) return 2;  
        if (KEY3==0) return 3; 
        if (KEY4==0) return 4;
    }else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1){
        flag=1;
    }

   return 0;
}