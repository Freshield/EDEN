/*
 * lib_IR_m16.h
 *
 * Created: 2015/10/02 11:41:48
 * Edited：	2015/11/12
 *  Author: Narcissus
 */ 

//----------------------------------------HEADER---------------------------------------//

//***注意芯片的熔丝位设置，新片的熔丝位为内部时钟
//***注意触发类别是下降沿还是上升沿 否则可能会导致丢失一个脉冲

#ifndef LIB_IR_M16_H_
#define LIB_IR_M16_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif
//最下边是receiver的程序
/*
 *M16的IR_sender程序
 *用timer1发出38khz的波
 *TIMER1的pwm
 *定义输出口 M16的TIMER0的输出口为OC0（PB3）
 */

#define IR_sender_PORT PORTB
#define IR_sender_DDR DDRB
#define IR_sender_PIN PINB
#define IR_sender_OUT PB3

int FN_IR = 1;//*****分频大小

//-------------------------------------------IMPLEMENTATION-----------------------------//

/*
 *IR_sender模式初始化
 *使用timer1的fastpwm icr1作为top值的模式
 */

void IR_sender_init()
{
	//端口初始化
	IR_sender_DDR |= (1<<IR_sender_OUT);  IR_sender_PORT &= ~(1 << IR_sender_OUT);//要把想相应的端口设为输出并值为零
	TCNT0 = 0x00;//计数器初始化
	TIMSK |= (1<<OCIE0)|(1<<TOIE0);//中断初始化
	//快速PWM模式设置
	//TCCR1A |= (1<<COM1A1)|(1<<WGM11);//比较匹配清零 TOP置位
	//TCCR1A |= (1<<COM1A1)| (1<<COM1A0)|(1<<WGM11);//比较匹配置位 TOP清零 使用这个模式 可以通过OCR1A的变化来修改频率 不用时候设为和OCR1A一样 则数值为零
	//TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10);FN_IR = 1;//PWM模式14 TOP为ICR1的值 1分频
	//TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS12);FN_IR = 256;//PWM模式14 TOP为ICR1的值 256分频
	TCCR0 |= (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << COM00) | (1 << CS00);FN_IR = 1;
	//设置为快速PWM；与OCR0匹配时置位 TOP清零；1分频
	
	
}

/*
 *IR sender模式频率设定,单位为频率
 //公式为 ICR1 = (F_CPU / 38000) - 1; OCR1 = DUTY * ICR1; 为了减轻cpu压力这里直接算好
 //若38000hz 1分频 F_CPU为7372800 DUTY为0.6 ICR1 = 193 ; OCR1 = 116 ;
 //若38000hz 1分频 F_CPU为7372800 DUTY为0.52 ICR1 = 193 ; OCR1 = 100 ;
 //若1000hz  1分频 F_CPU为7372800 DUTY为0.5 ICR1 = 7372 ; OCR1 = 3686 ;
 *此为OC0的模式下
 *fz = F_CPU / (256 - TCNT0);OCR0 = DUTY * (256 - TCNT0) + TCNT0为了减轻CPU压力 这里最好直接算好
 *若38000hz 1分频 F_CPU为7372800 DUTY为0.5 TCNT0 = 81; OCR0 = 149;OCR0设为255则不工作
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
 *M16的IR_receiver程序
 *用timer1捕获38khz的波
 *TIMER1的pwm
 *定义输出口 M16的TIMER1的输入口为ICP1(PD6)
 */

#define IR_receiver_PORT PORTD
#define IR_receiver_DDR DDRD
#define IR_receiver_PIN PIND
#define IR_receiver_OUT PD6

//int FN_IR = 1;//*****分频大小
void IR_receiver_init(uchar edge);//edge = 1 means up model and = 0 means down edge model
//设置为上升沿捕获
void IR_receiver_model_up();
//设置为下降沿捕获
void IR_receiver_model_down();
uchar IR_receiver_model_change(uchar model);//model == 1 is model up and == 0 is model down
//to use this function it's better to take model = IR_receiver_model_change(model);so that model can get the return value

//-------------------------------------------IMPLEMENTATION-----------------------------//

/*
 *IR_receiver模式初始化
 *使用timer1的icr1捕获
 */

void IR_receiver_init(uchar edge)//edge = 1 means up model and = 0 means down edge model
{
	IR_receiver_DDR &= ~(1<<IR_receiver_OUT);  IR_sender_PORT |= (1 << IR_sender_OUT);//相应端口设为接收并且置为高电平
	TIMSK |= (1<<TICIE1);//中断初始化
	TCCR1B |= (1<<ICNC1)|(1<<CS12);FN_IR = 256;//噪声抑制 下降沿触发 256分频
	TCNT1 = 0x00;//计数器初始化
	if (edge == 0)
	{
		IR_receiver_model_down();
	}
	else
	{
		IR_receiver_model_up();
	}
}
//设置为上升沿捕获
void IR_receiver_model_up()
{
	TCCR1B |= (1<<ICES1);
	TIFR |= (1<<ICF1);
}
//设置为下降沿捕获
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
 *IR_receiver获得时间的部分
 *当F_CPU为7372800 分频256时
 *每28.8次TCNT1增加为1ms
 *要使用一起拷到主程序中
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