/*
 * lib_adc.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_ADC_H_
#define LIB_ADC_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif

#define uchar unsigned char
#define uint unsigned int

//******************M16��adc����********************//

//***********************ADC�Ļ�ȡ*****************//

int M16_ADC_CATCH(char num)
{
	int result;
	
	int back;
	
	char hun,ten,one;
	
	//************IO�ڼ���
	
	DDRA &= ~(1 << 0);//*******��Ϊ����
	
	//***********�趨ת��
	
	ADMUX = num;
	
	delay_reduce(2000);
	
	result = (int)((ADC * 500.0)/ 1023.0);//******�Ѳο���ѹ����ת�� ����Ϊ5v
	
	//hun = result / 100;
	
	//ten = result / 10 % 10;
	
	//one = result % 10;
	
	//back = ((hun * 100.0)+(ten * 10.0)+ one);
	
	return(result);
	
	
	
	
}

//***********************ADC�ĳ�ʼ��*****************//

void M16_ADC_INIT()
{
	//********ADC�ο���ѹѡ��
	
	ADMUX |= (1 << REFS0);//*******ѡ��AVCCΪ�ο���ѹ
	
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE) | (1 << ADPS2);//**********�����ж� 16��Ƶ 
	
	delay_reduce(100);//*****��ϵͳ�ȶ�
	
}


#endif /*LIB_ADC_H_ */