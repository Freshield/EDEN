/*
 * lib_matrix_keyboard.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_MATRIX_KEYBOARD_H_
#define LIB_MATRIX_KEYBOARD_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//*******************************��ʼ�� 
//*****************************��ͨ������� Ӧ�ڿ�ʼʱDDRBΪ0xf0 PORTBΪ0x0f 
//*****************************N��������� Ӧ�ڿ�ʼʱDDRB DB0 DB1 DB2 DB3Ϊ��� PORTBΪ0x0f �жϲ���DD2ӦΪ���� 
#define uchar unsigned char
#define uint unsigned int
#define MATRIX_KEY_DDR DDRB
#define MATRIX_KEY_PORT PORTB
#define MATRIX_KEY_PIN PINB

//*********************************************************************************************************//
//******************************��ͨ������� ��N��+1�������***********************************************//
//*********************************************************************************************************//
//**************�ж����ް�������(MATRIX_DDR=0XF0 MATRIX_PORT=0X0F)
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

//****************��ȡ��ֵ
uchar NORMAL_KEY_READ()
{
	uchar KEY_NUM=16;
	//�ȸ���λ��� ����λ���� ����λ���� ͨ����ȡ��ֵ�жϼ�λ
	MATRIX_KEY_DDR=0XF0;MATRIX_KEY_PORT=0X0F;delay_reduce(10);
	
	switch(MATRIX_KEY_PIN)
	{
		case 0x0e:KEY_NUM=0;break;
		
		case 0x0d:KEY_NUM=1;break;
		
		case 0x0b:KEY_NUM=2;break;
		
		case 0x07:KEY_NUM=3;break;
		
		default:KEY_NUM=16;
		
	}
	//�ڶ����� ����λ���� ����λ��� ����λ���� ��ȡ��ֵ ������Ӧ����ֵ
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
//******************************          N���������        ***********************************************//
//*********************************************************************************************************//
//**************������PD2�������նˣ��ж�0�� ���жϺ��ȡ��ֵ������Ƚ� 
uchar N_SQUARE_KEY_READ()
{
	
	MATRIX_KEY_DDR = 0xF0;
	MATRIX_KEY_PORT = 0x00;
	DDRD = 0X00;
	PORTD = 0Xff;//***********����PD2׼����ֵ
	uchar REAL_NUM = 16;//******16Ϊ��ֵ
	uchar KEY_NUM;
	uchar MEDIM_NUM;
	
	//******************��һ������
	MATRIX_KEY_DDR = 0x01;//******��һλΪ�������Ϊ����
	MATRIX_KEY_PORT = 0x01;//*****��һλ���1
	delay_reduce(100);       //*******һ��Ҫ����ʱ �����޷���ʾ ������Ӧû����ô��
	if (PIND != 0xff) 
    {
		KEY_NUM = MATRIX_KEY_PIN;//*****��ȡ��ֵ
		    switch(KEY_NUM)
		    {
			    case 0x09: REAL_NUM = 0;break;
			    
			    case 0x05: REAL_NUM = 4;break;
			    
			    case 0x03: REAL_NUM = 8;break;
			     
			    case 0x01: REAL_NUM = 12;break;
			    
				default:REAL_NUM = 16;
		    }
	    return REAL_NUM;
		//*********************�ȴ�����̧��
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
//****************************************************************�ڶ�������	
	else
	{
		
	MATRIX_KEY_DDR = 0x02;//******�ڶ�λΪ�������Ϊ����
	MATRIX_KEY_PORT = 0x02;//*****�ڶ�λ���1
	delay_reduce(100);       //*******һ��Ҫ����ʱ �����޷���ʾ ������Ӧû����ô��
    if (PIND != 0xff) 
    {
		KEY_NUM = MATRIX_KEY_PIN;//*****��ȡ��ֵ
		    switch(KEY_NUM)
		    {
			    case 0x0a: REAL_NUM = 1;break;
			    
			    case 0x06: REAL_NUM = 5;break;
			    
			    case 0x02: REAL_NUM = 9;break;
			     
			    case 0x03: REAL_NUM = 13;break;
			    
				default:REAL_NUM = 16;
		    }
			
	    return REAL_NUM;
		//*********************�ȴ�����̧��
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
//***********************************************************����������	
	else
	{
		
	MATRIX_KEY_DDR = 0x04;//******����λΪ�������Ϊ����
	MATRIX_KEY_PORT = 0x04;//*****����λ���1
	delay_reduce(100);       //*******һ��Ҫ����ʱ �����޷���ʾ ������Ӧû����ô��
	KEY_NUM = MATRIX_KEY_PIN;//*****��ȡ��ֵ
	
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
		//*********************�ȴ�����̧��
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
//************************************************************����������	
	else
	{
		
	MATRIX_KEY_DDR = 0x08;//******����λΪ�������Ϊ����
	MATRIX_KEY_PORT = 0x08;//*****����λ���1
	delay_reduce(100);       //*******һ��Ҫ����ʱ �����޷���ʾ ������Ӧû����ô��
	KEY_NUM = MATRIX_KEY_PIN;//*****��ȡ��ֵ
	
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
		//*********************�ȴ�����̧��
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
//******************************N��������� �ж�����M128***********************************************//


/*
ISR(INT0_vect)
{ 
	EICRA = ~(1<<INT0);//���ⲿ�ж�0
	delay_reduce(100);
	if(PIND != 0xff)//***********ȥ��
	{
	
	MEDIUM_SHOW = N_SQUARE_KEY_READ();
	
	
	
	//*****************�ȴ�����̧��
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
	 test_send_data[1] = MEDIUM_SHOW;//**********************************������Ҫ��������
	 nrf24l01p_buffer_write(W_TX_PAYLOAD,test_send_data,32);//***********������Ҫ��������
	 //**********************************************************************************************
	 //**********************************************************************************************
	 delay_reduce(100);
	 
	  
	MATRIX_KEY_DDR = 0xFF;
	MATRIX_KEY_PORT = 0x0f;
	DDRD = 0x00;
	PORTD = 0xff;
	delay_reduce(100);	  
	 EICRA = (1<<INT0);//���ⲿ�ж�0
	 }	 
	else EICRA = (1<<INT0);//���ⲿ�ж�0
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