/*
 * lib_nixie.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_NIXIE_H_
#define LIB_NIXIE_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif
//*********************����A��Ϊ�����
#define NIXIE_PORT PORTA
#define NIXIE_DDR DDRA
#define NIXIE_PIN PINA

//*********************����B��Ϊ�����
#define NIXIE_CON_PORT PORTB
#define NIXIE_CON_DDR DDRB
#define NIXIE_CON_PIN PINB

#define uchar unsigned char
//*********************����ܳ�ʼ��
void NIXIE_INIT()
{
	NIXIE_DDR = 0xff;
	
	NIXIE_PORT = 0x00;
	
}

//********************��ʾ����� ���������ʾ��Ӧ������ ��ʱû�м���Ӣ�� 16Ϊ��ֵ
//*************************Ҫ��DP��17

void NIXIE_SHOW(uchar count)
{
uchar nixie[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,
0x3f | 0x80,0x06 | 0x80,0x5b | 0x80,0x4f | 0x80,0x66 | 0x80,0x6d | 0x80,0x7d | 0x80,0x07 | 0x80,0x7f | 0x80,
0x6f | 0x80,0x77 | 0x80,0x7c | 0x80,0x39 | 0x80,0x5e | 0x80,0x79 | 0x80,0x71 | 0x80 };
	
NIXIE_PORT=nixie[count];

}



//*******************ѭ����ʾ0��9 ��ʱû���ϸ����
void NIXIE_FLOW()
{
       for(uchar count=0;count<=15;count++)
	   {
		  
		    
		NIXIE_SHOW(count);
		
		delay_second(7);
		   
	   }		   
    }
	//*********************�����4λ��ʼ��
void NIXIE_4BIT_INIT()
{
	NIXIE_DDR = 0xff;
	
	NIXIE_PORT = 0x00;
	
	//***********׼������
	NIXIE_DDR = 0XFF;
	
	NIXIE_CON_DDR |= (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3);
}
//********************************��λ����
	
void NIXIE_4BIT_0_SHOW(uchar T)
{
	
	
	//******************��3λ
	
	NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	�����λ 
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XF7;//*********��3λ
	
	//NIXIE_CON_PORT = ~(1 << 3);
	
	NIXIE_SHOW(T);
	
	delay_reduce(100);
	
}	
	
//********************************��λ����
	
void NIXIE_4BIT_1_SHOW(uchar T)
{
	
	
	//******************��2λ
	
	NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	�����λ 
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XFB;//*********��2λ
	
	//NIXIE_CON_PORT = ~(1 << 2);
	
	NIXIE_SHOW(T);
	
	
	delay_reduce(100);
	
	
}	

//********************************��λ����
	
void NIXIE_4BIT_2_SHOW(uchar T)
{
	
	
	//******************��1λ
	
	 NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	�����λ
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XFD;//*********��1λ
	
	//NIXIE_CON_PORT = ~(1 << 1);
	
	NIXIE_SHOW(T);

    
    delay_reduce(100);
    

}	

//********************************��λ����
	
void NIXIE_4BIT_3_SHOW(uchar T)
{
	
	
	//******************��0λ
	
	NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	�����λ 
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XFE;//*********��0λ
	
	//NIXIE_CON_PORT = ~(1 << 0);
	
	NIXIE_SHOW(T);
	
	
	delay_reduce(100);
	
	
}	

void NIXIE_4BIT_SHOW(uchar D ,uchar C ,uchar B ,uchar A)
{
	NIXIE_4BIT_0_SHOW(A);
	
	NIXIE_4BIT_1_SHOW(B);
	
	NIXIE_4BIT_2_SHOW(C);
	
	NIXIE_4BIT_3_SHOW(D);
	
	
}
//********************��λ�������ʾ
//******************�øı����һ����ʾ��˳����ƽ������
void NIXIE_4BIT_SHOW_L1(uchar D ,uchar C ,uchar B ,uchar A)
{
	NIXIE_4BIT_0_SHOW(A);
	
	NIXIE_4BIT_1_SHOW(B);
	
	NIXIE_4BIT_2_SHOW(C);
	
	NIXIE_4BIT_3_SHOW(D);
	
	
}

void NIXIE_4BIT_SHOW_L2(uchar D ,uchar C ,uchar B ,uchar A)
{
	NIXIE_4BIT_0_SHOW(A);
	
	NIXIE_4BIT_1_SHOW(B);
	
	NIXIE_4BIT_3_SHOW(D);
	
	NIXIE_4BIT_2_SHOW(C);
	
	
}

void NIXIE_4BIT_SHOW_L3(uchar D ,uchar C ,uchar B ,uchar A)
{
	NIXIE_4BIT_0_SHOW(A);
	
	NIXIE_4BIT_2_SHOW(C);
	
	NIXIE_4BIT_3_SHOW(D);
	
	NIXIE_4BIT_1_SHOW(B);
	
	
}

void NIXIE_4BIT_SHOW_L4(uchar D ,uchar C ,uchar B ,uchar A)
{
	
	NIXIE_4BIT_1_SHOW(B);
	
	NIXIE_4BIT_2_SHOW(C);
	
	NIXIE_4BIT_3_SHOW(D);
	
	NIXIE_4BIT_0_SHOW(A);
	
}
#endif /* LIB_NIXIE_H_ */