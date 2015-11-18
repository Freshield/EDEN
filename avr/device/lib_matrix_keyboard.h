/*
 * lib_matrix_keyboard.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_MATRIX_KEYBOARD_H_
#define LIB_MATRIX_KEYBOARD_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//*******************************初始化 
//*****************************普通矩阵键盘 应在开始时DDRB为0xf0 PORTB为0x0f 
//*****************************N方矩阵键盘 应在开始时DDRB DB0 DB1 DB2 DB3为输出 PORTB为0x0f 中断部分DD2应为输入 
#define uchar unsigned char
#define uint unsigned int
#define MATRIX_KEY_DDR DDRB
#define MATRIX_KEY_PORT PORTB
#define MATRIX_KEY_PIN PINB

//*********************************************************************************************************//
//******************************普通矩阵键盘 非N方+1矩阵键盘***********************************************//
//*********************************************************************************************************//
//**************判断有无按键按下(MATRIX_DDR=0XF0 MATRIX_PORT=0X0F)
uchar NORMAL_KEY_DOWN()
{
	
	
	
	delay_reduce(100);
	uchar i;
	if(MATRIX_KEY_PIN!=0x0f)
	{
		i=1;
	}
	else 
	{
		i=0;
	}
	return i;

}

//****************读取键值
uchar NORMAL_KEY_READ()
{
	uchar KEY_NUM=16;
	//先高四位输出 低四位输入 高四位清零 通过读取键值判断键位
	MATRIX_KEY_DDR=0XF0;MATRIX_KEY_PORT=0X0F;delay_reduce(10);
	
	switch(MATRIX_KEY_PIN)
	{
		case 0x0e:KEY_NUM=0;break;
		
		case 0x0d:KEY_NUM=1;break;
		
		case 0x0b:KEY_NUM=2;break;
		
		case 0x07:KEY_NUM=3;break;
		
		default:KEY_NUM=16;
		
	}
	//第二次是 高四位输入 低四位输出 低四位清零 读取键值 加上相应的数值
	MATRIX_KEY_DDR=0X0f;MATRIX_KEY_PORT=0Xf0;delay_reduce(10);
	
	switch(MATRIX_KEY_PIN)
	{
		case 0xe0:KEY_NUM += 0;break;
		
		case 0xd0:KEY_NUM += 4;break;
		
		case 0xb0:KEY_NUM += 8;break;
		
		case 0x70:KEY_NUM += 12;break;
		
		default:KEY_NUM = 16;
	}
	return KEY_NUM;
}



//*********************************************************************************************************//
//******************************          N方矩阵键盘        ***********************************************//
//*********************************************************************************************************//
//**************按键由PD2来进行终端（中断0） 有中断后读取键值与编码表比较 
uchar N_SQUARE_KEY_READ()
{
	
	MATRIX_KEY_DDR = 0xF0;
	MATRIX_KEY_PORT = 0x00;
	DDRD = 0X00;
	PORTD = 0Xff;//***********重置PD2准备键值
	uchar REAL_NUM = 16;//******16为错值
	uchar KEY_NUM;
	uchar MEDIM_NUM;
	
	//******************第一行搜索
	MATRIX_KEY_DDR = 0x01;//******第一位为输出其他为输入
	MATRIX_KEY_PORT = 0x01;//*****第一位输出1
	delay_reduce(100);       //*******一定要有延时 否则无法显示 电流反应没有那么快
	if (PIND != 0xff) 
    {
		KEY_NUM = MATRIX_KEY_PIN;//*****读取键值
		    switch(KEY_NUM)
		    {
			    case 0x09: REAL_NUM = 0;break;
			    
			    case 0x05: REAL_NUM = 4;break;
			    
			    case 0x03: REAL_NUM = 8;break;
			     
			    case 0x01: REAL_NUM = 12;break;
			    
				default:REAL_NUM = 16;
		    }
	    return REAL_NUM;
		//*********************等待按键抬起
		delay_reduce(100);
		MATRIX_KEY_DDR = 0xFF;
		MATRIX_KEY_PORT = 0x0f;
		DDRD = 0x00;
		PORTD = 0xff;
		delay_reduce(100);
		while(PIND != 0xff)
		{
		}
    }
//****************************************************************第二行搜索	
	else
	{
		
	MATRIX_KEY_DDR = 0x02;//******第二位为输出其他为输入
	MATRIX_KEY_PORT = 0x02;//*****第二位输出1
	delay_reduce(100);       //*******一定要有延时 否则无法显示 电流反应没有那么快
    if (PIND != 0xff) 
    {
		KEY_NUM = MATRIX_KEY_PIN;//*****读取键值
		    switch(KEY_NUM)
		    {
			    case 0x0a: REAL_NUM = 1;break;
			    
			    case 0x06: REAL_NUM = 5;break;
			    
			    case 0x02: REAL_NUM = 9;break;
			     
			    case 0x03: REAL_NUM = 13;break;
			    
				default:REAL_NUM = 16;
		    }
			
	    return REAL_NUM;
		//*********************等待按键抬起
		delay_reduce(100);
		MATRIX_KEY_DDR = 0xFF;
		MATRIX_KEY_PORT = 0x0f;
		DDRD = 0x00;
		PORTD = 0xff;
		delay_reduce(100);
		while(PIND != 0xff) 
		{
		}			
	    
    }
//***********************************************************第三行搜索	
	else
	{
		
	MATRIX_KEY_DDR = 0x04;//******第三位为输出其他为输入
	MATRIX_KEY_PORT = 0x04;//*****第三位输出1
	delay_reduce(100);       //*******一定要有延时 否则无法显示 电流反应没有那么快
	KEY_NUM = MATRIX_KEY_PIN;//*****读取键值
	
    if (PIND != 0xff) 
    {
		    switch(KEY_NUM)
		    {
			    case 0x0c: REAL_NUM = 2;break;
			    
			    case 0x04: REAL_NUM = 6;break;
			    
			    case 0x06: REAL_NUM = 10;break;
			     
			    case 0x05: REAL_NUM = 14;break;
			    
				default:REAL_NUM = 16;
		    }
	    return REAL_NUM;
		//*********************等待按键抬起
		delay_reduce(100);
		MATRIX_KEY_DDR = 0xFF;
		MATRIX_KEY_PORT = 0x0f;
		DDRD = 0x00;
		PORTD = 0xff;
		delay_reduce(100);
		while(PIND != 0xff)
		{
		}
    }
//************************************************************第四行搜索	
	else
	{
		
	MATRIX_KEY_DDR = 0x08;//******第四位为输出其他为输入
	MATRIX_KEY_PORT = 0x08;//*****第四位输出1
	delay_reduce(100);       //*******一定要有延时 否则无法显示 电流反应没有那么快
	KEY_NUM = MATRIX_KEY_PIN;//*****读取键值
	
    if (PIND != 0xff) 
    {
		    switch(KEY_NUM)
		    {
			    case 0x08: REAL_NUM = 3;break;
			    
			    case 0x0c: REAL_NUM = 7;break;
			    
			    case 0x0a: REAL_NUM = 11;break;
			     
			    case 0x09: REAL_NUM = 15;break;
			    
				default:REAL_NUM = 16;
		    }
	    return REAL_NUM;
		//*********************等待按键抬起
		delay_reduce(100);
		MATRIX_KEY_DDR = 0xFF;
		MATRIX_KEY_PORT = 0x0f;
		DDRD = 0x00;
		PORTD = 0xff;
		delay_reduce(100);
		while(PIND != 0xff)
		{
		}
    }
	}
	
	}
	
	}
	
	
}
//******************************N方矩阵键盘 中断样例M128***********************************************//


/*
ISR(INT0_vect)
{ 
	EICRA = ~(1<<INT0);//关外部中断0
	delay_reduce(100);
	if(PIND != 0xff)//***********去抖
	{
	
	MEDIUM_SHOW = N_SQUARE_KEY_READ();
	
	
	
	//*****************等待按键抬起
	MATRIX_KEY_DDR = 0xFF; 
	MATRIX_KEY_PORT = 0x0f;
	DDRD = 0x00;
	PORTD = 0xff; 
	delay_reduce(100);   
	 while(PIND != 0xff) 
	 {  
		 
	 }	 
	 delay_reduce(100); 
	 //**********************************************************************************************
	 //**********************************************************************************************
	 test_send_data[1] = MEDIUM_SHOW;//**********************************这里是要做的事情
	 nrf24l01p_buffer_write(W_TX_PAYLOAD,test_send_data,32);//***********这里是要做的事情
	 //**********************************************************************************************
	 //**********************************************************************************************
	 delay_reduce(100);
	 
	  
	MATRIX_KEY_DDR = 0xFF;
	MATRIX_KEY_PORT = 0x0f;
	DDRD = 0x00;
	PORTD = 0xff;
	delay_reduce(100);	  
	 EICRA = (1<<INT0);//开外部中断0
	 }	 
	else EICRA = (1<<INT0);//开外部中断0
}


int main(void)
{
	
	MATRIX_KEY_DDR=0xFF;
	MATRIX_KEY_PORT=0x0f;
	DDRD = 0x00;
	PORTD = 0xff;
	EXTERNAL_INTERRUPT0_INIT_M128();
	sei();
	while(1)
	{
	}		
*/



#endif /* LIB_MATRIX_KEYBOARD_H_ */