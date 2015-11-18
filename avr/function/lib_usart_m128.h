/*
 * lib_usart_m128.h
 *
 * Created: 2015/10/05
 * Edited：	2015/10/05
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
	UCSR1A = (0<<U2X1)|(0<<MPCM1);//关闭倍速模式和多处理器通信模式
	UCSR1B = (1<<TXEN1)|(1<<RXEN1)|(1<<RXCIE1);//开启rx和tx
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);//8位显示
	//UBRR1H默认值
	UBRR1L = 0x07;//波特率57600,7.3728m
	//UBRR1L = 0x0b;//波特率38400,7.3728m
}

//参数:无符号字符变量
void usart_1_send_char(unsigned char data)
{
	/* 等待发送缓冲器为空 */
	while ( !( UCSR1A & (1<<UDRE1)) )
	;
	/* 将数据放入缓冲器，发送数据*/
	UDR1 = data;
}

unsigned char usart_1_recv_char()
{
	/* 等待接收数据*/
	while ( !(UCSR1A & (1<<RXC1)) )
	;
	/* 从缓冲器中获取并返回数据*/
	return UDR1;
}

//参数:字符串首地址,字符串长度(使用sizeof计算),光标归位标志位,换行标志位
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
		usart_1_send_char('\r');//光标归位
	}
	
	if (n == 0)
	{
		asm volatile ("nop");
	}
	else
	{
		usart_1_send_char('\n');//换行
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