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
 *����ʱ Ӧ������ʱ����
 */
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//*****************************************************
//************************�˲���δ�������������˼����ж�ȥ������

/*
 *������������
 *һ���ȳ�ʼ����Ӧ�жϿں�sei();����ȫ���ж�
 *����Ȼ�����������м���ISR(INT0_vect)��д�жϳ���
 *ע�⣺Ӧ�ڿ�ǰ����delay�Ŀ⣬����ǰ�����ȷ���°����ĳ�ʼ�����޳�ͻ
 */


/*
 *��ʼ�� ����
 */
#define uchar unsigned char
#define uint unsigned int
#define KEY_DDR DDRB
#define KEY_PORT PORTB
#define KEY_PIN PINB

/*
 *ָ�������б�
 */

#define KEY_AIM() ((KEY_PIN & 0X80) == 0X00)//***�˴�ΪPB7

/*
 *ʹ������ if(KEY_AIM()) COUNT = 0;�˴�Ϊ��������
 *while(! KEY_AIM());
 *while(KEY_AIM());
 *delay(5000);
 *while(KEY_AIM());
 */

uchar MOVE_LED_DIRECTION = 0;
uchar RECENT_KEY = 0X00;

void KEYBOARD_INIT_M16();//***��ʼ��
uchar KEY_DOWN();//***�ж����ް�������
uchar keyscan();//***������
void MOVE_LED();//***���̿���LED��λ
int KEY_INT_M16();//***�����ж�ȥ��


//--------------------------------------IMPLEMENTATION------------------------//

/*
 *��ʼ��
 */

void KEYBOARD_INIT_M16()
{
	KEY_DDR = 0X00;
	
	KEY_PORT = 0Xff;
}

/*
 *�ж����ް�������
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
 *������
 */

uchar keyscan()
{
	KEY_DDR = 0x00;
	
	KEY_PORT = 0xFF;
	
	uchar keyvalue = 16;
	
	uchar zavr = KEY_PIN;
	
	if (zavr != 0x00)
	 {
		//****************ȥ�� 
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
 *���̿���LED��λ
 *A��ΪLED�� B��Ϊ
 */

void MOVE_LED()
{
	DDRA = 0XFF;
	
	if ((KEY_PIN & 0X01) == 0X00) MOVE_LED_DIRECTION = (MOVE_LED_DIRECTION - 1) & 0X07;//*****Ϊѭ���ƶ�
	
	else if((KEY_PIN & 0X02) == 0X00) MOVE_LED_DIRECTION = (MOVE_LED_DIRECTION + 1) & 0X07;//******ѭ���ƶ�
	
	PORTA = (1 << MOVE_LED_DIRECTION);//***********������ MOVE_LED_DIRECTION λ�ĵ�
	
	
	
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
 *�����ж�ȥ��������ɹ��򷵻�0
 *INT0************ע����̰�����Ҫ���������赽�ߵ�ƽ
 *��������
 *һ���ȳ�ʼ���жϲ���
 *�����˲���Ϊ����ISR(INT0_vect)���жϳ���
 *��Ҫ������
 *EXTERNAL_INTERRUPT0_INIT_M16();��ʼ��
 */

int KEY_INT_M16()//***ȥ������ ����ɹ��򷵻�0
{
	delay_reduce(30000);//***ȥ��
	
	uchar get = PIND;//***ȡ�õ�ǰ��ֵ
	
	get = get & 0x04;//***INT0�ļ�λ
	
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
 *�򵥵ĵȰ���̧��
 *������ ������ѭ��
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