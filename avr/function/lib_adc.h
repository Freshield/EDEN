/*
 * lib_adc.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_ADC_H_
#define LIB_ADC_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char
#define uint unsigned int

//******************M16的adc程序********************//

//***********************ADC的获取*****************//

int M16_ADC_CATCH(char num)
{
	int result;
	
	int back;
	
	char hun,ten,one;
	
	//************IO口激活
	
	DDRA &= ~(1 << 0);//*******设为输入
	
	//***********设定转换
	
	ADMUX = num;
	
	delay_reduce(2000);
	
	result = (int)((ADC * 500.0)/ 1023.0);//******把参考电压进行转换 这里为5v
	
	//hun = result / 100;
	
	//ten = result / 10 % 10;
	
	//one = result % 10;
	
	//back = ((hun * 100.0)+(ten * 10.0)+ one);
	
	return(result);
	
	
	
	
}

//***********************ADC的初始化*****************//

void M16_ADC_INIT()
{
	//********ADC参考电压选择
	
	ADMUX |= (1 << REFS0);//*******选择AVCC为参考电压
	
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2);//**********开了中断 16分频 
	
	delay_reduce(100);//*****等系统稳定
	
}


#endif /*LIB_ADC_H_ */