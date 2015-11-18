/*
 * lib_external_interrupt_m16.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited：	2015/09/23 
 *  Author: Narcissus
 */ 


#ifndef LIB_EXTERNAL_INTERRUPT_M16_H_
#define LIB_EXTERNAL_INTERRUPT_M16_H_
//*********************INT启动流程
//******一，先初始化相应中断口和sei();来打开全局中断
//******二，然后在主程序中加入ISR(INT0_vect)来写中断程序
//*******************************************************************
//******注意：应在库前引用delay的库，如果是按键，确认下按键的初始化有无冲突
//*******************************************************************

#define INT0_FOOT 2//**********PD2为INTO接口
#define INT1_FOOT 3//**********PD3为INT1接口



//**********************M16 INT2----PB2  INT1---PD3 INT0----PD2*****************//

//******************初始化*****************

//**********************************外部中断0

void EXTERNAL_INTERRUPT0_INIT_M16()
{
	DDRD &= ~(1 << INT0_FOOT);//*************INT0位设为向内
	
	PORTD |= (1 << INT0_FOOT);//*************INT0位值设为高
	
	MCUCR |= (1<<ISC01);//外部中断0下降沿产生中断 
	
	GICR |= (1<<INT0);//开外部中断0
	
	//sei();//************开全局中断 最好在主程序自己写 这样比较合理 写在主程序的最后
	
	
}
//开外部中断0
void EXTERNAL_INTERRUPT0_OPEN_M16()
{
	
	GICR |= (1<<INT0);//开外部中断0
	
}
//关外部中断0
void EXTERNAL_INTERRUPT0_CLOSE_M16()
{
	
	GICR &= ~(1<<INT0);//开外部中断0
	
}

//**********************************外部中断1

void EXTERNAL_INTERRUPT1_INIT_M16()
{
	DDRD &= ~(1 << INT1_FOOT);
	
	PORTD |= (1 << INT1_FOOT);
	
	MCUCR |= (1<<ISC11);//外部中断1下降沿产生中断 
	
	GICR |= (1<<INT1);//开外部中断1
	
	
}
//**********************************外部中断2
void EXTERNAL_INTERRUPT2_INIT_M16()
{
	DDRB &= ~(1<<2);
	PORTB |= (1<<2);
	MCUCSR &= ~(1<<ISC2);//外部中断2 下降沿产生中断
	GICR |= (1<<INT2);//开外部中断2
	
	
}


#endif /* LIB_EXTERNAL_INTERRUPT_M16_H_ */