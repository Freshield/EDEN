/*
 * lib_keyboard.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

//-----------------------------HEADER-------------------------------//

#ifndef LIB_KEYBOARD_H_
#define LIB_KEYBOARD_H_
/*
 *有延时 应包含延时程序
 */
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//*****************************************************
//************************此部分未订正，仅订正了键盘中断去抖部分

/*
 *键盘启动流程
 *一，先初始化相应中断口和sei();来打开全局中断
 *二，然后在主程序中加入ISR(INT0_vect)来写中断程序
 *注意：应在库前引用delay的库，如果是按键，确认下按键的初始化有无冲突
 */


/*
 *初始化 共阴
 */
#define uchar unsigned char
#define uint unsigned int
#define KEY_DDR DDRB
#define KEY_PORT PORTB
#define KEY_PIN PINB

/*
 *指定按键判别
 */

#define KEY_AIM() ((KEY_PIN & 0X80) == 0X00)//***此处为PB7

/*
 *使用例子 if(KEY_AIM()) COUNT = 0;此处为清零作用
 *while(! KEY_AIM());
 *while(KEY_AIM());
 *delay(5000);
 *while(KEY_AIM());
 */

uchar MOVE_LED_DIRECTION = 0;
uchar RECENT_KEY = 0X00;

void KEYBOARD_INIT_M16();//***初始化
uchar KEY_DOWN();//***判断有无按键按下
uchar keyscan();//***读键盘
void MOVE_LED();//***键盘控制LED移位
int KEY_INT_M16();//***键盘中断去抖


//--------------------------------------IMPLEMENTATION------------------------//

/*
 *初始化
 */

void KEYBOARD_INIT_M16()
{
	KEY_DDR = 0X00;
	
	KEY_PORT = 0Xff;
}

/*
 *判断有无按键按下
 */

uchar KEY_DOWN()
{
	
	
	
	delay_reduce(100);
	uchar i;
	if(KEY_PIN != 0xff)
	{
		i=1;
	}
	else 
	{
		i=0;
	}
	return i;

}

/*
 *读键盘
 */

uchar keyscan()
{
	KEY_DDR = 0x00;
	
	KEY_PORT = 0xFF;
	
	uchar keyvalue = 16;
	
	uchar zavr = KEY_PIN;
	
	if (zavr != 0x00)
	 {
		//****************去抖 
	delay_reduce(30);
	
	if (zavr == zavr)
	{
		switch(zavr)
		{
		
		case 0xfe:keyvalue = 1;
		break;
		
		case 0xfd:keyvalue = 2;
		break;
		
		case 0xfb:keyvalue = 3;
		break;
		
		case 0xf7:keyvalue = 4;
		break;
		
		case 0xef:keyvalue = 5;
		break;
		
		case 0xdf:keyvalue = 6;
		break;
		
		case 0xbf:keyvalue = 7;
		break;
		
		case 0x7f:keyvalue = 8;
		break;
		
		default : keyvalue = 16;
		}	
			
	}
	else keyvalue = 16;
	}	
	else keyvalue = 16;
	
	return(keyvalue);
	
	
}

/*
 *键盘控制LED移位
 *A口为LED口 B口为
 */

void MOVE_LED()
{
	DDRA = 0XFF;
	
	if ((KEY_PIN & 0X01) == 0X00) MOVE_LED_DIRECTION = (MOVE_LED_DIRECTION - 1) & 0X07;//*****为循环移动
	
	else if((KEY_PIN & 0X02) == 0X00) MOVE_LED_DIRECTION = (MOVE_LED_DIRECTION + 1) & 0X07;//******循环移动
	
	PORTA = (1 << MOVE_LED_DIRECTION);//***********点亮第 MOVE_LED_DIRECTION 位的灯
	
	
	
}

void KEYBOARD_MOVE_LED()
{
	if (KEY_PIN != RECENT_KEY)
	{
		RECENT_KEY = KEY_PIN;
		
		MOVE_LED();
		
		delay_reduce(20);
		
		
	}
	
	
	
}


/*
 *键盘中断去抖，如果成功则返回0
 *INT0************注意键盘按键需要接上来电阻到高电平
 *启动流程
 *一，先初始化中断部分
 *二，此部分为加入ISR(INT0_vect)的中断程序
 *主要别忘了
 *EXTERNAL_INTERRUPT0_INIT_M16();初始化
 */

int KEY_INT_M16()//***去抖程序 如果成功则返回0
{
	delay_reduce(30000);//***去抖
	
	uchar get = PIND;//***取得当前的值
	
	get = get & 0x04;//***INT0的键位
	
	if (get == 0)
	{
		return 0;
	}
	
	else
	{
		return 1;
	}
	

}

//--------------------------------------PROBLEMS-----------------------------//

/*
 *P1
 *简单的等按键抬起
 *有问题 可能死循环
 */

/*
uchar KEY_ACCURATE()
{
	while(! KEY_AIM());
	
	delay_reduce(500);
	
	while(! KEY_AIM());
	
	while(KEY_AIM());
	
	delay_reduce(500);
	
	while(KEY_AIM());
}
*/



#endif /*LIB_KEYBOARD_H_ */