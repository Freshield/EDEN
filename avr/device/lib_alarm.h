/*
 * lib_alarm.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_ALARM_H_
#define LIB_ALARM_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define ALARM_DDR DDRD
#define ALARM_PORT PORTD
#define ALARM_PIN PIND
#define uchar unsigned char 
#define SOUND 7//*********PD7�ӷ�����

#define RE_TURE_SOUND() (ALARM_PORT ^= 0X80);//*****������

void ALARM_INIT()
{
	ALARM_DDR |= (1 << SOUND);
	
	ALARM_PORT &= ~(1 << SOUND);
	
	
}


void ALARM(uchar time)
{
	
	for(uchar i = 0;i < 100;i ++)
	{
		
		RE_TURE_SOUND(); delay_reduce(time);//********time���Ʋ�ͬ��Ƶ��
		
	}
	
	
}


void CLEAR_ALARM()
{
	ALARM_PORT &= ~(1 << SOUND);
}


#endif /*LIB_ALARM_H_ */