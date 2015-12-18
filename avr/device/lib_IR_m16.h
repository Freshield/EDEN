/*
 * lib_IR_m16.h
 *
 * Created: 2015/10/02 11:41:48
 * Edited��	2015/11/12
 *  Author: Narcissus
 */ 

//----------------------------------------HEADER---------------------------------------//

//***ע��оƬ����˿λ���ã���Ƭ����˿λΪ�ڲ�ʱ��
//***ע�ⴥ��������½��ػ��������� ������ܻᵼ�¶�ʧһ������

#ifndef LIB_IR_M16_H_
#define LIB_IR_M16_H_
//*********************����ʱ Ӧ������ʱ����
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif
//���±���receiver�ĳ���
/*
 *M16��IR_sender����
 *��timer1����38khz�Ĳ�
 *TIMER1��pwm
 *��������� M16��TIMER0�������ΪOC0��PB3��
 */

#define IR_sender_PORT PORTB
#define IR_sender_DDR DDRB
#define IR_sender_PIN PINB
#define IR_sender_OUT PB3

int FN_IR = 1;//*****��Ƶ��С

//-------------------------------------------IMPLEMENTATION-----------------------------//

/*
 *IR_senderģʽ��ʼ��
 *ʹ��timer1��fastpwm icr1��Ϊtopֵ��ģʽ
 */

void IR_sender_init()
{
	//�˿ڳ�ʼ��
	IR_sender_DDR |= (1<<IR_sender_OUT);  IR_sender_PORT &= ~(1 << IR_sender_OUT);//Ҫ������Ӧ�Ķ˿���Ϊ�����ֵΪ��
	TCNT0 = 0x00;//��������ʼ��
	TIMSK |= (1<<OCIE0)|(1<<TOIE0);//�жϳ�ʼ��
	//����PWMģʽ����
	//TCCR1A |= (1<<COM1A1)|(1<<WGM11);//�Ƚ�ƥ������ TOP��λ
	//TCCR1A |= (1<<COM1A1)| (1<<COM1A0)|(1<<WGM11);//�Ƚ�ƥ����λ TOP���� ʹ�����ģʽ ����ͨ��OCR1A�ı仯���޸�Ƶ�� ����ʱ����Ϊ��OCR1Aһ�� ����ֵΪ��
	//TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);FN_IR = 1;//PWMģʽ14 TOPΪICR1��ֵ 1��Ƶ
	//TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS12);FN_IR = 256;//PWMģʽ14 TOPΪICR1��ֵ 256��Ƶ
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << COM00) | (1 << CS00);FN_IR = 1;
	//����Ϊ����PWM����OCR0ƥ��ʱ��λ TOP���㣻1��Ƶ
	
	
}

/*
 *IR senderģʽƵ���趨,��λΪƵ��
 //��ʽΪ ICR1 = (F_CPU / 38000) - 1; OCR1 = DUTY * ICR1; Ϊ�˼���cpuѹ������ֱ�����
 //��38000hz 1��Ƶ F_CPUΪ7372800 DUTYΪ0.6 ICR1 = 193 ; OCR1 = 116 ;
 //��38000hz 1��Ƶ F_CPUΪ7372800 DUTYΪ0.52 ICR1 = 193 ; OCR1 = 100 ;
 //��1000hz  1��Ƶ F_CPUΪ7372800 DUTYΪ0.5 ICR1 = 7372 ; OCR1 = 3686 ;
 *��ΪOC0��ģʽ��
 *fz = F_CPU / (256 - TCNT0);OCR0 = DUTY * (256 - TCNT0) + TCNT0Ϊ�˼���CPUѹ�� �������ֱ�����
 *��38000hz 1��Ƶ F_CPUΪ7372800 DUTYΪ0.5 TCNT0 = 81; OCR0 = 149;OCR0��Ϊ255�򲻹���
 */

void IR_sender_fz_set(int bottom,int top)
{
	
	TCNT0 = bottom;
	
	OCR0 = top;
}


void IR_sender_service()
{
	TCNT0 = 81;
}

void IR_sender_zero()
{
	OCR0 = 255;
}

void IR_sender_work()
{
	OCR0 = 149;
}
void IR_sender_open()
{
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << COM00) | (1 << CS00);FN_IR = 1;
}
void IR_sender_close()
{
	TCCR0 = 0X00;
}
//---------------------------------------------------------------------------------------------------------//
/*
 *M16��IR_receiver����
 *��timer1����38khz�Ĳ�
 *TIMER1��pwm
 *��������� M16��TIMER1�������ΪICP1(PD6)
 */

#define IR_receiver_PORT PORTD
#define IR_receiver_DDR DDRD
#define IR_receiver_PIN PIND
#define IR_receiver_OUT PD6

//int FN_IR = 1;//*****��Ƶ��С
void IR_receiver_init(uchar edge);//edge = 1 means up model and = 0 means down edge model
//����Ϊ�����ز���
void IR_receiver_model_up();
//����Ϊ�½��ز���
void IR_receiver_model_down();
uchar IR_receiver_model_change(uchar model);//model == 1 is model up and == 0 is model down
//to use this function it's better to take model = IR_receiver_model_change(model);so that model can get the return value

//-------------------------------------------IMPLEMENTATION-----------------------------//

/*
 *IR_receiverģʽ��ʼ��
 *ʹ��timer1��icr1����
 */

void IR_receiver_init(uchar edge)//edge = 1 means up model and = 0 means down edge model
{
	IR_receiver_DDR &= ~(1<<IR_receiver_OUT);  IR_sender_PORT |= (1 << IR_sender_OUT);//��Ӧ�˿���Ϊ���ղ�����Ϊ�ߵ�ƽ
	TIMSK |= (1<<TICIE1);//�жϳ�ʼ��
	TCCR1B |= (1<<ICNC1)|(1<<CS12);FN_IR = 256;//�������� �½��ش��� 256��Ƶ
	TCNT1 = 0x00;//��������ʼ��
	if (edge == 0)
	{
		IR_receiver_model_down();
	}
	else
	{
		IR_receiver_model_up();
	}
}
//����Ϊ�����ز���
void IR_receiver_model_up()
{
	TCCR1B |= (1<<ICES1);
	TIFR |= (1<<ICF1);
}
//����Ϊ�½��ز���
void IR_receiver_model_down()
{
	TCCR1B &= ~(1<<ICES1);
	TIFR |= (1<<ICF1);
}

uchar IR_receiver_model_change(uchar model)//model == 1 is model up and == 0 is model down
//to use this function it's better to take model = IR_receiver_model_change(model);so that model can get the return value
{
	if (model == 0)
	{
		
		
		IR_receiver_model_up();
		
		return 1;
	}
	else
	{
		
		IR_receiver_model_down();
		
		return 0;
	}
	
}

/*
 *IR_receiver���ʱ��Ĳ���
 *��F_CPUΪ7372800 ��Ƶ256ʱ
 *ÿ28.8��TCNT1����Ϊ1ms
 *Ҫʹ��һ�𿽵���������
 */
/*
unsigned int old_num = 0;
unsigned int new_num,change_num;

void IR_receiver_catch()
{
	new_num = ICR1;
	change_num = new_num - old_num;
	old_num = new_num;
}
*/









#endif /* LIB_IR_M16_H_ */