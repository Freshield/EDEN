/*
 * lib_virtual_pwm.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_VIRTUAL_PWM_H_
#define LIB_VIRTUAL_PWM_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif


//******************M16的pwm程序********************//

//***********************TIMER1的pwm*****************//
//定义输出口 M16的TIMER1的输出口为OC1A（PD5）和OC1B(PD4)//
#define PWM_VIRTUAL_PORT PORTD
#define PWM_VIRTUAL_DDR DDRD
#define PWM_VIRTUAL_PIN PIND
#define PWM_VIRTUAL_OUTA PD5
#define PWM_VIRTUAL_OUTB PD4
#define uchar unsigned char
#define uint unsigned int
#define F_CPU 7372800UL//7.3728晶振

//**********************FAST PWM ICR1模式*******************//
uint TIMER1_VIRTUAL_FASTPWMA_ICR1(uint compare_time,uint top_time,uint FZ)
{
	//端口初始化
	PWM_VIRTUAL_DDR|=(1<<PWM_VIRTUAL_OUTA);  PWM_VIRTUAL_PORT=0x00;
	
	uint PWM_VIRTUAL_OCR1A=F_CPU/FZ*compare_time;
	uint PWM_VIRTUAL_ICR1=F_CPU/FZ*top_time;
	
	for (uint PWM_VIRTUAL_COUNT=0x00;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)
	{
		delay_reduce(FZ/10);
		if (PWM_VIRTUAL_COUNT<PWM_VIRTUAL_OCR1A)
		{
			PWM_VIRTUAL_PORT|=(1<<PWM_VIRTUAL_OUTA);
		}
		else
		{
			PWM_VIRTUAL_PORT&=~(1<<PWM_VIRTUAL_OUTA);
		}
		
	}
}


#endif /* LIB_VIRTUAL_PWM_H_ */