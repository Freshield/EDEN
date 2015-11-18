/*
 * lib_lcd1602_m16.h
 *
 * Created: 2013/04/07 11:41:48
 * Edited：	2015/10/06
 *  Author: Narcissus
 */ 


#ifndef LIB_LCD1602_M16_H_
#define LIB_LCD1602_M16_H_


//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif


#define uchar unsigned char
#define uint unsigned int

/*
1602采用标准的16脚接口，其中:

第1脚：VSS为地电源

第2脚：VDD接5V正电源

第3脚：V0为液晶显示器对比度调整端，接正电源时对比度最弱，接地电源时对比度最高，对比度过高时会产生“鬼影”，使用时可以通过一个10K的电位器调整对比度

第4脚：RS为寄存器选择，高电平时选择数据寄存器、低电平时选择指令寄存器。

第5脚：R/W为读写信号线，高电平时进行读操作，低电平时进行写操作。当RS和RW共同为低电平时可以写入指令或者显示地址，
当RS为低电平RW为高电平时可以读忙信号，当RS为高电平RW为低电平时可以写入数据。

第6脚：E端为使能端，当E端由高电平跳变成低电平时，液晶模块执行命令。

第7～14脚：D0～D7为8位双向数据线。

第15脚：背光电源正极

第16脚：背光电源负极
*/

//char line1[] = {0X2E,0X2E,0X2E,0XA7,0XC5,0XC0,0X2E,0X2E,0X2E,0x20,0x20,0x20,0x20,0x20,0x20,0x20};//日语 我喜欢你
//char line2[] = {0XBD,0X2E,0X2E,0X2E,0XB7,0X2E,0X2E,0X2E,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20};//

//*************************M16初始化定义
//*******************控制端口！！！3位
#define LCD_CON_PORT PORTA
#define LCD_CON_DDR DDRA
#define RS 0
#define RW 1
#define E 2
//*******************数据端口！！！8位
#define LCD_DAT_PORT PORTB
#define LCD_DAT_DDR DDRB
#define LCD_DAT_PIN PINB




//************************控制端口置位 清零
#define RS_1() LCD_CON_PORT |= (1<<RS)//**********置一 数据寄存器选择    
#define RS_0() LCD_CON_PORT &= ~(1<<RS)//*********清零 指令寄存器选择
#define RW_1() LCD_CON_PORT |= (1<<RW)//**********置一 读操作
#define RW_0() LCD_CON_PORT &= ~(1<<RW)//*********清零 写操作
#define E_1() LCD_CON_PORT |= (1<<E)
#define E_0() LCD_CON_PORT &= ~(1<<E)//***********E口由高变低时候 液晶模块使能

//****************************忙等待
void LCD_BUSY_WAIT()
{
	RS_0();RW_1();
	LCD_DAT_DDR=0X00;
	E_1();delay_reduce(10);
	while(LCD_DAT_PIN & 0x80);//***********如果最高位BF为零则不忙
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
	WRITE_LCD_COMMAND(0x0c);delay_reduce(15);//**********显示开关 无光标 不闪烁
	//WRITE_LCD_COMMAND(0x1c);delay_reduce(15);//**********移动显示的文字
	WRITE_LCD_COMMAND(0x38);delay_reduce(15);//**********显示 2行显示 5*7
	
	
}
//***************清屏程序
void LCD_CLEAR()
{
	WRITE_LCD_COMMAND(0x01);delay_reduce(5);
	
}


//********************LCD string显示程序
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
#endif /* LIB_LCD1602_M16_H_ */