/*
 * lib_delay.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited：	2015/09/23 
 *  Author: Narcissus
 */ 

//***头文件
#ifndef LIB_DELAY_H_
#define LIB_DELAY_H_

#define uchar unsigned char

void delay_reduce(long int delay)
{
	/* 
    for(;delay > 1;delay--)
	{
		asm volatile ("nop");
	}
	*/
	while (delay)
	{
		delay--;
		asm volatile ("nop");
	}
}

void delay_second(int i) 
{
	
	int j;
	for(;i!=0;i--)
	{
		for(j=65535;j!=0;j--);
		{
			asm volatile ("nop");
		}

	}
	
}

#endif /* LIB_DELAY_H_ */