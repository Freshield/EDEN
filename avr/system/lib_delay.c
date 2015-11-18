/*
 * lib_delay.c
 *
 * Created: 2015/10/14 11:41:48
 * Edited£º	2015/10/14
 *  Author: Narcissus
 */ 
 #include "asf.h" 
 #include "lib_delay.h"

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