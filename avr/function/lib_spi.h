/*
 * lib_spi.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_SPI_H_
#define LIB_SPI_H_

//#define M8
#define M16
//#define M128



#ifdef M8


//********************��ʼ������  Ӧ�Խ���Ӧ�ӿ� M8��SPI�� SCK----PB5 MISO---PB4 MOSI---PB3 SS---PB2
#define SCK 5
#define MISO 4
#define MOSI 3
#define SS 2


void SPI_SLAVE_M8_init()
{
	DDRB |= (1<<MOSI);
	DDRB &= ~((1<<MISO)|(1<<SCK)|(1<<SS));
	SPCR = (1<<SPIE)|(1<<SPE);//***********LSB��MSB��˳�����Ҫ ���ܻ��������ҵ� һ��ע��
	SPSR = 0X00;
}

#endif













#ifdef M16


//********************��ʼ������  Ӧ�Խ���Ӧ�ӿ� M16��SPI�� SCK----PB7 MISO---PB6 MOSI---PB5 SS---PB4
#define SCK 7
#define MISO 6
#define MOSI 5
#define SS 4

void SPI_MASTER_M16_init()
{
	DDRB |= (1 << MOSI)|(1 << SCK)|(1 << SS);
	
	DDRB &= ~(1 << MISO);
	
	SPCR |= (1 << SPIE)|(1 << SPE)|(1 << MSTR)|(1 << SPR0);//****16��Ƶ
	
	
	
}


void SPI_SLAVE_M16_init()
{
	DDRB |= (1<<MISO);
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));
	SPCR |= (1<<SPIE)|(1<<SPE)|(1<<SPR0);//***********LSB��MSB��˳�����Ҫ ���ܻ��������ҵ� һ��ע�� 16��Ƶ

}

void SPI_MasterTransmit(char cData)
{
	PORTB &= ~(1 << SS);
	
	SPCR |= (1 << MSTR);// MSTR��ʱ�ᱻ���㣬����ǿ�ƽ�������ģʽ
	
	SPDR = cData;
	
	//********������ж���дһ�� PORTB |= (1 << SS);�������ָ�
}

#endif






#endif /* LIB_SPI_H_ */