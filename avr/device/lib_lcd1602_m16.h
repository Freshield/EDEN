/*
 * lib_lcd1602_m16.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited��	2015/10/06
 *  Author: Narcissus
 */ 


#ifndef LIB_LCD1602_M16_H_
#define LIB_LCD1602_M16_H_


//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif


#define uchar unsigned char
#define uint unsigned int

/*
1602���ñ�׼��16�Žӿڣ�����:

��1�ţ�VSSΪ�ص�Դ

��2�ţ�VDD��5V����Դ

��3�ţ�V0ΪҺ����ʾ���Աȶȵ����ˣ�������Դʱ�Աȶ��������ӵص�Դʱ�Աȶ���ߣ��Աȶȹ���ʱ���������Ӱ����ʹ��ʱ����ͨ��һ��10K�ĵ�λ�������Աȶ�

��4�ţ�RSΪ�Ĵ���ѡ�񣬸ߵ�ƽʱѡ�����ݼĴ������͵�ƽʱѡ��ָ��Ĵ�����

��5�ţ�R/WΪ��д�ź��ߣ��ߵ�ƽʱ���ж��������͵�ƽʱ����д��������RS��RW��ͬΪ�͵�ƽʱ����д��ָ�������ʾ��ַ��
��RSΪ�͵�ƽRWΪ�ߵ�ƽʱ���Զ�æ�źţ���RSΪ�ߵ�ƽRWΪ�͵�ƽʱ����д�����ݡ�

��6�ţ�E��Ϊʹ�ܶˣ���E���ɸߵ�ƽ����ɵ͵�ƽʱ��Һ��ģ��ִ�����

��7��14�ţ�D0��D7Ϊ8λ˫�������ߡ�

��15�ţ������Դ����

��16�ţ������Դ����
*/

//char line1[] = {0X2E,0X2E,0X2E,0XA7,0XC5,0XC0,0X2E,0X2E,0X2E,0x20,0x20,0x20,0x20,0x20,0x20,0x20};//���� ��ϲ����
//char line2[] = {0XBD,0X2E,0X2E,0X2E,0XB7,0X2E,0X2E,0X2E,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};//

//*************************M16��ʼ������
//*******************���ƶ˿ڣ�����3λ
#define LCD_CON_PORT PORTA
#define LCD_CON_DDR DDRA
#define RS 0
#define RW 1
#define E 2
//*******************���ݶ˿ڣ�����8λ
#define LCD_DAT_PORT PORTB
#define LCD_DAT_DDR DDRB
#define LCD_DAT_PIN PINB




//************************���ƶ˿���λ ����
#define RS_1() LCD_CON_PORT |= (1<<RS)//**********��һ ���ݼĴ���ѡ��    
#define RS_0() LCD_CON_PORT &= ~(1<<RS)//*********���� ָ��Ĵ���ѡ��
#define RW_1() LCD_CON_PORT |= (1<<RW)//**********��һ ������
#define RW_0() LCD_CON_PORT &= ~(1<<RW)//*********���� д����
#define E_1() LCD_CON_PORT |= (1<<E)
#define E_0() LCD_CON_PORT &= ~(1<<E)//***********E���ɸ߱��ʱ�� Һ��ģ��ʹ��

//****************************æ�ȴ�
void LCD_BUSY_WAIT()
{
	RS_0();RW_1();
	LCD_DAT_DDR=0X00;
	E_1();delay_reduce(10);
	while(LCD_DAT_PIN & 0x80);//***********������λBFΪ����æ
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
	WRITE_LCD_COMMAND(0x0c);delay_reduce(15);//**********��ʾ���� �޹�� ����˸
	//WRITE_LCD_COMMAND(0x1c);delay_reduce(15);//**********�ƶ���ʾ������
	WRITE_LCD_COMMAND(0x38);delay_reduce(15);//**********��ʾ 2����ʾ 5*7
	
	
}
//***************��������
void LCD_CLEAR()
{
	WRITE_LCD_COMMAND(0x01);delay_reduce(5);
	
}


//********************LCD string��ʾ����
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
	/*WRITE_LCD_COMMAND(0x07);
	uchar count=0;
	if(y==0)WRITE_LCD_COMMAND(0x80|x);else
	if(y==1)WRITE_LCD_COMMAND(0xc0|x);
	
	for(count=0;count<16 && str[count]!='\0';count++)
	{
		WRITE_LCD_DATA(str[count]);
		
		delay_second(15);
	
	}		*/
	uchar count=0;
	if(y==0)WRITE_LCD_COMMAND(0x80|x);else
	if(y==1)WRITE_LCD_COMMAND(0xc0|x);
	
	for(count=0;count<16 && str[count]!='\0';count++)
	{WRITE_LCD_DATA(str[count]);
		
		delay_second(3);}
	
	
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
#endif /* LIB_LCD1602_M16_H_ */