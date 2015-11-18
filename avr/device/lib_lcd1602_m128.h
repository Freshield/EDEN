/*
 * lib_lcd1602_m128.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited��	2015/10/06
 *  Author: Narcissus
 */ 


#ifndef LIB_LCD1602_M128_H_
#define LIB_LCD1602_M128_H_


//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif


#define uchar unsigned char
#define uint unsigned int

//*************************M128��ʼ������
#define LCD_CON_PORT PORTE
#define LCD_CON_DDR DDRE
#define LCD_DAT_PORT PORTC
#define LCD_DAT_DDR DDRC
#define LCD_DAT_PIN PINC
#define RS 0
#define RW 1
#define E 2



//************************���ƶ˿���λ ����
#define RS_1() LCD_CON_PORT |= (1<<RS)//**********���ݼĴ���ѡ��
#define RS_0() LCD_CON_PORT &= ~(1<<RS)//*********ָ��Ĵ���ѡ��
#define RW_1() LCD_CON_PORT |= (1<<RW)//**********������
#define RW_0() LCD_CON_PORT &= ~(1<<RW)//*********д����
#define E_1() LCD_CON_PORT |= (1<<E)
#define E_0() LCD_CON_PORT &= ~(1<<E)//***********Һ��ģ��ʹ��

//****************************æ�ȴ�
void LCD_BUSY_WAIT()
{
	RS_0();RW_1();
	LCD_DAT_DDR=0X00;
	E_1();delay_reduce(10);
	while(LCD_DAT_PIN & 0x80);
	E_0();
	LCD_DAT_DDR=0xff;
	
	
}
//**************************LCD дָ��
void WRITE_LCD_COMMAND(uchar cmd)
{
	LCD_BUSY_WAIT();
	RS_0();RW_0();
	LCD_DAT_PORT = cmd;
	E_1();E_0();
	
}
//**************************LCD д��ʾλ��
void LCD_POS(uchar pos)
{
	WRITE_LCD_COMMAND(pos|0x80);
	
	
}
//************************LCD д����
void WRITE_LCD_DATA(uchar dat)
{
	LCD_BUSY_WAIT();
	RS_1();RW_0();
	LCD_DAT_PORT = dat;
	E_1();E_0();
	
	
	
}
//*********************LCD ��ʼ��
void LCD_init()
{
	
	LCD_DAT_DDR = 0XFF;
	LCD_CON_DDR |= (1<<RS)|(1<<RW)|(1<<E);
	WRITE_LCD_COMMAND(0x01);delay_reduce(15);//**********����
	WRITE_LCD_COMMAND(0x06);delay_reduce(15);//**********��ʾģʽ ����ƶ�
	WRITE_LCD_COMMAND(0x0c);delay_reduce(15);//**********��ʾ����
	//WRITE_LCD_COMMAND(0x1c);delay_reduce(15);//**********�ƶ���ʾ������
	WRITE_LCD_COMMAND(0x38);delay_reduce(15);//**********��ʾ 2����ʾ 5*7
	
	
}
//********************LCD ��ʾ����
void LCD_SHOW_STRING(uchar x,uchar y,char *str) 
{
	uchar count=0;
	if(y==0)WRITE_LCD_COMMAND(0x80|x);else
	if(y==1)WRITE_LCD_COMMAND(0xc0|x);
	
	for(count=0;count<16 && str[count]!='\0';count++)
	WRITE_LCD_DATA(str[count]);
	
	
}


//*******************LCD �����ʾ

void LCD_SAMPLE_SHOW_STRING(uchar x,uchar y,char *str)
{
	WRITE_LCD_COMMAND(0x07);
	uchar count=0;
	if(y==0)WRITE_LCD_COMMAND(0x80|x);else
	if(y==1)WRITE_LCD_COMMAND(0xc0|x);
	
	for(count=0;str[count]!='\0';count++)
	{
		WRITE_LCD_DATA(str[count]);
		
		delay_second(15);
	
	}		
	
	
}

//**************LCD ѭ����ʾ
void LCD_FLOW_SHOW_STRING(uchar x,uchar y,char *str)
{
	LCD_SAMPLE_SHOW_STRING(x,y,str);
	
	for (;x < 15;x ++)
	{
		LCD_SHOW_STRING(x,y,str);
		delay_second(30);
		WRITE_LCD_COMMAND(0x01);
	}
	
	
}
#endif /* LIB_LCD1602_M128_H_ */