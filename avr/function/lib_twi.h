/*
 * lib_twi.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_TWI_H_
#define LIB_TWI_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char
#define uint unsigned int

//#define M8
#define M16
//#define M128


#ifdef M16

//********MT******************

#define TWI_MT_START 0X08

#define TWI_MT_RESTART 0X10

#define TWI_MT_SLA_ACK 0X18

#define TWI_MT_SLA_NACK 0X20

#define TWI_MT_DATA_ACK 0X28

#define TWI_MT_DATA_NACK 0X30

//********MR********************

#define TWI_MR_START 0X08

#define TWI_MR_RESTART 0X10

#define TWI_MR_SLA_ACK 0X40

#define TWI_MR_SLA_NACK 0X48

#define TWI_MR_DATA_ACK 0X50

#define TWI_MR_DATA_NACK 0X58

//******SR********************

#define TWI_SR_SLA_ACK 0X60

#define TWI_SR_RADIO_ACK 0X70

#define TWI_SR_DATA_ACK 0X80

#define TWI_SR_DATA_NACK 0X88

#define TWI_SR_STOP_RESTART 0XA0

//**********ST************

#define TWI_ST_SLA_ACK 0XA8

#define TWI_ST_DATA_ACK 0XB8

#define TWI_ST_DATA_NACK 0XC0

//***********SLA_W**********

#define SLA_W 0X28

//***********TWI_SCL

#define TWI_SCL 9600UL

//********F_CPU

#define F_CPU 7372800UL

//////////////////////////////////////////////////
////M16 TWI
//////////////////////////////////////////////////

//*********���� SDA PC1 SCL PC0**********


//**************������***************

void TWI_ERROR()
{
	delay_reduce(5);
}

//*************������ʼ��*********���ж�

void M16_TWI_MASTER_INIT()
{
	DDRC |= (1 << 0)|(1 << 1);
	
	PORTC |= (1 << 0)|(1 << 1);
	
	TWBR = (((F_CPU / TWI_SCL) - 16) / 8);//********7.3728m BUAD 9600
	
	TWCR |= (1 << TWEN);//**********ʹ��TWI
	
}

//**************������������***************

void M16_TWI_MASTER_SEND(char data)
{
	TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);//******START
	
	while(!(TWCR & (1 << TWINT)));//**********WAIT TWINT
	
	if((TWSR & 0XF8) != TWI_MT_START);//****************************
	                                 //*******�б�START״̬��
	TWI_ERROR();                     //*****************************
	
	TWDR = SLA_W;                    //*****************************************
	                                //***********װ��SLA_W TWINT���� �������͵�ַ
	TWCR = (1 << TWINT)|(1 << TWEN);//*******************************************
	
	while(!(TWCR & (1 << TWINT)));//*************WAIT TWINT
	
	if((TWSR & 0XF8) != TWI_MT_SLA_ACK);//****************************
	                                    //*******�б�SLA_ACK״̬��
	TWI_ERROR();                       //*****************************
	
	TWDR = data;                    //*****************************************
	                                //***********װ������ TWINT���� ������������
	TWCR = (1 << TWINT)|(1 << TWEN);//*******************************************
	
	while(!(TWCR & (1 << TWINT)));//*************WAIT TWINT
	
	if((TWSR & 0XF8) != TWI_MT_DATA_ACK);//****************************
	                                    //*******�б�DATA_ACK״̬��
	TWI_ERROR();                       //*****************************
	
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);//*********STOP
	
}

//*************�ӻ���ʼ��*********

void M16_TWI_SLAVE_INIT()
{
	DDRC &= ~(1 << 0)|(1 << 1);
	
	PORTC |= (1 << 0)|(1 << 1);
	
	TWBR = (((F_CPU / TWI_SCL) - 16) / 8);//********7.3728m BUAD 9600
	
	TWAR = SLA_W;//******д�ӻ���ַ
	
	TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWIE)|(1 << TWEN);//**********ʹ��TWI ����TWINT TWI�ж� ʹ��Ӧ��
	
}

//**************�ӻ��������ݣ��жϣ�***************

uchar M16_TWI_SLAVE_RESERVE()//**********255Ϊ��ʼ��
{
	
	uchar statue = 255;
	
	uchar get;
	
	get = TWSR & 0XF8;//*****��ȡ״̬��
	
	switch(get)
	{
		case TWI_SR_SLA_ACK:  //TW_STATUS=0x60,�յ�����SLA+W,ACK�ѷ���
		//��TWINT,��һ���������ݣ�����ACK
		break;
		
		case TWI_SR_DATA_ACK: //TW_STATUS=0x80,��ǰSLA+W��Ѱַ,�յ�����,ACK�ѷ���
		//��������
		
		statue = TWDR;
		
		//��TWINT,��һ���������ݣ�����ACK
		break;
		
		case TWI_SR_STOP_RESTART:     //TW_STATUS=0xA0,��TWINT,�յ�STOP��RESTART
		break;
		
		default:             break;
		
		
		
	}
	TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWIE)|(1 << TWEN);//**********ʹ��TWI ����TWINT TWI�ж� ʹ��Ӧ��
	
	return(statue);
}

#endif


#ifdef M128

//////////////////////////////////////////////////
// 
//////////////////////////////////////////////////

#endif

#endif /* LIB_TWI_H_ */