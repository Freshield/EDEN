/*
 * lib_virtual_rgbled.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_VIRTUAL_RGBLED_H_
#define LIB_VIRTUAL_RGBLED_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif
//********************RGB LED��ʼ��*************************************//
#define RGB_DDR DDRC
#define RGB_PORT PORTC
#define RGB_PIN PINC
#define RGB_CON_DDR DDRD
#define RGB_CON_PORT PORTD
#define RGB_CON_PIN PIND
#define red_port 0
#define green_port 1
#define blue_port 2
#define uchar unsigned char
#define uint unsigned int
uint red_value;
uint green_value;
uint blue_value;
uint red_value0;
uint green_value0;
uint blue_value0;
uint red_value1;
uint green_value1;
uint blue_value1;
uint red_value2;
uint green_value2;
uint blue_value2;
uint red_value3;
uint green_value3;
uint blue_value3;
uint red_value4;
uint green_value4;
uint blue_value4;
uint red_value5;
uint green_value5;
uint blue_value5;
uint red_value6;
uint green_value6;
uint blue_value6;
uint red_value7;
uint green_value7;
uint blue_value7;

uint FZ;//**************************��Ƶ
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

//*********************ledѡ����λ******************************//
void rgbled_clr_bit(uchar led_num)
{
	RGB_CON_PORT|=(1<<led_num);
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

//********************led1ѡ������*****************************//
void rgbled_set_bit(uchar led_num)
{
	RGB_CON_PORT&=~(1<<led_num);
}



//********************************************************************************************************************************//

//********************************************************************************************************************************//
//******************* RGB ��ʾ��ʼ��**********************************//
void RGB_SHOW_init()
{
	RGB_DDR |= (1<<red_port)|(1<<green_port)|(1<<blue_port);
	RGB_PORT |= (1<<red_port)|(1<<green_port)|(1<<blue_port);
	RGB_CON_DDR=0xff;
	RGB_CON_PORT=0xff;//�˿ڳ�ʼ��
	
	FZ=1;
}
//********************************************************************************************************************************//

//********************************************************************************************************************************//




//********************************************************************************************************************************//

//********************************************************************************************************************************//
//**********************PWM����ʽFAST PWM ICR1 RGBLEDģʽ*******************//
uint TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(uchar red_valuer,uchar green_valuer,uchar blue_valuer)
{
	
	
	uint PWM_VIRTUAL_OCR1A=1;
	uint PWM_VIRTUAL_ICR1=255;
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	for(uint PWM_VIRTUAL_COUNT=0x00;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)
	{
		
		if (PWM_VIRTUAL_COUNT<PWM_VIRTUAL_OCR1A)
		{
			if (red_value>PWM_VIRTUAL_OCR1A)
			{
				red_clr_bit();
			}
			else
			{
				red_set_bit();
			}
			if (green_value>PWM_VIRTUAL_OCR1A)
			{
				green_clr_bit();
			}
			else
			{
				green_set_bit();
			}
			if (blue_value>PWM_VIRTUAL_OCR1A)
			{
				blue_clr_bit();
			}
			else
			{
				blue_set_bit();
			}
		}
		else
		{
			red_set_bit();
			green_set_bit();
			blue_set_bit();
		}
		
		if (PWM_VIRTUAL_OCR1A<255)
		{
			PWM_VIRTUAL_OCR1A++;	
		}
	 }  
}

//**********************PWM����ʽFAST PWM ICR1 RGBLED FLOWģʽ*******************//
void TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_FLOW_ICR1()
{
	uchar red_flow_value=255;
	uchar green_flow_value=0;
	uchar blue_flow_value=0;
	uchar flow_time=0;
	uint change_time=3000;
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
    for (flow_time=0;flow_time<255;flow_time++)
    {
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value++;
    }
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		red_flow_value--;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		blue_flow_value++;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value--;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		red_flow_value++;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		blue_flow_value--;
	}
	
}
//*********************PWM����ʽFAST PWM ICR1 RGBLED ָ��Ŀ����ɫ

uint TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_CHANGE_TO(uchar red_aim_value,uchar green_aim_value,uchar blue_aim_value)
{
	   uint change_time=500;
	   uchar change_value;
	   
	   for(change_value=254;change_value>0;change_value--)
	   {
	      TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_ICR1(red_value,green_value,blue_value);
		   if (red_value<red_aim_value)
		   {
			   red_value++;
		   }
		   else if (red_value>red_aim_value)
		   {
			   red_value--;
		   }
		   if (green_value<green_aim_value)
		   {
			   green_value++;
		   }
		   else if (green_value>green_aim_value)
		   {
			   green_value--;
		   }
		   if (blue_value<blue_aim_value)
		   {
			   blue_value++;
		   }
		   else if (blue_value>blue_aim_value)
		   {
			   blue_value--;
		   }
	   delay_reduce(change_time);
	   }	
}
//********************************************************************************************************************************//

//********************PWM����ʽ ���߷��� ledƬѡ�ķ���
//********************�����������߿��� led�������ɶ˿ڿ���
//********************************************************************************************************************************//

uint TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(uchar red_valuer,uchar green_valuer,uchar blue_valuer,uchar led_num)
{
	
	
	uint PWM_VIRTUAL_OCR1A=1;
	uint PWM_VIRTUAL_ICR1=255;
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	
	for(uint PWM_VIRTUAL_COUNT=0;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)
	{
		rgbled_clr_bit(led_num);
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		
			//*****************red bus
		
			red_clr_bit();
			green_set_bit();
			blue_set_bit();
			if (red_value>PWM_VIRTUAL_OCR1A)
			{
				rgbled_set_bit(led_num);
			}
			else
			{
				rgbled_clr_bit(led_num);
			}
			
		
		rgbled_clr_bit(led_num);
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		//*****************green bus
		
			green_clr_bit();
			red_set_bit();
			blue_set_bit();
			if (green_value>PWM_VIRTUAL_OCR1A)
			{
				rgbled_set_bit(led_num);
			}
			else
			{
				rgbled_clr_bit(led_num);
			}
		
		rgbled_clr_bit(led_num);
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		//*****************blue bus
		
			blue_clr_bit();
			green_set_bit();
			red_set_bit();
			if (blue_value>PWM_VIRTUAL_OCR1A)
			{
				rgbled_set_bit(led_num);
			}
			else
			{
				rgbled_clr_bit(led_num);
			}
			
		    PWM_VIRTUAL_OCR1A++;
		
		
		
		}
}
//**********************PWM����ʽ RGBLED FLOWģʽ*******************//
void TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_MODE_FLOW()
{
	uchar red_flow_value=255;
	uchar green_flow_value=0;
	uchar blue_flow_value=0;
	uchar flow_time=0;
	uint change_time=3000;
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
		delay_reduce(change_time);
		green_flow_value++;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
		delay_reduce(change_time);
		red_flow_value--;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
		delay_reduce(change_time);
		blue_flow_value++;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
		delay_reduce(change_time);
		green_flow_value--;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
		delay_reduce(change_time);
		red_flow_value++;
	}
	TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_flow_value,green_flow_value,blue_flow_value,1);
		delay_reduce(change_time);
		blue_flow_value--;
	}
}
	
//*********************PWM����ʽ ���߷�ʽ ָ��Ŀ����ɫ

uint TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_MODE_CHANGE_TO(uchar red_aim_value,uchar green_aim_value,uchar blue_aim_value,uchar led_aim_num)
{
	   uint change_time=500;
	   uchar change_value;
	   
	   for(change_value=255;change_value>0;change_value--)
	   {
	      TIMER1_PWM_ADD_MODE_VIRTUAL_RGBLED_BUS_ICR1(red_value,green_value,blue_value,led_aim_num);
		   if (red_value<red_aim_value)
		   {
			   red_value++;
		   }
		   else if (red_value>red_aim_value)
		   {
			   red_value--;
		   }
		   if (green_value<green_aim_value)
		   {
			   green_value++;
		   }
		   else if (green_value>green_aim_value)
		   {
			   green_value--;
		   }
		   if (blue_value<blue_aim_value)
		   {
			   blue_value++;
		   }
		   else if (blue_value>blue_aim_value)
		   {
			   blue_value--;
		   }
	   delay_reduce(change_time);
	   }	
}

//********************************************************************************************************************************//

//********************************************************************************************************************************//
//**********************PWM����ʽFAST PWM ICR1 RGBLEDģʽ*******************//
uint TIMER1_PWM_COUNT_MODE_VIRTUAL_RGBLED_ICR1(uchar red_valuer,uchar green_valuer,uchar blue_valuer)
//****************����ʽPWM�ĵ��ƾ���������ģ�ⷽ�����ϵķ���ռ�ձ�Ϊ50%��PWM�� ��PWM VIRTUAL TIME������pwm���ĸ��� ���Ժͺ�ɫ��ɫ��ɫ��ֵ���бȽ�
//�����ڳ���ɫ��ɫ��ɫ�Ĳ�ͬ��pwm������ Ȼ�������ͬ����ɫ**********************************PS rgbledΪ����led ����Ҫ���� ����Ҫ����
{
	
	
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	uint PWM_VIRTUAL_OCR1A=127;//***********����ģ���ocr1aΪ127 Ҳ���Ƿ���ռ�ձ�Ϊ50%��PWM��
	uint PWM_VIRTUAL_ICR1=255;//************ģ��ICRģʽ��PWM 255Ϊtop
	uint PWM_VIRTUAL_TIME=0;//**************PWM������
	for(uint PWM_VIRTUAL_COUNT=0x00;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)//***************����ģ������� for���Ϊһ��PWM��
	{
		delay_reduce(FZ/10);//***********�����趨�ķ�Ƶ��ʱ ģ���Ƶ
		if (PWM_VIRTUAL_COUNT=1)//*****************PWM��Ϊ�ߵ�ƽ��
		{
			PWM_VIRTUAL_TIME++;//******************pwm���ļ�����1
			if (red_value>PWM_VIRTUAL_TIME)//************�趨�ĺ�ɫֵ���бȽ� �����ɫ��ֵ���ڵ�ǰpwm�������������ɫ��io����������ɫ
			{
				red_clr_bit();//***********�����ɫλ ��������ɫ�� rgbledΪ����led ����Ҫ���� ����Ҫ����
			}
			else
			{
				red_set_bit();//**********��λ��ɫλ ��Ϩ���ɫ��
			}
			if (green_value>PWM_VIRTUAL_TIME)//*************ͬ��ɫ
			{
				green_clr_bit();
			}
			else
			{
				green_set_bit();
			}
			if (blue_value>PWM_VIRTUAL_TIME)//**************ͬ��ɫ
			{
				blue_clr_bit();
			}
			else
			{
				blue_set_bit();
			}
		}
		if (PWM_VIRTUAL_COUNT=PWM_VIRTUAL_OCR1A)//*************PWM���ĵ͵�ƽ�� �����Եƾ�Ϩ��
		{
			red_set_bit();
			green_set_bit();
			blue_set_bit();
		}
		if (PWM_VIRTUAL_TIME=255)//*************һ����255ɫ ������255��PWM��Ϊһ��ѭ�� ����PWM������
		{
			PWM_VIRTUAL_TIME=0;
		}
		
	}
		
	
}	
//**********************PWM����ʽFAST PWM ICR1 RGBLEDģʽ test*******************//
uint TIMER1_PWM_COUNT_MODE_VIRTUAL_RGBLED1_ICR1(uchar red_valuer,uchar green_valuer,uchar blue_valuer)
{
	
	
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	uint PWM_VIRTUAL_OCR1A=127;
	uint PWM_VIRTUAL_ICR1=255;
	uint PWM_VIRTUAL_TIME=1;
	for(uint PWM_VIRTUAL_COUNT=0;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)
	{
		delay_reduce(FZ/10);
		if (PWM_VIRTUAL_COUNT=255)
		{
			
			if (red_value>PWM_VIRTUAL_TIME)
			{
				red_clr_bit();
			}
			else
			{
				red_set_bit();
			}
			if (green_value>PWM_VIRTUAL_TIME)
			{
				green_clr_bit();
			}
			else
			{
				green_set_bit();
			}
			if (blue_value>PWM_VIRTUAL_TIME)
			{
				blue_clr_bit();
			}
			else
			{
				blue_set_bit();
			}
		}
		if (PWM_VIRTUAL_COUNT=PWM_VIRTUAL_OCR1A)
		{
			PWM_VIRTUAL_TIME++;
			red_set_bit();
			green_set_bit();
			blue_set_bit();
		
		if (PWM_VIRTUAL_TIME=255)
		{
			PWM_VIRTUAL_TIME=0;
		}
		}		
	}
	
	
}
//**********************PWM����ʽFAST PWM ICR1 RGBLED FLOWģʽ*******************//
void TIMER1_PWM_COUNT_MODE_VIRTUAL_RGBLED_FLOW_ICR1()
{
	uint red_flow_value=255;
	uint green_flow_value=0;
	uint blue_flow_value=0;
	
	uint change_time=5000;
	for (uint flow_time=0;flow_time<254;flow_time++)
	{
		TIMER1_PWM_COUNT_MODE_VIRTUAL_RGBLED1_ICR1(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value++;
	}
}


//********************************************************************************************************************************//

//********************************************************************************************************************************//




//********************************************************************************************************************************//

//********************************************************************************************************************************//
//*******************��򵥵Ŀ���PWM����
uint SIMPLE_RGBLED_SHOW(uchar red_valuer,uchar green_valuer,uchar blue_valuer)
{
	
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	for(uint SIMPLE_TIME=0;SIMPLE_TIME<255;SIMPLE_TIME++)
	{
		delay_reduce(FZ/10);
		
			if (red_value>SIMPLE_TIME)
			{
				red_clr_bit();
			}
			else
			{
				red_set_bit();
			}
			if (green_value>SIMPLE_TIME)
			{
				green_clr_bit();
			}
			else
			{
				green_set_bit();
			}
			if (blue_value>SIMPLE_TIME)
			{
				blue_clr_bit();
			}
			else
			{
				blue_set_bit();
			}
		
	}
	
	
}
//**********************SIMPLE RGBLED FLOWģʽ*******************//
void SIMPLE_RGBLED_FLOW()
{
	uchar red_flow_value=254;
	uchar green_flow_value=1;
	uchar blue_flow_value=1;
	uchar flow_time=0;
	uint change_time=3000;
	SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value++;
	}
	SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		red_flow_value--;
	}
	SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		blue_flow_value++;
	}
	SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value--;
	}
	SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		red_flow_value++;
	}
	SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		blue_flow_value--;
	}
}

//*********************SIMPLE FAST PWM��ָ��Ŀ����ɫ

uint SIMPLE_RGBLED_CHANGE_TO(uchar red_aim_value,uchar green_aim_value,uchar blue_aim_value)
{
	   uint change_time=500;
	   uchar change_value;
	   
	   for(change_value=254;change_value>0;change_value--)
	   {
	      SIMPLE_RGBLED_SHOW(red_value,green_value,blue_value);
		   if (red_value<red_aim_value)
		   {
			   red_value++;
		   }
		   else if (red_value>red_aim_value)
		   {
			   red_value--;
		   }
		   if (green_value<green_aim_value)
		   {
			   green_value++;
		   }
		   else if (green_value>green_aim_value)
		   {
			   green_value--;
		   }
		   if (blue_value<blue_aim_value)
		   {
			   blue_value++;
		   }
		   else if (blue_value>blue_aim_value)
		   {
			   blue_value--;
		   }
	   delay_reduce(change_time);
	   }	
}
//********************************************************************************************************************************//

//********************SIMPLE ���߷��� ledƬѡ�ķ���
//********************�����������߿��� led�������ɶ˿ڿ���
//********************************************************************************************************************************//

//*******************SIMPLE ����
uint SIMPLE_RGBLED_BUS_MODE_SHOW(uchar red_valuer,uchar green_valuer,uchar blue_valuer,uchar led_num)
{
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	
	for(uint SIMPLE_TIME=0;SIMPLE_TIME<(256*3);SIMPLE_TIME++)
	{
		delay_reduce(FZ);
		//*****************red bus
		if (SIMPLE_TIME<256)
		{
			red_clr_bit();
			green_set_bit();
			blue_set_bit();
			if (red_value>SIMPLE_TIME)
			{
				rgbled_set_bit(led_num);
			}
			else
			{
				rgbled_clr_bit(led_num);
			}
		}
		//*****************green bus
		else if ((SIMPLE_TIME<(256*2))&&(SIMPLE_TIME>=255))
		{
			green_clr_bit();
			red_set_bit();
			blue_set_bit();
			if ((green_value+255)>SIMPLE_TIME)
			{
				rgbled_set_bit(led_num);
			}
			else
			{
				rgbled_clr_bit(led_num);
			}
		}
		//*****************blue bus
		else if ((SIMPLE_TIME<(256*3))&&(SIMPLE_TIME>=((256*2)-1)))
		{
			blue_clr_bit();
			green_set_bit();
			red_set_bit();
			if ((blue_value+(256*2)-1)>SIMPLE_TIME)
			{
				rgbled_set_bit(led_num);
			}
			else
			{
				rgbled_clr_bit(led_num);
			}
		}
		
	}
}
//**********************SIMPLE���� RGBLED FLOWģʽ*******************//
void SIMPLE_RGBLED_BUS_MODE_FLOW()
{
	uchar red_flow_value=254;
	uchar green_flow_value=1;
	uchar blue_flow_value=1;
	uchar flow_time=0;
	uint change_time=3000;
	SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
		delay_reduce(change_time);
		green_flow_value++;
	}
	SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
		delay_reduce(change_time);
		red_flow_value--;
	}
	SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
		delay_reduce(change_time);
		blue_flow_value++;
	}
	SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
		delay_reduce(change_time);
		green_flow_value--;
	}
	SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
		delay_reduce(change_time);
		red_flow_value++;
	}
	SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<253;flow_time++)
	{
		
		SIMPLE_RGBLED_BUS_MODE_SHOW(red_flow_value,green_flow_value,blue_flow_value,0);
		delay_reduce(change_time);
		blue_flow_value--;
	}
}
	
//*********************SIMPLE ���߷�ʽ ָ��Ŀ����ɫ

uint SIMPLE_RGBLED_BUS_MODE_CHANGE_TO(uchar red_aim_value,uchar green_aim_value,uchar blue_aim_value,uchar led_aim_num)
{
	   uint change_time=500;
	   uchar change_value;
	   
	   for(change_value=255;change_value>0;change_value--)
	   {
	      SIMPLE_RGBLED_BUS_MODE_SHOW(red_value,green_value,blue_value,led_aim_num);
		   if (red_value<red_aim_value)
		   {
			   red_value++;
		   }
		   else if (red_value>red_aim_value)
		   {
			   red_value--;
		   }
		   if (green_value<green_aim_value)
		   {
			   green_value++;
		   }
		   else if (green_value>green_aim_value)
		   {
			   green_value--;
		   }
		   if (blue_value<blue_aim_value)
		   {
			   blue_value++;
		   }
		   else if (blue_value>blue_aim_value)
		   {
			   blue_value--;
		   }
	   delay_reduce(change_time);
	   }	
}

//********************************************************************************************************************************//
		
#endif /* LIB_VIRTUAL_RGBLED_H_ */