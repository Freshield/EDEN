/*
 * lib_twi.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 

#ifndef LIB_TWI_H_
#define LIB_TWI_H_
//*********************有延时 应包含延时程序
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

//*********引脚 SDA PC1 SCL PC0**********


//**************错误处理***************

void TWI_ERROR()
{
	delay_reduce(5);
}

//*************主机初始化*********无中断

void M16_TWI_MASTER_INIT()
{
	DDRC |= (1 << 0)|(1 << 1);
	
	PORTC |= (1 << 0)|(1 << 1);
	
	TWBR = (((F_CPU / TWI_SCL) - 16) / 8);//********7.3728m BUAD 9600
	
	TWCR |= (1 << TWEN);//**********使能TWI
	
}

//**************主机发送数据***************

void M16_TWI_MASTER_SEND(char data)
{
	TWCR = (1 << TWINT)|(1 << TWSTA)|(1 << TWEN);//******START
	
	while(!(TWCR & (1 << TWINT)));//**********WAIT TWINT
	
	if((TWSR & 0XF8) != TWI_MT_START);//****************************
	                                 //*******判别START状态字
	TWI_ERROR();                     //*****************************
	
	TWDR = SLA_W;                    //*****************************************
	                                //***********装入SLA_W TWINT清零 启动发送地址
	TWCR = (1 << TWINT)|(1 << TWEN);//*******************************************
	
	while(!(TWCR & (1 << TWINT)));//*************WAIT TWINT
	
	if((TWSR & 0XF8) != TWI_MT_SLA_ACK);//****************************
	                                    //*******判别SLA_ACK状态字
	TWI_ERROR();                       //*****************************
	
	TWDR = data;                    //*****************************************
	                                //***********装入数据 TWINT清零 启动发送数据
	TWCR = (1 << TWINT)|(1 << TWEN);//*******************************************
	
	while(!(TWCR & (1 << TWINT)));//*************WAIT TWINT
	
	if((TWSR & 0XF8) != TWI_MT_DATA_ACK);//****************************
	                                    //*******判别DATA_ACK状态字
	TWI_ERROR();                       //*****************************
	
	TWCR = (1 << TWINT)|(1 << TWEN)|(1 << TWSTO);//*********STOP
	
}

//*************从机初始化*********

void M16_TWI_SLAVE_INIT()
{
	DDRC &= ~(1 << 0)|(1 << 1);
	
	PORTC |= (1 << 0)|(1 << 1);
	
	TWBR = (((F_CPU / TWI_SCL) - 16) / 8);//********7.3728m BUAD 9600
	
	TWAR = SLA_W;//******写从机地址
	
	TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWIE)|(1 << TWEN);//**********使能TWI 清零TWINT TWI中断 使能应答
	
}

//**************从机接收数据（中断）***************

uchar M16_TWI_SLAVE_RESERVE()//**********255为初始码
{
	
	uchar statue = 255;
	
	uchar get;
	
	get = TWSR & 0XF8;//*****获取状态码
	
	switch(get)
	{
		case TWI_SR_SLA_ACK:  //TW_STATUS=0x60,收到本机SLA+W,ACK已返回
		//清TWINT,下一步接收数据，返回ACK
		break;
		
		case TWI_SR_DATA_ACK: //TW_STATUS=0x80,以前SLA+W被寻址,收到数据,ACK已返回
		//接收数据
		
		statue = TWDR;
		
		//清TWINT,下一步接收数据，返回ACK
		break;
		
		case TWI_SR_STOP_RESTART:     //TW_STATUS=0xA0,清TWINT,收到STOP或RESTART
		break;
		
		default:             break;
		
		
		
	}
	TWCR |= (1 << TWINT)|(1 << TWEA)|(1 << TWIE)|(1 << TWEN);//**********使能TWI 清零TWINT TWI中断 使能应答
	
	return(statue);
}

#endif


#ifdef M128

//////////////////////////////////////////////////
// 
//////////////////////////////////////////////////

#endif

#endif /* LIB_TWI_H_ */