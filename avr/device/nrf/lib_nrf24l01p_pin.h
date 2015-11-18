/*
 * lib_nrf24l01p_pin.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_NRF24L01P_PIN_H_
#define LIB_NRF24L01P_PIN_H_


//********************��ʼ������  Ӧ�Խ���Ӧ�ӿ�
#define NRF24L01P_DDR	DDRA
#define NRF24L01P_PIN	PINA
#define NRF24L01P_PORT	PORTA

#define CE		4
#define IRQ		5


int nrf24l01p_ce_bit_control(int bit);
int nrf24l01p_irq_bit_control(int bit);
void nrf24l01p_port_init();


int nrf24l01p_ce_bit_control(int bit)
{
	if (bit == 1)
	{
		NRF24L01P_PORT |= (1<<CE);
		return 0;
	}
	else if (bit == 0)
	{
		NRF24L01P_PORT &= ~(1<<CE);
		return 0;
	}
	else
	{
		return -1;
	}
}

int nrf24l01p_irq_bit_control(int bit)
{
	if (bit == 1)
	{
		NRF24L01P_PORT |= (1<<IRQ);
		return 0;
	}
	else if (bit == 0)
	{
		NRF24L01P_PORT &= ~(1<<IRQ);
		return 0;
	}
	else
	{
		return -1;
	}
}

/*************************************************************************
����:nRF24L01�˿ڳ�ʼ��
ע��:spi�˿�Ҳ�����ʼ��,��������
*************************************************************************/
void nrf24l01p_port_init()
{
	NRF24L01P_DDR |=((1<<CE));	//CE���
	NRF24L01P_DDR &=~((1<<IRQ));	//IRQ����
	
	NRF24L01P_PORT = 0x00;
}

#endif /* LIB_NRF24L01P_PIN_H_ */