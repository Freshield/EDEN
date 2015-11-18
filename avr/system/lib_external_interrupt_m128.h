/*
 * lib_external_interrupt_m128.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited��	2015/09/23 
 *  Author: Narcissus
 */ 
 
 
//***********************************************************************
//**********************��ͷ�ļ�������
//**********************��Ҫ����
//***********************************************************************

#ifndef LIB_EXTERNAL_INTERRUPT_M128_H_
#define LIB_EXTERNAL_INTERRUPT_M128_H_

#define INT0_FOOT 0//**********
#define INT1_FOOT 1//**********


//**********************M128 INT3----PD3   INT2----PD2  INT1---PD1 INT0----PD0  
//*****************INT7----PE7   INT6----PE6  INT5---PE5 INT4----PE4

//******************��ʼ��
void EXTERNAL_INTERRUPT0_INIT_M128()
{
	
	EICRA=(1<<ISC01);//�ⲿ�ж�0�½��ز����ж� 
	EIMSK=(1<<INT0);//���ⲿ�ж�0
	
	
}

#endif

#endif /* LIB_EXTERNAL_INTERRUPT_M128_H_ */