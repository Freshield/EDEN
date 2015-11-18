/*
 * lib_led.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited：	2015/09/23 
 *  Author: Narcissus
 */ 


#ifndef LIB_LED_H_
#define LIB_LED_H_
//*********************LED启动流程
//******一，先初始化输出口
//******二，然后找相应的程序即可
//*******************************************************************
//******注意：应在库前引用delay的库
//*******************************************************************



//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//*********************定义A口为输出口
#define LED_PORT PORTA
#define LED_DDR DDRA
#define LED_PIN PINA
#define uchar unsigned char

uchar LED_LEFT_NUM = 0X01;


//************初始化
void LED_INIT()
{
	
	LED_PORT = 0X00;
	
	LED_DDR = 0XFF;
	
	
}




//********指定位取反
void LED_TWINK(uchar num)
{
	LED_PORT ^= 1 << num;//********指定位取反
}


//****************指定位闪烁
void LED_BLINK(uchar num,uchar time)
{
	LED_DDR |= 1 << num;//******指定位为输出
	
	LED_PORT |= 1 << num;//********指定位为点亮
	
	delay_second(time);
	
	LED_PORT &= ~(1 << num);//*******指定位为灭
	
	delay_second(time);
	
	
}


/*********************流水灯*********************/

void LED_FLOW()
{
	LED_DDR = 0XFF;
	LED_PORT = 0x01;
	for(uchar K = 0;K < 8;K ++)
	{
		delay_second(5);
		
		LED_PORT = LED_PORT <<1;
		
		
		 
	}
	LED_PORT = 0x01;
}

//*************循环左移
//*************初始化时要加入LED_PORT = 0X01;
void LED_LEFT_CIRCLE()
{
	
	delay_second(4);
	
	if (LED_PORT & 0X80)
	{
		LED_PORT = 0X01;
	}
	
	else
	
	
	
	LED_PORT <<= 1;
	
	
}



//******************数组定义流水灯

const uchar LED_ARRAY[] = 
{
	0XFF,0X00,0XFF,0X00,0X01,0X02,0X04,0X08,0X10,0X20,0X40,0X80,0XFF,0X00,0XFF,0X00,
	
	0XFF,0X00,0XFF,0X00,0X80,0X40,0X20,0X10,0X08,0X04,0X02,0X01,0XFF,0X00,0XFF,0X00
	
	
	
	
};

#endif /* LIB_DELAY_H_ */