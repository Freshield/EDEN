/*
 * lib_virtual_spi.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_VIRTUAL_SPI_H_
#define LIB_VIRTUAL_SPI_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

//********************��ʼ������  Ӧ�Խ���Ӧ�ӿ�
#define SPI_DDR		DDRA
#define SPI_PIN		PINA
#define SPI_PORT	PORTA

#define MISO	0
#define MOSI	1
#define SCK		2
#define CSN		3

#define uchar unsigned char
#define uint unsigned int



//*****************************���� ����������ļ�
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


//**********************************io��ʼ��
void spi_init()
{
	SPI_DDR = 0x00;
	SPI_DDR |= ((1<<MOSI)|(1<<SCK)|(1<<CSN));//����MOSI��SCK��CSN�������������
	SPI_DDR &= ~((1<<MISO));
	
	SPI_PORT = 0x00;
}

//******************************************SPI���ͽ���һ����� ����������Ӧ��data ���յĻ� 0x00
unsigned char spi_rw(unsigned char send_data)
{
	unsigned char recv_data = 0x00;

	//SPI0 CPOL=0 CPHA=0
	
	//Ƭѡ���ʹ�������
	//spi_csn_bit_control(0);
	
	delay_reduce(delay_time);
	
	for (int i = 0;i < 8;i++)
	{
		if (send_data & (0x80 >> i))//��λ��ǰ,��λ��ǰ��Ϊ(0x01<<i)
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
	
	//Ƭѡ���ߴ������
	//spi_csn_bit_control(1);
	
	return recv_data;
}


//************************************************************�ڶ��˿�SPI

//********************��ʼ������  Ӧ�Խ���Ӧ�ӿ�
#define SPI_DDR1		DDRB
#define SPI_PIN1		PINB
#define SPI_PORT1	    PORTB

#define MISO1	4
#define MOSI1	5
#define SCK1	6
#define CSN1	7

#define uchar unsigned char
#define uint unsigned int



//*****************************���� ����������ļ�
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


//**********************************io��ʼ��
void spi1_init()
{
	SPI_DDR1 = 0x00;
	SPI_DDR1 |= ((1<<MOSI1)|(1<<SCK1)|(1<<CSN1));//����MOSI��SCK��CSN�������������
	SPI_DDR1 &= ~((1<<MISO1));
	
	SPI_PORT1 = 0x00;
}

//******************************************SPI���ͽ���һ����� ����������Ӧ��data ���յĻ� 0x00
unsigned char spi1_rw(unsigned char send_data1)
{
	unsigned char recv_data1 = 0x00;

	//SPI0 CPOL=0 CPHA=0
	
	//Ƭѡ���ʹ�������
	//spi_csn_bit_control(0);
	
	delay_reduce(delay_time1);
	
	for (int i = 0;i < 8;i++)
	{
		if (send_data1 & (0x80 >> i))//��λ��ǰ,��λ��ǰ��Ϊ(0x01<<i)
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
	
	//Ƭѡ���ߴ������
	//spi_csn_bit_control(1);
	
	return recv_data1;
}
//************************************��������
/*MASTER*/
/*���� 
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
		for(count=0XBB;;count>>1)//*****����ͬʱѭ���ƶ�
		{
			
			receive_data=SPI_RW(0x00);
			
			PORTB=receive_data;
			delay_reduce(60000);
			
			SPI_RW(count);
		}
	}
}*/






#endif /* LIB_VIRTUAL_SPI_H_ */