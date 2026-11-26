#include "stm32f10x.h"
#include "system.h"
#include "systick.h"
#include "key.h"
#include "usart1.h"
#include "stdio.h"
#include "adc_temp.h"
#include "lcd.h"
#include "image.h"
#include "jkey.h"
#include "motor.h"
#include "24cxx.h"
#include "led.h"
#include "servoMotor.h"
#include "exti.h"
#include "music.h"
#include "beep.h"

#if 0//蜂鸣器测试
int main(void)
{
	systick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	usart1_init(115200);
	key_init();
	printf("hello world6\n");
	beep_init();
	while(1){
		u8 key = key_scan(1);
		if(key!=0){
			switch(key){
				case 1:
					beep_on();
					break;
				case 2:
					beep_off();
					break;
				default:
					break;
			}
		}
	}
}
#endif



#if 0//lcd测试+直流电机测试
int main(void)
{
	systick_init();
	key_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	usart1_init(115200);
	printf("hello world1\n");
	
	lcd_init();				//LCD初始化，内部会先清屏为白色
	motor_init();
	DRV8833_Enable();
	lcd_show_line(RED);		//在y=10处画一条红线
	lcd_show_picture(gImage_ima);	//显示图片
	jkey_init();
	while(1){
		u8 key = jkey_scan();
		if(key!=0){
			switch(key){
				case 1:
					M1_Forward();//前向
					break;
				case 2:
					M1_Backward();//后向
					break;
				case 3:
					M1_Brake();//刹车
					break;
				case 4:
					M1_Coast();//自由滑行
					break;
				default:
					break;
			}
		}
	}	
}
#endif

#if 0//adc测试
int main(void)
{
	systick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	usart1_init(115200);
	ADC_init();
	printf("hello world2\n");
	while(1){
		u16 adc_value = get_adc_value(ADC_Channel_TempSensor,10);//读取温度传感器值，10次取平均值
		float vsense = (float)adc_value * 3.3f / 4096.0f;//将ADC值转换为电压值
		int t10 = (int)(((1.43f - vsense) / 0.0043f + 25.0f) * 10.0f);//将电压值转换为温度值
		if(t10 < 0){//温度值为负数时，需要取绝对值
			t10 = -t10;//取绝对值
			printf("adc = %d, temp = -%d.%d C\n",adc_value,t10/10,t10%10);//打印温度值，保留2位小数
		}else{//温度值为正数时，直接打印
			printf("adc = %d, temp = %d.%d C\n",adc_value,t10/10,t10%10);//打印温度值，保留2位小数
		}//温度值为正数时，直接打印
		delay_ms(500);//延时500ms，避免打印过快
	}
}
#endif


#if 0//24CXX测试
int main(void)
{
	systick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	usart1_init(115200);
	AT24CXX_Init();//初始化24CXX
	led_init();//初始化LED
	#if 0
		while(AT24CXX_Check());//等待24CXX初始化完成
		printf("hello world3,24CXX初始化完成\n");
		AT24CXX_WriteOneByte(0x00,0x01);//写入地址0x00的数据
		printf("hello world4,24CXX写入完成 0x00->0x01\n");
	#else
		printf("hello world\n");
		u8 data = AT24CXX_ReadOneByte(0x00);//读取地址0x00的数据
		printf("data = %d\n",data);//打印读取的数据
		for(int i=0;i<data;i++){
			LED1=!LED1;//切换LED状态
			delay_ms(500);//延时500ms，避免打印过快
			LED1=!LED1;//切换LED状态
			delay_ms(500);//延时500ms，避免打印过快
		}
		AT24CXX_WriteOneByte(0x00,data+1);//写入地址0x00的数据
		printf("hello world4,24CXX写入完成 0x00->data+1\n",data+1);
	#endif
	while(1){}
}
#endif

#if 0//servoMotor测试
void ServoAngleCallback(u16 len, u16 *buf) {
    u8 angle = 0;
    u8 i;

    // 将接收到的字符转换为角度值
    // 假设发送格式为纯数字，如 "90\r\n"
    for(i = 0; i < len; i++) {
        if(buf[i] >= '0' && buf[i] <= '9') {
            angle = angle * 10 + (buf[i] - '0');
        }
    }

    // 限制角度范围 0-180
    if(angle > 180) angle = 180;

    // 控制舵机转动到指定角度
    Servo_SetAngle(angle);

    // 可选：通过串口返回确认信息
    printf("Servo angle set to: %d\r\n", angle);

}
int main(void)
{
	systick_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	usart1_init(115200);
	led_init();
	Servo_PWM_Init();//初始化舵机电机
	exti_init();//初始化外部中断（放在外设初始化之后，避免中断提前触发）
	// 注册串口接收回调函数
  	USART1_RegisterRxCallback(ServoAngleCallback);
	printf("hello world5,舵机电机初始化完成\n");
	while(1){

	}
}
#endif


#if 1//音乐播放
int main(void)
{
	systick_init();
	key_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	beep_init();//蜂鸣器初始化
	usart1_init(115200);
	printf("hello world1\n");
	lcd_init();				//LCD初始化，内部会先清屏为白色
	lcd_show_picture(gImage_ima);	//显示图片
	u8 key;
	uint16_t N=258;
	while(1){
		key = key_scan(1);
		if(key == 1)
	    PlayMusic(N,music);

	}	
}


#endif

#if 0
int main(void)
{
	systick_init();
	key_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//2:2位优先级，6位子优先级
	beep_init();//蜂鸣器初始化
	usart1_init(115200);
	printf("hello world1\n");
	lcd_init();				//LCD初始化，内部会先清屏为白色
	lcd_show_picture(gImage_ima);	//显示图片
	u8 key;
	uint16_t N=258;
	while(1){
		key = key_scan(1);
		if(key == 1)
	    PlayMusic(N,music);
		if(key == 3)
	    PlayMusic(20,music2);

	}	
}
#endif