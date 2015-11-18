/*
 * lib_led.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited��	2015/09/23 
 *  Author: Narcissus
 */ 


#ifndef LIB_LED_H_
#define LIB_LED_H_
//*********************LED��������
//******һ���ȳ�ʼ�������
//******����Ȼ������Ӧ�ĳ��򼴿�
//*******************************************************************
//******ע�⣺Ӧ�ڿ�ǰ����delay�Ŀ�
//*******************************************************************



//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//*********************����A��Ϊ�����
#define LED_PORT PORTA
#define LED_DDR DDRA
#define LED_PIN PINA
#define uchar unsigned char

uchar LED_LEFT_NUM = 0X01;


//************��ʼ��
void LED_INIT()
{
	
	LED_PORT = 0X00;
	
	LED_DDR = 0XFF;
	
	
}




//********ָ��λȡ��
void LED_TWINK(uchar num)
{
	LED_PORT ^= 1 << num;//********ָ��λȡ��
}


//****************ָ��λ��˸
void LED_BLINK(uchar num,uchar time)
{
	LED_DDR |= 1 << num;//******ָ��λΪ���
	
	LED_PORT |= 1 << num;//********ָ��λΪ����
	
	delay_second(time);
	
	LED_PORT &= ~(1 << num);//*******ָ��λΪ��
	
	delay_second(time);
	
	
}


/*********************��ˮ��*********************/

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

//*************ѭ������
//*************��ʼ��ʱҪ����LED_PORT = 0X01;
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



//******************���鶨����ˮ��

const uchar LED_ARRAY[] = 
{
	0XFF,0X00,0XFF,0X00,0X01,0X02,0X04,0X08,0X10,0X20,0X40,0X80,0XFF,0X00,0XFF,0X00,
	
	0XFF,0X00,0XFF,0X00,0X80,0X40,0X20,0X10,0X08,0X04,0X02,0X01,0XFF,0X00,0XFF,0X00
	
	
	
	
};

#endif /* LIB_DELAY_H_ */