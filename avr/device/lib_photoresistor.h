/*
 * lib_photoresistor.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_PHOTORESISTOR_H_
#define LIB_PHOTORESISTOR_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char

#define uint unsigned int

#define PHOTORESISTOR_LIGHT 1

#define PHOTORESISTOR_DARK 0



uchar VALUE[10],RESULT,LIGHT,DARK;


//****************************************************
//******************越亮电压越低
//****************************************************


//****************************************************
//******************定义端口
//****************************************************

#define PHOTORESISTOR_IO 0

#define PHOTORESISTOR_PORT PORTB

#define PHOTORESISTOR_DDR DDRB

#define PHOTORESISTOR_PIN PINB

//****************************************************
//******************初始化
//****************************************************

void PHOTORESISTOR_INIT()
{
	PHOTORESISTOR_DDR &= ~(1 << PHOTORESISTOR_IO);
	
	PHOTORESISTOR_PORT &= ~(1 << PHOTORESISTOR_IO);
	
	
}


//****************************************************
//******************判别现在是亮还是暗 因为亮时候很容易跳 所以用数组只要有亮的就亮
//****************************************************
uchar PHOTORESISTOR_VALUE()
{
	uchar PHOTORESISTOR_NOW;
	
	for (uchar i = 0;i < 10;i ++)
	{
		VALUE[i] = PHOTORESISTOR_PIN;
		
		delay_reduce(5);
	}
	for(uchar i = 0;i < 10;i ++)
	{
		if ((VALUE[i] &  (1 << PHOTORESISTOR_IO))  == 0x00)
		{
			PHOTORESISTOR_NOW = PHOTORESISTOR_LIGHT;
			
			break;
		}
		if ((VALUE[i] | 0X00) == (1 << PHOTORESISTOR_IO))
		{
			PHOTORESISTOR_NOW = PHOTORESISTOR_DARK;
		}
		
	}
	
	
	return PHOTORESISTOR_NOW;
}


























































#endif /*LIB_PHOTORESISTOR_H_ */