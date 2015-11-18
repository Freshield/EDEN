/*
 * lib_usart_m128.h
 *
 * Created: 2015/10/05
 * Edited��	2015/10/05
 *  Author: Narcissus
 */ 

#include <stdio.h>


#ifndef LIB_USART_M128_H_
#define LIB_USART_M128_H_


//////////////////////////////////////////////////
// USART 1
//////////////////////////////////////////////////
void usart_1_init(void)
{
	UCSR1A = (0<<U2X1)|(0<<MPCM1);//�رձ���ģʽ�Ͷദ����ͨ��ģʽ
	UCSR1B = (1<<TXEN1)|(1<<RXEN1)|(1<<RXCIE1);//����rx��tx
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);//8λ��ʾ
	//UBRR1HĬ��ֵ
	UBRR1L = 0x07;//������57600,7.3728m
	//UBRR1L = 0x0b;//������38400,7.3728m
}

//����:�޷����ַ�����
void usart_1_send_char(unsigned char data)
{
	/* �ȴ����ͻ�����Ϊ�� */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	/* �����ݷ��뻺��������������*/
	UDR1 = data;
}

unsigned char usart_1_recv_char()
{
	/* �ȴ���������*/
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* �ӻ������л�ȡ����������*/
	return UDR1;
}

//����:�ַ����׵�ַ,�ַ�������(ʹ��sizeof����),����λ��־λ,���б�־λ
void usart_1_send_string_ex(char data_string[],int string_size,int r,int n)
{
	for (int i = 0;i < string_size;i++)
	{
		usart_1_send_char(data_string[i]);
	}
	
	if (r == 0)
	{
		asm volatile ("nop");
	}
	else
	{
		usart_1_send_char('\r');//����λ
	}
	
	if (n == 0)
	{
		asm volatile ("nop");
	}
	else
	{
		usart_1_send_char('\n');//����
	}
}

/*void usart_1_send_string(char data_string[],int string_size)
{
	usart_1_send_string_ex(data_string,string_size,1,1);
}

void usart_1_recv_string_ex(char data_string[],int string_size)
{
	for (int i = 0;i < string_size;i++)
	{
		data_string[i] = usart_1_recv_char();
	}
	
}

void usart_1_recv_string(char data_string[],int string_size)
{
	usart_1_recv_string_ex(data_string,string_size,1,1);
}*/


#endif


#endif /* LIB_USART_M128_H_ */