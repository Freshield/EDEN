/*
 * lib_sleep.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_SLEEP_H_
#define LIB_SLEEP_H_

#define M16

#ifdef M16
//**********************M16 *****************//

//******************初始化
void SLEEP_INIT_M16()
{
	
   MCUCR |= (1<<SM1);//*********掉电模式
   
}

//*******************准备睡眠

void SLEEP_BEGIN_M16()

{
	MCUCR |= (1 << SE);//******准备睡觉
}


//****************清除睡眠准备

void SLEEP_CLR_M16()
{
	
	MCUCR &= ~(1 << SE);//*******清除睡觉
	
};
#endif


#endif /* LIB_SLEEP_H_ */