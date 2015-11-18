/*
 * lib_lcd1602_m128.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited：	2015/10/06
 *  Author: Narcissus
 */ 


#ifndef LIB_LCD1602_M128_H_
#define LIB_LCD1602_M128_H_


//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif


#define uchar unsigned char
#define uint unsigned int

//*************************M128初始化定义
#define LCD_CON_PORT PORTE
#define LCD_CON_DDR DDRE
#define LCD_DAT_PORT PORTC
#define LCD_DAT_DDR DDRC
#define LCD_DAT_PIN PINC
#define RS 0
#define RW 1
#define E 2



//************************控制端口置位 清零
#define RS_1() LCD_CON_PORT |= (1<<RS)//**********数据寄存器选择
#define RS_0() LCD_CON_PORT &= ~(1<<RS)//*********指令寄存器选择
#define RW_1() LCD_CON_PORT |= (1<<RW)//**********读操作
#define RW_0() LCD_CON_PORT &= ~(1<<RW)//*********写操作
#define E_1() LCD_CON_PORT |= (1<<E)
#define E_0() LCD_CON_PORT &= ~(1<<E)//***********液晶模块使能

//****************************忙等待
void LCD_BUSY_WAIT()
{
	RS_0();RW_1();
	LCD_DAT_DDR=0X00;
	E_1();delay_reduce(10);
	while(LCD_DAT_PIN & 0x80);
	E_0();
	LCD_DAT_DDR=0xff;
	
	
}
//**************************LCD 写指令
void WRITE_LCD_COMMAND(uchar cmd)
{
	LCD_BUSY_WAIT();
	RS_0();RW_0();
	LCD_DAT_PORT = cmd;
	E_1();E_0();
	
}
//**************************LCD 写显示位置
void LCD_POS(uchar pos)
{
	WRITE_LCD_COMMAND(pos|0x80);
	
	
}
//************************LCD 写数据
void WRITE_LCD_DATA(uchar dat)
{
	LCD_BUSY_WAIT();
	RS_1();RW_0();
	LCD_DAT_PORT = dat;
	E_1();E_0();
	
	
	
}
//*********************LCD 初始化
void LCD_init()
{
	
	LCD_DAT_DDR = 0XFF;
	LCD_CON_DDR |= (1<<RS)|(1<<RW)|(1<<E);
	WRITE_LCD_COMMAND(0x01);delay_reduce(15);//**********清屏
	WRITE_LCD_COMMAND(0x06);delay_reduce(15);//**********显示模式 光标移动
	WRITE_LCD_COMMAND(0x0c);delay_reduce(15);//**********显示开关
	//WRITE_LCD_COMMAND(0x1c);delay_reduce(15);//**********移动显示的文字
	WRITE_LCD_COMMAND(0x38);delay_reduce(15);//**********显示 2行显示 5*7
	
	
}
//********************LCD 显示程序
void LCD_SHOW_STRING(uchar x,uchar y,char *str) 
{
	uchar count=0;
	if(y==0)WRITE_LCD_COMMAND(0x80|x);else
	if(y==1)WRITE_LCD_COMMAND(0xc0|x);
	
	for(count=0;count<16 && str[count]!='\0';count++)
	WRITE_LCD_DATA(str[count]);
	
	
}


//*******************LCD 逐个显示

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

//**************LCD 循环显示
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