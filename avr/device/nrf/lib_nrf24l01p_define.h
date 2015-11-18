/*
 * lib_nrf24l01p_define.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_NRF24L01P_DEFINE_H_
#define LIB_NRF24L01P_DEFINE_H_

//��������
#define R_REGSITER	  0X00	//���Ĵ���	ֱ�����ַ��λ��
#define W_REGSITER	  0X20	//д�Ĵ���	ֱ�����ַ��λ��
#define R_RX_PAYLOAD  0X61	//������ 1-32 �ֽ�  ��0�ֽڿ�ʼ
#define W_TX_PAYLOAD  0XA0	//д���� 1-32 �ֽ�  ��0�ֽڿ�ʼ
#define FLUSH_TX	  0xE1	//���TX FIFO �Ĵ���
#define FLUSH_RX      0XE2	//���RX FIFO �Ĵ���  ����Ӧ���ź�ʱ����Ӧʹ�ô�����
#define RESUSE_TX_PL  0XE3	//����ʹ����һ����Ч���ݣ���CEΪ��ʱ�����ݰ��������·���
#define NOP			  0XFF	//��ָ�� ����ȡ������

//�Ĵ�����ַ
#define REG_CONFIG			0x00	//'Config' �Ĵ�����ַ
#define REG_EN_AA			0x01	//'Enable Auto Acknowledgment' �Ĵ�����ַ
#define REG_EN_RXADDR		0x02	//'Enabled RX addresses' �Ĵ�����ַ
#define REG_SETUP_AW		0x03	//'Setup address width' �Ĵ�����ַ
#define REG_SETUP_RETR		0x04	//'Setup Auto. Retrans' �Ĵ�����ַ
#define REG_RF_CH			0x05	//'RF channel' �Ĵ�����ַ
#define REG_RF_SETUP		0x06	//'RF setup' �Ĵ�����ַ
#define REG_STATUS			0x07	//'Status' �Ĵ�����ַ
#define REG_OBSERVE_TX		0x08	//'Observe TX' �Ĵ�����ַ
#define REG_CD				0x09	//'Carrier Detect' �Ĵ�����ַ
#define REG_RX_ADDR_P0		0x0A	//'RX address pipe0' �Ĵ�����ַ
#define REG_RX_ADDR_P1		0x0B	//'RX address pipe1' �Ĵ�����ַ
#define REG_RX_ADDR_P2		0x0C	//'RX address pipe2' �Ĵ�����ַ
#define REG_RX_ADDR_P3		0x0D	//'RX address pipe3' �Ĵ�����ַ
#define REG_RX_ADDR_P4		0x0E	//'RX address pipe4' �Ĵ�����ַ
#define REG_RX_ADDR_P5		0x0F	//'RX address pipe5' �Ĵ�����ַ
#define REG_TX_ADDR			0x10	//'TX address' �Ĵ�����ַ
#define REG_RX_PW_P0		0x11	//'RX payload width, pipe0' �Ĵ�����ַ
#define REG_RX_PW_P1		0x12	//'RX payload width, pipe1' �Ĵ�����ַ
#define REG_RX_PW_P2		0x13	//'RX payload width, pipe2' �Ĵ�����ַ
#define REG_RX_PW_P3		0x14	//'RX payload width, pipe3' �Ĵ�����ַ
#define REG_RX_PW_P4		0x15	//'RX payload width, pipe4' �Ĵ�����ַ
#define REG_RX_PW_P5		0x16	//'RX payload width, pipe5' �Ĵ�����ַ
#define REG_FIFO_STATUS		0x17	//'FIFO Status Register' �Ĵ�����ַ

//Config' �Ĵ���
#define MASK_RX_DR	6	//�������ж�RX_RD[1: IRQ���Ų���ʾRX_RD�ж�,0: RX_RD�жϲ���ʱIRQ���ŵ�ƽΪ��]
#define MASK_TX_DS	5	//�������ж�TX_DS[1: IRQ���Ų���ʾTX_DS�ж�,0: TX_DS�жϲ���ʱIRQ���ŵ�ƽΪ��]
#define MASK_MAX_RT	4	//�������ж�MAX_RT[1: IRQ���Ų���ʾMAX_RT�ж�,0: MAX_RT�жϲ���ʱIRQ���ŵ�ƽΪ��]
#define EN_CRC		3	//CRCʹ��,���EN_AA������һλΪ����EN_CRCǿ��Ϊ��
#define CRCO		2	//CRCģʽ [0: 8λCRCУ��,1: 16λCRCУ��]
#define PWR_UP		1	//��Դģʽ [1: �ϵ�,0: ����]
#define PRIM_RX		0	//����ģʽ [1: ����,0: ����]

//'Enable Auto Acknowledgment' �Ĵ���
#define ENAA_P5	5	//����ͨ��5�Զ�Ӧ�𿪹�[Ĭ��ֵ:1]
#define ENAA_P4	4	//����ͨ��4�Զ�Ӧ�𿪹�[Ĭ��ֵ:1]
#define ENAA_P3	3	//����ͨ��3�Զ�Ӧ�𿪹�[Ĭ��ֵ:1]
#define ENAA_P2	2	//����ͨ��2�Զ�Ӧ�𿪹�[Ĭ��ֵ:1]
#define ENAA_P1	1	//����ͨ��1�Զ�Ӧ�𿪹�[Ĭ��ֵ:1]
#define ENAA_P0	0	//����ͨ��0�Զ�Ӧ�𿪹�[Ĭ��ֵ:1]

//'Enabled RX addresses' �Ĵ���
#define ERX_P5	5	//��������ͨ��5����[Ĭ��ֵ:0]
#define ERX_P4	4	//��������ͨ��4����[Ĭ��ֵ:0]
#define ERX_P3	3	//��������ͨ��3����[Ĭ��ֵ:0]
#define ERX_P2	2	//��������ͨ��2����[Ĭ��ֵ:0]
#define ERX_P1	1	//��������ͨ��1����[Ĭ��ֵ:1]
#define ERX_P0	0	//��������ͨ��0����[Ĭ��ֵ:1]

//'Setup address width' �Ĵ���
#define AW1 1	//����/�����ַ���[00: ��Ч,01: 3�ֽڿ��,10: 4�ֽڿ��,11: 5�ֽڿ��]
#define AW0 0	//[Ĭ��ֵ:11]

//'Setup Auto. Retrans' �Ĵ���
#define ARD3	7	//ARDΪ����[Ĭ��ֵ:0000]
#define ARD2	6	//�Զ��ط���ʱ
#define ARD1	5	//'0000' �ȴ�250+86us,'0001' �ȴ�500+86us,'0010' �ȴ�750+86us,'1111' �ȴ�4000+86us
#define ARD0	4	//��ʱʱ����ָһ�����ݷ�����ɵ���һ�����ݿ�ʼ����֮���ʱ����
#define ARC3	3	//ARCΪ����[Ĭ��ֵ:11]
#define ARC2	2	//�Զ��ط�����
#define ARC1	1	//'0000' ��ֹ,'0001' �ط�һ��...'1111' �ط�15��
#define ARC0	0	//

//'RF channel' �Ĵ���
#define RF_CH6	6	//��Ƶͨ��
#define RF_CH5	5	//����nRF24L01 ����ͨ��Ƶ��
#define RF_CH4	4	//[Ĭ��ֵ:0000010]
#define RF_CH3	3	//
#define RF_CH2	2	//
#define RF_CH1	1	//
#define RF_CH0	0	//

//'RF setup' �Ĵ���
#define PLL_LOCK	4	//PLL_LOCK ������Ӧ���ڲ���ģʽ[Ĭ��ֵ:0]
#define RF_DR		3	//���ݴ����� [0: 1Mbps,1: 2Mbps][Ĭ��ֵ:1]
#define RF_PWR1		2	//���书��[Ĭ��ֵ:11]
#define RF_PWR0		1	//[00: -18dBm,01: -12dBm,10: -6dBm,11: 0dBm]
#define LNA_HCURR	0	//�������Ŵ������濪��[Ĭ��ֵ:1]

//'Status' �Ĵ���
#define RX_DR				6	//������������ж�,�����յ���Ч���ݺ�����ж�
#define	TX_DS				5	//���ݷ�������ж�,�����ݷ�����ɺ�����ж�.����������Զ�Ӧ��ģʽ��,ֻ�е����յ�Ӧ���źź�Ų����ж�
#define MAX_RT				4	//�ﵽ�����ط��ж�,������жϲ�������������ϵͳ���ܽ���ͨѶ
#define RX_P_NO2			3	//��������ͨ����[Ĭ��ֵ:111][ֻ��]
#define RX_P_NO1			2	//[000-101: ����ͨ����,110: δʹ��,111: RX FIFO�Ĵ���Ϊ��]
#define RX_P_NO0			1	//
#define STATUS_TX_FULL		0	//TX FIFO�Ĵ�������־ [1: ����,0: δ��][Ĭ��ֵ:0][ֻ��]

//'Observe TX' �Ĵ���
#define PLOS_CNT3	7	//���ݰ���ʧ������
#define PLOS_CNT2	6	//����ʧ15�����ݰ���˼Ĵ�������
#define PLOS_CNT1	5	//��дRF_CH�Ĵ���ʱ�˼Ĵ�����λ
#define PLOS_CNT0	4	//[Ĭ��ֵ:0][ֻ��]
#define ARC_CNT3	3	//�ط�������
#define ARC_CNT2	2	//���������ݰ�ʱ�˼Ĵ�����λ
#define ARC_CNT1	1	//
#define ARC_CNT0	0	//[Ĭ��ֵ:0][ֻ��]

//'Carrier Detect' �Ĵ�����ַ
#define CD	0	//�ز���� [Ĭ��ֵ:0][ֻ��]

//'FIFO Status Register' �Ĵ���
#define TX_REUSE	6	//����ʹ�����һ�����ݰ�,��λ����CEΪ�ߵ�ƽ״̬ʱ���Ϸ�����һ���ݰ�,ͨ��ָ��REUSE_TX_PL��λ,ͨ��W_TX_PALOAD��FLUSH_TX��λ
#define TX_FULL		5	//TX FIFO�Ĵ�������־ [1: ����,0: δ��][Ĭ��ֵ:0][ֻ��]
#define TX_EMPTY	4	//TX FIFO�Ĵ����ձ�־ [1: �ѿ�,0: δ��][Ĭ��ֵ:0][ֻ��]
#define RX_FULL		1	//RX FIFO�Ĵ�������־ [1: ����,0: δ��][Ĭ��ֵ:0][ֻ��]
#define RX_EMPTY	0	//RX FIFO�Ĵ����ձ�־ [1: �ѿ�,0: δ��][Ĭ��ֵ:0][ֻ��]


#define ADR_SIZE	5	//��ַ��С
#define PLOAD_SIZE	32	//���ݻ�������С

#endif /* LIB_NRF24L01P_DEFINE_H_ */