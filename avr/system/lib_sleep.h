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

//******************��ʼ��
void SLEEP_INIT_M16()
{
	
   MCUCR |= (1<<SM1);//*********����ģʽ
   
}

//*******************׼��˯��

void SLEEP_BEGIN_M16()

{
	MCUCR |= (1 << SE);//******׼��˯��
}


//****************���˯��׼��

void SLEEP_CLR_M16()
{
	
	MCUCR &= ~(1 << SE);//*******���˯��
	
};
#endif


#endif /* LIB_SLEEP_H_ */