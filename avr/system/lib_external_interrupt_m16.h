/*
 * lib_external_interrupt_m16.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited��	2015/09/23 
 *  Author: Narcissus
 */ 


#ifndef LIB_EXTERNAL_INTERRUPT_M16_H_
#define LIB_EXTERNAL_INTERRUPT_M16_H_
//*********************INT��������
//******һ���ȳ�ʼ����Ӧ�жϿں�sei();����ȫ���ж�
//******����Ȼ�����������м���ISR(INT0_vect)��д�жϳ���
//*******************************************************************
//******ע�⣺Ӧ�ڿ�ǰ����delay�Ŀ⣬����ǰ�����ȷ���°����ĳ�ʼ�����޳�ͻ
//*******************************************************************

#define INT0_FOOT 2//**********PD2ΪINTO�ӿ�
#define INT1_FOOT 3//**********PD3ΪINT1�ӿ�



//**********************M16 INT2----PB2  INT1---PD3 INT0----PD2*****************//

//******************��ʼ��*****************

//**********************************�ⲿ�ж�0

void EXTERNAL_INTERRUPT0_INIT_M16()
{
	DDRD &= ~(1 << INT0_FOOT);//*************INT0λ��Ϊ����
	
	PORTD |= (1 << INT0_FOOT);//*************INT0λֵ��Ϊ��
	
	MCUCR |= (1<<ISC01);//�ⲿ�ж�0�½��ز����ж� 
	
	GICR |= (1<<INT0);//���ⲿ�ж�0
	
	//sei();//************��ȫ���ж� ������������Լ�д �����ȽϺ��� д������������
	
	
}
//���ⲿ�ж�0
void EXTERNAL_INTERRUPT0_OPEN_M16()
{
	
	GICR |= (1<<INT0);//���ⲿ�ж�0
	
}
//���ⲿ�ж�0
void EXTERNAL_INTERRUPT0_CLOSE_M16()
{
	
	GICR &= ~(1<<INT0);//���ⲿ�ж�0
	
}

//**********************************�ⲿ�ж�1

void EXTERNAL_INTERRUPT1_INIT_M16()
{
	DDRD &= ~(1 << INT1_FOOT);
	
	PORTD |= (1 << INT1_FOOT);
	
	MCUCR |= (1<<ISC11);//�ⲿ�ж�1�½��ز����ж� 
	
	GICR |= (1<<INT1);//���ⲿ�ж�1
	
	
}
//**********************************�ⲿ�ж�2
void EXTERNAL_INTERRUPT2_INIT_M16()
{
	DDRB &= ~(1<<2);
	PORTB |= (1<<2);
	MCUCSR &= ~(1<<ISC2);//�ⲿ�ж�2 �½��ز����ж�
	GICR |= (1<<INT2);//���ⲿ�ж�2
	
	
}


#endif /* LIB_EXTERNAL_INTERRUPT_M16_H_ */