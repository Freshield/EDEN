/*
 * lib_ds1302.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_DS1302_H_
#define LIB_DS1302_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char

#define uint unsigned int



//****************************************************
//******************����˿�
//****************************************************

#define DS1302_IO 1//**********оƬ��6��

#define DS1302_SCLK 2//********оƬ��7��

#define DS1302_RST 0//*********оƬ��5��

#define DS1302_PORT PORTA

#define DS1302_DDR DDRA

#define DS1302_PIN PINA


//****************************************************
//******************�������ݷ���
//****************************************************


#define DS1302_IO_DDR_RD() DS1302_DDR &= ~(1 << DS1302_IO)

#define DS1302_IO_DDR_WR() DS1302_DDR |= 1 << DS1302_IO



//****************************************************
//******************�������Ų���
//****************************************************


#define DS1302_WR_IO_0() DS1302_PORT &= ~(1 << DS1302_IO)

#define DS1302_WR_IO_1() DS1302_PORT |= 1 << DS1302_IO

#define DS1302_RD_IO() (DS1302_PIN & (1 << DS1302_IO))

#define DS1302_WR_SCLK_1() DS1302_PORT |= 1 << DS1302_SCLK

#define DS1302_WR_SCLK_0() DS1302_PORT &= ~(1 << DS1302_SCLK)

#define DS1302_WR_RST_1() DS1302_PORT |= 1 << DS1302_RST

#define DS1302_WR_RST_0() DS1302_PORT &= ~(1 << DS1302_RST)



//****************************************************
//******************��������
//****************************************************

char *WEEK[] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
	
uchar DATETIME[7];//*************��7���ֽ� 0�롢1�֡�2ʱ��3�ա�4�¡�5�ܡ�6��

char DS1302_BUFFER_DATE[17],DS1302_BUFFER_TIME[17];

//****************************************************
//******************д��1�ֽ�
//****************************************************

void DS1302_WRITE_BYTE(uchar DATA)
{
	uchar TIME;
	
	DS1302_IO_DDR_WR();
	
	for(TIME = 0x01;TIME != 0x00;TIME <<= 1)
	{
		
		if ((DATA & TIME) != 0)  //******������д��
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
//******************��ȡ1�ֽ�
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
		
		if (DS1302_RD_IO() != 0)//******�½��ض�ȡ
		{
			DATA |= 1 << TIME;
		} 
		else
		{
			DATA &= ~(1 << TIME);
		}
		
	}
	
	return (DATA / 16 * 10 + DATA % 16);//********BCDת����10����
	
}

//****************************************************
//******************д��ָ����ַ����
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
//******************��ȡָ����ַ����
//****************************************************

uchar DS1302_READ_DATA(uchar ADDR)
{
	uchar DATA;
	
	DS1302_WR_RST_1();//*****RST����
	
	delay_reduce(2);
	
	DS1302_WRITE_BYTE(ADDR);//*****д���ַ
	
	DATA = DS1302_GET_BYTE();//****��ȡ����
	
	delay_reduce(2);
	
	DS1302_WR_RST_0();//*****RST����
	
	delay_reduce(2);
	
	return DATA;
	
	
}

//****************************************************
//******************ת��DS1302��ʽ
//****************************************************
void DS1302_BUFFER_1602_TRANSIT()
{
	
	sprintf(DS1302_BUFFER_TIME,"TIME:%2d:%2d:%2d    ",DATETIME[2],DATETIME[1],DATETIME[0]);
	
	sprintf(DS1302_BUFFER_DATE,"DATE:%02d-%02d-%02d%3s",DATETIME[6],DATETIME[4],DATETIME[3],WEEK[DATETIME[5]-1]);
}

//****************************************************
//******************��ȡ��ǰ����ʱ��
//****************************************************

void DS1302_GET_TIME()
{
	
	uchar TIME = 0X00;
	
	uchar ADDR = 0X81;//******���뿪ʼ����
	
	for(TIME = 0;TIME < 7;TIME ++)//*************��7���ֽ� 0�롢1�֡�2ʱ��3�ա�4�¡�5�ܡ�6��
	{
		DATETIME[TIME] = DS1302_READ_DATA(ADDR);
		
		ADDR += 2;//*********��ַ����Ϊ0x81,0x83,0x85...
		
		delay_reduce(2);
		
	}
	
	//DS1302_BUFFER_TRANSIT();
	
}

//****************************************************
//******************��ʼ��DS1302
//****************************************************

void DS1302_INIT(uchar year,uchar month,uchar day,uchar hour,uchar minute,uchar second)//****��ʽ��BCD�� ����14�� д0x14
{
	//************��������׼��
	
	unsigned char t1=0,t2=1;
	unsigned char week=5;                //��ʼ��2000-01-01������
	int y=2000;                                  //������(2000��ʼ)
	
	//*********************
	
	DS1302_WRITE_ADDR_DATA(0x8e,0x00);//******д�����Ĵ���
	
	DS1302_WRITE_ADDR_DATA(0x8c,year);
	
	DS1302_WRITE_ADDR_DATA(0x88,month);
	
	DS1302_WRITE_ADDR_DATA(0x86,day);
	
	DS1302_WRITE_ADDR_DATA(0x84,hour);//*****24Сʱ��ʾ
	
	DS1302_WRITE_ADDR_DATA(0x82,minute);
	
	DS1302_WRITE_ADDR_DATA(0x80,second);
	
	
	//**************�������ڳ��� �����year��ֵ ���Է������
	
	while(t1<year)
	{
		if(((y%4==0)&&(y%100!=0))||(y%400==0))week=week+2;   //�ж��Ƿ�������,����2����29�� ��ʽ:366%7=2
		else week++;
		week=week%7;
		t1++;
		y++;
	}
	while(t2<month)
	{                                           //������(1�¿�ʼ)
		switch(t2){
			case 1:case 3:case 5:case 7:case 8:case 10: case 12:week=week+3;break;  //��������31%7=3
			case 2:if(((y%4==0)&&(y%100!=0))||(y%400==0)) week++;break;             //��������,����2����29��  29%7=1
			case 4:case 6:case 9:case 11: week=week+2;break;                        //С������30%7=2
		}
		week=week%7;
		t2++;
	}
	week=week+day;                              //������(��1�տ�ʼ)
	week=week%7;
	if(week==0) week=7;
	
	
	DS1302_WRITE_ADDR_DATA(0x8a,week);
	
	
	//********************
	
	DS1302_WRITE_ADDR_DATA(0x8e,0x80);//******д�����Ĵ���
	
} 


//****************************************************
//******************��ʼ��DS1302�˿�
//****************************************************
void DS1302_DDR_PORT_INIT()
{
	DS1302_DDR |= (1 << DS1302_IO)|(1 << DS1302_SCLK)|(1 << DS1302_RST);
	
	DS1302_PORT |= (1 << DS1302_IO)|(1 << DS1302_SCLK)|(1 << DS1302_RST);
	
}








#endif /*LIB_DS1302_H_ */