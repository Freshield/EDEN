/*
 * lib_rgbled.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_RGBLED_H_
#define LIB_RGBLED_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_PWM_H_
# error "not define LIB_PWM_H_ ; LIB_PWM_H_ can not work"
#endif


//********************RGB LED��ʼ��*************************************//
#define RGB_DDR DDRA
#define RGB_PORT PORTA
#define RGB_PIN PINA
#define red_port PA0
#define green_port PA1
#define blue_port PA2
uchar red_value;
uchar green_value;
uchar blue_value;
//*********************��ɫ��λ******************************//
void red_set_bit()
{
	RGB_PORT|=(1<<red_port);
}

//*********************��ɫ��λ******************************//
void green_set_bit()
{
	RGB_PORT|=(1<<green_port);
}

//*********************��ɫ��λ******************************//
void blue_set_bit()
{
	RGB_PORT|=(1<<blue_port);
}

//********************��ɫ����*****************************//
void red_clr_bit()
{
	RGB_PORT&=~(1<<red_port);
}
//********************��ɫ����*****************************//
void green_clr_bit()
{
	RGB_PORT&=~(1<<green_port);
}
//********************��ɫ����*****************************//
void blue_clr_bit()
{
	RGB_PORT&=~(1<<blue_port);
}
//*******************PWM����ʽRGB ��ʾ��ʼ��**********************************//
void RGB_SHOW_init()
{
	RGB_DDR=0xff;RGB_PORT=0xff;//�˿ڳ�ʼ��
	
	ICR1=256;
	OCR1A=1;
}
//********************PWM����ʽRGB�ж��õƱ���ֵ���ʱ�����********************************//
void RGB_SHOW_interrupt_set()
{
	if (OCR1A<255)
	{
		OCR1A++;
	}
	else
	{
		OCR1A=1;
	}
	if (red_value>OCR1A)
	{
		red_clr_bit();
	}
	else
	{
		red_set_bit();
	}
	if (green_value>OCR1A)
	{
		green_clr_bit();
	}
	else
	{
		green_set_bit();
	}
	if (blue_value>OCR1A)
	{
		blue_clr_bit();
	}
	else
	{
		blue_set_bit();
	}
}
//**************************PWM����ʽRGB�ж��õ�Ϩ��******************//
void RGB_SHOW_interrupt_clr()
{
	
		red_set_bit();
	
		green_set_bit();
	
		blue_set_bit();
	
}
#endif /* LIB_RGBLED_H_ */