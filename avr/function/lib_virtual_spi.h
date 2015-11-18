/*
 * lib_virtual_spi.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_VIRTUAL_SPI_H_
#define LIB_VIRTUAL_SPI_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//********************初始化定义  应对接相应接口
#define SPI_DDR		DDRA
#define SPI_PIN		PINA
#define SPI_PORT	PORTA

#define MISO	0
#define MOSI	1
#define SCK		2
#define CSN		3

#define uchar unsigned char
#define uint unsigned int



//*****************************声明 本库包含的文件
int spi_csn_bit_control(int bit);
int spi_mosi_bit_control(int bit);
int spi_miso_bit_control(int bit);
int spi_sck_bit_control(int bit);

void spi_init();
uchar spi_rw(uchar send_data);
uchar delay_time=20;

unsigned char led_config[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


int spi_csn_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT |= (1<<CSN);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT &= ~(1<<CSN);
		return 0;
	}
	else
	{
		return -1;
	}
}

int spi_mosi_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT |= (1<<MOSI);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT &= ~(1<<MOSI);
		return 0;
	}
	else
	{
		return -1;
	}
}

int spi_miso_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT |= (1<<MISO);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT &= ~(1<<MISO);
		return 0;
	}
	else
	{
		return -1;
	}
}

int spi_sck_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT |= (1<<SCK);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT &= ~(1<<SCK);
		return 0;
	}
	else
	{
		return -1;
	}
}


//**********************************io初始化
void spi_init()
{
	SPI_DDR = 0x00;
	SPI_DDR |= ((1<<MOSI)|(1<<SCK)|(1<<CSN));//设置MOSI、SCK、CSN输出，其余输入
	SPI_DDR &= ~((1<<MISO));
	
	SPI_PORT = 0x00;
}

//******************************************SPI发送接收一体程序 发送输入相应的data 接收的话 0x00
unsigned char spi_rw(unsigned char send_data)
{
	unsigned char recv_data = 0x00;

	//SPI0 CPOL=0 CPHA=0
	
	//片选拉低传送数据
	//spi_csn_bit_control(0);
	
	delay_reduce(delay_time);
	
	for (int i = 0;i < 8;i++)
	{
		if (send_data & (0x80 >> i))//高位在前,低位在前改为(0x01<<i)
		{
			spi_mosi_bit_control(1);
		}
		else
		{
			spi_mosi_bit_control(0);
		}
		delay_reduce(delay_time);
		spi_sck_bit_control(1);
		
		if ((SPI_PIN >> MISO) & 0x01)
		{
			recv_data |= (0x80>>i);
		}
		delay_reduce(delay_time);
		spi_sck_bit_control(0);
	}
	delay_reduce(delay_time);
	
	//片选拉高传送完毕
	//spi_csn_bit_control(1);
	
	return recv_data;
}


//************************************************************第二端口SPI

//********************初始化定义  应对接相应接口
#define SPI_DDR1		DDRB
#define SPI_PIN1		PINB
#define SPI_PORT1	    PORTB

#define MISO1	4
#define MOSI1	5
#define SCK1	6
#define CSN1	7

#define uchar unsigned char
#define uint unsigned int



//*****************************声明 本库包含的文件
int spi_csn1_bit_control(int bit);
int spi_mosi1_bit_control(int bit);
int spi_miso1_bit_control(int bit);
int spi_sck1_bit_control(int bit);

void spi1_init();
uchar spi1_rw(uchar send_data1);
uchar delay_time1=20;


int spi_csn1_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT1 |= (1<<CSN1);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT1 &= ~(1<<CSN1);
		return 0;
	}
	else
	{
		return -1;
	}
}

int spi_mosi1_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT1 |= (1<<MOSI1);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT1 &= ~(1<<MOSI1);
		return 0;
	}
	else
	{
		return -1;
	}
}

int spi_miso1_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT1 |= (1<<MISO1);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT1 &= ~(1<<MISO1);
		return 0;
	}
	else
	{
		return -1;
	}
}

int spi_sck1_bit_control(int bit)
{
	if (bit == 1)
	{
		SPI_PORT1 |= (1<<SCK1);
		return 0;
	}
	else if (bit == 0)
	{
		SPI_PORT1 &= ~(1<<SCK1);
		return 0;
	}
	else
	{
		return -1;
	}
}


//**********************************io初始化
void spi1_init()
{
	SPI_DDR1 = 0x00;
	SPI_DDR1 |= ((1<<MOSI1)|(1<<SCK1)|(1<<CSN1));//设置MOSI、SCK、CSN输出，其余输入
	SPI_DDR1 &= ~((1<<MISO1));
	
	SPI_PORT1 = 0x00;
}

//******************************************SPI发送接收一体程序 发送输入相应的data 接收的话 0x00
unsigned char spi1_rw(unsigned char send_data1)
{
	unsigned char recv_data1 = 0x00;

	//SPI0 CPOL=0 CPHA=0
	
	//片选拉低传送数据
	//spi_csn_bit_control(0);
	
	delay_reduce(delay_time1);
	
	for (int i = 0;i < 8;i++)
	{
		if (send_data1 & (0x80 >> i))//高位在前,低位在前改为(0x01<<i)
		{
			spi_mosi1_bit_control(1);
		}
		else
		{
			spi_mosi1_bit_control(0);
		}
		delay_reduce(delay_time1);
		spi_sck1_bit_control(1);
		
		if ((SPI_PIN1 >> MISO1) & 0x01)
		{
			recv_data1 |= (0x80>>i);
		}
		delay_reduce(delay_time1);
		spi_sck1_bit_control(0);
	}
	delay_reduce(delay_time1);
	
	//片选拉高传送完毕
	//spi_csn_bit_control(1);
	
	return recv_data1;
}
//************************************程序样例
/*MASTER*/
/*样例 
int main(void)
{
	SPI_MASTER_init();
	
	
	DDRB=0xff;
	PORTB=0x00;
	
    while(1)
    {
       for (uchar count = 0;count < 255;count++)
	   {
		   SPI_RW(count);
		   delay_reduce(60000);
		   delay_reduce(60000);
		   delay_reduce(60000);
		   delay_reduce(60000);
		   
	   }		 
    }
}
*/

/*SLAVE
int main(void)
{
	SPI_init();
	uchar count;
	DDRB=0xff;
	PORTB=0x00;
	uchar receive_data;
	while(1)
	{
		for(count=0XBB;;count>>1)//*****接收同时循环移动
		{
			
			receive_data=SPI_RW(0x00);
			
			PORTB=receive_data;
			delay_reduce(60000);
			
			SPI_RW(count);
		}
	}
}*/






#endif /* LIB_VIRTUAL_SPI_H_ */