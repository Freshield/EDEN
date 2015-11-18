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


//********************初始化定义  应对接相应接口 M8的SPI口 SCK----PB5 MISO---PB4 MOSI---PB3 SS---PB2
#define SCK 5
#define MISO 4
#define MOSI 3
#define SS 2


void SPI_SLAVE_M8_init()
{
	DDRB |= (1<<MOSI);
	DDRB &= ~((1<<MISO)|(1<<SCK)|(1<<SS));
	SPCR = (1<<SPIE)|(1<<SPE);//***********LSB和MSB的顺序很重要 可能会让数据乱掉 一定注意
	SPSR = 0X00;
}

#endif













#ifdef M16


//********************初始化定义  应对接相应接口 M16的SPI口 SCK----PB7 MISO---PB6 MOSI---PB5 SS---PB4
#define SCK 7
#define MISO 6
#define MOSI 5
#define SS 4

void SPI_MASTER_M16_init()
{
	DDRB |= (1 << MOSI)|(1 << SCK)|(1 << SS);
	
	DDRB &= ~(1 << MISO);
	
	SPCR |= (1 << SPIE)|(1 << SPE)|(1 << MSTR)|(1 << SPR0);//****16分频
	
	
	
}


void SPI_SLAVE_M16_init()
{
	DDRB |= (1<<MISO);
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));
	SPCR |= (1<<SPIE)|(1<<SPE)|(1<<SPR0);//***********LSB和MSB的顺序很重要 可能会让数据乱掉 一定注意 16分频

}

void SPI_MasterTransmit(char cData)
{
	PORTB &= ~(1 << SS);
	
	SPCR |= (1 << MSTR);// MSTR有时会被清零，这里强制进入主机模式
	
	SPDR = cData;
	
	//********最好在中断中写一句 PORTB |= (1 << SS);这样来恢复
}

#endif






#endif /* LIB_SPI_H_ */