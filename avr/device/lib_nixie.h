/*
 * lib_nixie.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_NIXIE_H_
#define LIB_NIXIE_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif
//*********************定义A口为输出口
#define NIXIE_PORT PORTA
#define NIXIE_DDR DDRA
#define NIXIE_PIN PINA

//*********************定义B口为输出口
#define NIXIE_CON_PORT PORTB
#define NIXIE_CON_DDR DDRB
#define NIXIE_CON_PIN PINB

#define uchar unsigned char
//*********************数码管初始化
void NIXIE_INIT()
{
	NIXIE_DDR = 0xff;
	
	NIXIE_PORT = 0x00;
	
}

//********************显示数码管 输入序号显示相应的数字 暂时没有加入英文 16为错值
//*************************要带DP加17

void NIXIE_SHOW(uchar count)
{
uchar nixie[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,
0x3f | 0x80,0x06 | 0x80,0x5b | 0x80,0x4f | 0x80,0x66 | 0x80,0x6d | 0x80,0x7d | 0x80,0x07 | 0x80,0x7f | 0x80,
0x6f | 0x80,0x77 | 0x80,0x7c | 0x80,0x39 | 0x80,0x5e | 0x80,0x79 | 0x80,0x71 | 0x80 };
	
NIXIE_PORT=nixie[count];

}



//*******************循环显示0到9 延时没有严格计算
void NIXIE_FLOW()
{
       for(uchar count=0;count<=15;count++)
	   {
		  
		    
		NIXIE_SHOW(count);
		
		delay_second(7);
		   
	   }		   
    }
	//*********************数码管4位初始化
void NIXIE_4BIT_INIT()
{
	NIXIE_DDR = 0xff;
	
	NIXIE_PORT = 0x00;
	
	//***********准备工作
	NIXIE_DDR = 0XFF;
	
	NIXIE_CON_DDR |= (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3);
}
//********************************单位测试
	
void NIXIE_4BIT_0_SHOW(uchar T)
{
	
	
	//******************第3位
	
	NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	清低四位 
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XF7;//*********第3位
	
	//NIXIE_CON_PORT = ~(1 << 3);
	
	NIXIE_SHOW(T);
	
	delay_reduce(100);
	
}	
	
//********************************单位测试
	
void NIXIE_4BIT_1_SHOW(uchar T)
{
	
	
	//******************第2位
	
	NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	清低四位 
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XFB;//*********第2位
	
	//NIXIE_CON_PORT = ~(1 << 2);
	
	NIXIE_SHOW(T);
	
	
	delay_reduce(100);
	
	
}	

//********************************单位测试
	
void NIXIE_4BIT_2_SHOW(uchar T)
{
	
	
	//******************第1位
	
	 NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	清低四位
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XFD;//*********第1位
	
	//NIXIE_CON_PORT = ~(1 << 1);
	
	NIXIE_SHOW(T);

    
    delay_reduce(100);
    

}	

//********************************单位测试
	
void NIXIE_4BIT_3_SHOW(uchar T)
{
	
	
	//******************第0位
	
	NIXIE_CON_PORT = NIXIE_CON_PORT | 0X0F;//*********	清低四位 
	
	NIXIE_PORT = 0X00;
	
	
	NIXIE_CON_PORT = NIXIE_CON_PORT & 0XFE;//*********第0位
	
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
//********************四位数码管显示
//******************用改变最后一个显示的顺序来平衡亮度
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