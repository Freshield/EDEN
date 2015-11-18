/*
 * lib_photoresistor.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_PHOTORESISTOR_H_
#define LIB_PHOTORESISTOR_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char

#define uint unsigned int

#define PHOTORESISTOR_LIGHT 1

#define PHOTORESISTOR_DARK 0



uchar VALUE[10],RESULT,LIGHT,DARK;


//****************************************************
//******************Խ����ѹԽ��
//****************************************************


//****************************************************
//******************����˿�
//****************************************************

#define PHOTORESISTOR_IO 0

#define PHOTORESISTOR_PORT PORTB

#define PHOTORESISTOR_DDR DDRB

#define PHOTORESISTOR_PIN PINB

//****************************************************
//******************��ʼ��
//****************************************************

void PHOTORESISTOR_INIT()
{
	PHOTORESISTOR_DDR &= ~(1 << PHOTORESISTOR_IO);
	
	PHOTORESISTOR_PORT &= ~(1 << PHOTORESISTOR_IO);
	
	
}


//****************************************************
//******************�б������������ǰ� ��Ϊ��ʱ��������� ����������ֻҪ�����ľ���
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