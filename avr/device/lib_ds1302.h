/*
 * lib_ds1302.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_DS1302_H_
#define LIB_DS1302_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char

#define uint unsigned int



//****************************************************
//******************定义端口
//****************************************************

#define DS1302_IO 1//**********芯片的6口

#define DS1302_SCLK 2//********芯片的7口

#define DS1302_RST 0//*********芯片的5口

#define DS1302_PORT PORTA

#define DS1302_DDR DDRA

#define DS1302_PIN PINA


//****************************************************
//******************定义数据方向
//****************************************************


#define DS1302_IO_DDR_RD() DS1302_DDR &= ~(1 << DS1302_IO)

#define DS1302_IO_DDR_WR() DS1302_DDR |= 1 << DS1302_IO



//****************************************************
//******************定义引脚操作
//****************************************************


#define DS1302_WR_IO_0() DS1302_PORT &= ~(1 << DS1302_IO)

#define DS1302_WR_IO_1() DS1302_PORT |= 1 << DS1302_IO

#define DS1302_RD_IO() (DS1302_PIN & (1 << DS1302_IO))

#define DS1302_WR_SCLK_1() DS1302_PORT |= 1 << DS1302_SCLK

#define DS1302_WR_SCLK_0() DS1302_PORT &= ~(1 << DS1302_SCLK)

#define DS1302_WR_RST_1() DS1302_PORT |= 1 << DS1302_RST

#define DS1302_WR_RST_0() DS1302_PORT &= ~(1 << DS1302_RST)



//****************************************************
//******************定义日期
//****************************************************

char *WEEK[] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
	
uchar DATETIME[7];//*************共7个字节 0秒、1分、2时、3日、4月、5周、6年

char DS1302_BUFFER_DATE[17],DS1302_BUFFER_TIME[17];

//****************************************************
//******************写入1字节
//****************************************************

void DS1302_WRITE_BYTE(uchar DATA)
{
	uchar TIME;
	
	DS1302_IO_DDR_WR();
	
	for(TIME = 0x01;TIME != 0x00;TIME <<= 1)
	{
		
		if ((DATA & TIME) != 0)  //******上升沿写入
		{
			DS1302_WR_IO_1();
		}
		else
		{
			DS1302_WR_IO_0();
		}
		
		delay_reduce(2);
		
		DS1302_WR_SCLK_0();
		
		delay_reduce(2);
		
		DS1302_WR_SCLK_1();
		
		delay_reduce(2);
		
	}
	
	
}

//****************************************************
//******************读取1字节
//****************************************************

uchar DS1302_GET_BYTE()
{
	uchar TIME,DATA = 0X00;
	
	DS1302_IO_DDR_RD();
	
	for(TIME = 0;TIME < 8;TIME ++)
	{
		
		delay_reduce(2);
		
		DS1302_WR_SCLK_1();
		
		delay_reduce(2);
		
		DS1302_WR_SCLK_0();
		
		delay_reduce(2);
		
		if (DS1302_RD_IO() != 0)//******下降沿读取
		{
			DATA |= 1 << TIME;
		} 
		else
		{
			DATA &= ~(1 << TIME);
		}
		
	}
	
	return (DATA / 16 * 10 + DATA % 16);//********BCD转换成10进制
	
}

//****************************************************
//******************写入指定地址数据
//****************************************************
void DS1302_WRITE_ADDR_DATA(uchar ADDR,uchar DATA)
{
	DS1302_WR_RST_0();
	
	delay_reduce(2);
	
	DS1302_WR_SCLK_0();
	
	delay_reduce(2);
	
	DS1302_WR_RST_1();
	
	DS1302_WRITE_BYTE(ADDR);
	
	DS1302_WRITE_BYTE(DATA);
	
	DS1302_WR_SCLK_1();
	
	delay_reduce(2);
	
	DS1302_WR_RST_0();
	
	
}

//****************************************************
//******************读取指定地址数据
//****************************************************

uchar DS1302_READ_DATA(uchar ADDR)
{
	uchar DATA;
	
	DS1302_WR_RST_1();//*****RST拉高
	
	delay_reduce(2);
	
	DS1302_WRITE_BYTE(ADDR);//*****写入地址
	
	DATA = DS1302_GET_BYTE();//****读取数据
	
	delay_reduce(2);
	
	DS1302_WR_RST_0();//*****RST拉低
	
	delay_reduce(2);
	
	return DATA;
	
	
}

//****************************************************
//******************转换DS1302格式
//****************************************************
void DS1302_BUFFER_1602_TRANSIT()
{
	
	sprintf(DS1302_BUFFER_TIME,"TIME:%2d:%2d:%2d    ",DATETIME[2],DATETIME[1],DATETIME[0]);
	
	sprintf(DS1302_BUFFER_DATE,"DATE:%02d-%02d-%02d%3s",DATETIME[6],DATETIME[4],DATETIME[3],WEEK[DATETIME[5]-1]);
}

//****************************************************
//******************读取当前日期时间
//****************************************************

void DS1302_GET_TIME()
{
	
	uchar TIME = 0X00;
	
	uchar ADDR = 0X81;//******从秒开始读起
	
	for(TIME = 0;TIME < 7;TIME ++)//*************共7个字节 0秒、1分、2时、3日、4月、5周、6年
	{
		DATETIME[TIME] = DS1302_READ_DATA(ADDR);
		
		ADDR += 2;//*********地址依次为0x81,0x83,0x85...
		
		delay_reduce(2);
		
	}
	
	//DS1302_BUFFER_TRANSIT();
	
}

//****************************************************
//******************初始化DS1302
//****************************************************

void DS1302_INIT(uchar year,uchar month,uchar day,uchar hour,uchar minute,uchar second)//****格式用BCD码 比如14年 写0x14
{
	//************计算星期准备
	
	unsigned char t1=0,t2=1;
	unsigned char week=5;                //初始化2000-01-01星期六
	int y=2000;                                  //处理年(2000开始)
	
	//*********************
	
	DS1302_WRITE_ADDR_DATA(0x8e,0x00);//******写保护寄存器
	
	DS1302_WRITE_ADDR_DATA(0x8c,year);
	
	DS1302_WRITE_ADDR_DATA(0x88,month);
	
	DS1302_WRITE_ADDR_DATA(0x86,day);
	
	DS1302_WRITE_ADDR_DATA(0x84,hour);//*****24小时显示
	
	DS1302_WRITE_ADDR_DATA(0x82,minute);
	
	DS1302_WRITE_ADDR_DATA(0x80,second);
	
	
	//**************计算星期程序 会更改year等值 所以放在最后
	
	while(t1<year)
	{
		if(((y%4==0)&&(y%100!=0))||(y%400==0))week=week+2;   //判断是否是闰年,闰年2月是29天 公式:366%7=2
		else week++;
		week=week%7;
		t1++;
		y++;
	}
	while(t2<month)
	{                                           //处理月(1月开始)
		switch(t2){
			case 1:case 3:case 5:case 7:case 8:case 10: case 12:week=week+3;break;  //大月天数31%7=3
			case 2:if(((y%4==0)&&(y%100!=0))||(y%400==0)) week++;break;             //闰月天数,闰年2月是29天  29%7=1
			case 4:case 6:case 9:case 11: week=week+2;break;                        //小月天数30%7=2
		}
		week=week%7;
		t2++;
	}
	week=week+day;                              //处理日(从1日开始)
	week=week%7;
	if(week==0) week=7;
	
	
	DS1302_WRITE_ADDR_DATA(0x8a,week);
	
	
	//********************
	
	DS1302_WRITE_ADDR_DATA(0x8e,0x80);//******写保护寄存器
	
} 


//****************************************************
//******************初始化DS1302端口
//****************************************************
void DS1302_DDR_PORT_INIT()
{
	DS1302_DDR |= (1 << DS1302_IO)|(1 << DS1302_SCLK)|(1 << DS1302_RST);
	
	DS1302_PORT |= (1 << DS1302_IO)|(1 << DS1302_SCLK)|(1 << DS1302_RST);
	
}








#endif /*LIB_DS1302_H_ */