/*
 * lib_virtual_rgbled_bus.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */ 


#ifndef LIB_VIRTUAL_RGBLED_BUS_H_
#define LIB_VIRTUAL_RGBLED_BUS_H_
//*********************有延时 应包含延时程序
#ifndef LIB_DELAY_H_
# error "not define LIB_DELAY_H_ ; LIB_LED_H_ can not work"
#endif
//********************RGB LED初始化*************************************//
#define RGB_DDR DDRC
#define RGB_PORT PORTC
#define RGB_PIN PINC
#define RGB_CON_DDR DDRD
#define RGB_CON_PORT PORTD
#define RGB_CON_PIN PIND
#define red_port 0
#define green_port 1
#define blue_port 2
#define uchar unsigned char
#define uint unsigned int
uint red_value;
uint green_value;
uint blue_value;
uint red_value0;
uint green_value0;
uint blue_value0;
uint red_value1;
uint green_value1;
uint blue_value1;
uint red_value2;
uint green_value2;
uint blue_value2;
uint red_value3;
uint green_value3;
uint blue_value3;
uint red_value4;
uint green_value4;
uint blue_value4;
uint red_value5;
uint green_value5;
uint blue_value5;
uint red_value6;
uint green_value6;
uint blue_value6;
uint red_value7;
uint green_value7;
uint blue_value7;

uint FZ;//**************************分频
//*********************红色置位******************************//
void red_set_bit()
{
	RGB_PORT|=(1<<red_port);
}

//*********************绿色置位******************************//
void green_set_bit()
{
	RGB_PORT|=(1<<green_port);
}

//*********************蓝色置位******************************//
void blue_set_bit()
{
	RGB_PORT|=(1<<blue_port);
}

//*********************led选择置位******************************//
void rgbled_clr_bit(uchar led_num)
{
	RGB_CON_PORT|=(1<<led_num);
}
//********************红色清零*****************************//
void red_clr_bit()
{
	RGB_PORT&=~(1<<red_port);
}
//********************绿色清零*****************************//
void green_clr_bit()
{
	RGB_PORT&=~(1<<green_port);
}
//********************蓝色清零*****************************//
void blue_clr_bit()
{
	RGB_PORT&=~(1<<blue_port);
}

//********************led1选择清零*****************************//
void rgbled_set_bit(uchar led_num)
{
	RGB_CON_PORT&=~(1<<led_num);
}



//********************************************************************************************************************************//

//********************************************************************************************************************************//
//******************* RGB 显示初始化**********************************//
void RGB_SHOW_init()
{
	RGB_DDR |= (1<<red_port)|(1<<green_port)|(1<<blue_port);
	RGB_PORT |= (1<<red_port)|(1<<green_port)|(1<<blue_port);
	RGB_CON_DDR=0xff;
	RGB_CON_PORT=0xff;//端口初始化
	
	FZ=1;
}
//********************************************************************************************************************************//

//********************************************************************************************************************************//




//********************************************************************************************************************************//

//********************PWM增量式 8线总线方法 led片选的方法
//********************红绿蓝由总线控制 led的阳极由端口控制
//********************************************************************************************************************************//

void BUS8_RGBLED_SHOW(uchar red_valuer0,uchar green_valuer0,uchar blue_valuer0,uchar red_valuer1,uchar green_valuer1,uchar blue_valuer1,uchar red_valuer2,uchar green_valuer2,uchar blue_valuer2,uchar red_valuer3,uchar green_valuer3,uchar blue_valuer3,uchar red_valuer4,uchar green_valuer4,uchar blue_valuer4,uchar red_valuer5,uchar green_valuer5,uchar blue_valuer5,uchar red_valuer6,uchar green_valuer6,uchar blue_valuer6,uchar red_valuer7,uchar green_valuer7,uchar blue_valuer7)
{
	
	
	
	uint wait_time = 1;
	red_value0 = red_valuer0;
	green_value0 = green_valuer0;
	blue_value0 = blue_valuer0;
	red_value1 = red_valuer1;
	green_value1 = green_valuer1;
	blue_value1 = blue_valuer1;
	red_value2 = red_valuer2;
	green_value2 = green_valuer2;
	blue_value2 = blue_valuer2;
	red_value3 = red_valuer3;
	green_value3 = green_valuer3;
	blue_value3 = blue_valuer3;
	red_value4 = red_valuer4;
	green_value4 = green_valuer4;
	blue_value4 = blue_valuer4;
	red_value5 = red_valuer5;
	green_value5 = green_valuer5;
	blue_value5 = blue_valuer5;
	red_value6 = red_valuer6;
	green_value6 = green_valuer6;
	blue_value6 = blue_valuer6;
	red_value7 = red_valuer7;
	green_value7 = green_valuer7;
	blue_value7 = blue_valuer7;
	
	for(uint PWM_VIRTUAL_COUNT=1;PWM_VIRTUAL_COUNT<257;PWM_VIRTUAL_COUNT++)
	{
		    RGB_CON_PORT = 0Xff;
		
			//*****************red bus
		
			red_clr_bit();
			green_set_bit();
			blue_set_bit();
			if (red_value0>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(0);
			}
			else
			{
				rgbled_clr_bit(0);
			}
			
			
			if (red_value1>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(1);
			}
			else
			{
				rgbled_clr_bit(1);
		    }
			
			
		    if (red_value2>PWM_VIRTUAL_COUNT)
		    {
			rgbled_set_bit(2);
		    }
		   else
		   {
			rgbled_clr_bit(2);
	       }
		   
		   
	       if (red_value3>PWM_VIRTUAL_COUNT)
	       {
	 	    rgbled_set_bit(3);
	       }
	       else
	      {
		   rgbled_clr_bit(3);
          }
		  
		  
		  if (red_value4>PWM_VIRTUAL_COUNT)
         {
	      rgbled_set_bit(4);
          }
          else
          {
	      rgbled_clr_bit(4);
          }
		  
		  
		  if (red_value5>PWM_VIRTUAL_COUNT)
		 {
		  rgbled_set_bit(5);
		 }
		  else
		 {
		  rgbled_clr_bit(5);
		 }
		 
		 
		 if (red_value6>PWM_VIRTUAL_COUNT)
		{
			rgbled_set_bit(6);
		}
		else
		{
			rgbled_clr_bit(6);
	    }
		
		
		if (red_value7>PWM_VIRTUAL_COUNT)
	   {
		rgbled_set_bit(7);
	    }
	    else
	   {
		rgbled_clr_bit(7);
	    }
		delay_reduce(wait_time);
		RGB_CON_PORT = 0Xff;
		//*****************green bus
		
			green_clr_bit();
			red_set_bit();
			blue_set_bit();
			if (green_value0>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(0);
			}
			else
			{
				rgbled_clr_bit(0);
			}
			
			
			if (green_value1>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(1);
			}
			else
			{
				rgbled_clr_bit(1);
			}
			
			
			if (green_value2>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(2);
			}
			else
			{
				rgbled_clr_bit(2);
			}
			
			
			if (green_value3>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(3);
			}
			else
			{
				rgbled_clr_bit(3);
			}
			
			
			if (green_value4>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(4);
			}
			else
			{
				rgbled_clr_bit(4);
			}
			
			
			if (green_value5>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(5);
			}
			else
			{
				rgbled_clr_bit(5);
			}
			
			
			if (green_value6>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(6);
			}
			else
			{
				rgbled_clr_bit(6);
			}
			
			
			if (green_value7>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(7);
			}
			else
			{
				rgbled_clr_bit(7);
			}
		delay_reduce(wait_time);
		RGB_CON_PORT = 0Xff;
		//*****************blue bus
		
			blue_clr_bit();
			green_set_bit();
			red_set_bit();
			if (blue_value0>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(0);
			}
			else
			{
				rgbled_clr_bit(0);
			}
			
			
			if (blue_value1>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(1);
			}
			else
			{
				rgbled_clr_bit(1);
			}
			
			
			if (blue_value2>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(2);
			}
			else
			{
				rgbled_clr_bit(2);
			}
			
			
			if (blue_value3>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(3);
			}
			else
			{
				rgbled_clr_bit(3);
			}
			
			
			if (blue_value4>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(4);
			}
			else
			{
				rgbled_clr_bit(4);
			}
			
			
			if (blue_value5>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(5);
			}
			else
			{
				rgbled_clr_bit(5);
			}
			
			
			if (blue_value6>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(6);
			}
			else
			{
				rgbled_clr_bit(6);
			}
			
			
			if (blue_value7>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(7);
			}
			else
			{
				rgbled_clr_bit(7);
			}
			delay_reduce(wait_time);
			RGB_CON_PORT = 0Xff;
		  
		}
}

//*********************PWM增量式 8总线方式 指向目标颜色

void BUS8_RGBLED_CHANGE_TO(uchar red_aim_value0,uchar green_aim_value0,uchar blue_aim_value0,uchar red_aim_value1,uchar green_aim_value1,uchar blue_aim_value1,uchar red_aim_value2,uchar green_aim_value2,uchar blue_aim_value2,uchar red_aim_value3,uchar green_aim_value3,uchar blue_aim_value3,uchar red_aim_value4,uchar green_aim_value4,uchar blue_aim_value4,uchar red_aim_value5,uchar green_aim_value5,uchar blue_aim_value5,uchar red_aim_value6,uchar green_aim_value6,uchar blue_aim_value6,uchar red_aim_value7,uchar green_aim_value7,uchar blue_aim_value7)
{
	   
	   uchar change_value;
	   
	   for(change_value=257;change_value>0;change_value--)
	   {
	      BUS8_RGBLED_SHOW(red_value0,green_value0,blue_value0,red_value1,green_value1,blue_value1,red_value2,green_value2,blue_value2,red_value3,green_value3,blue_value3,red_value4,green_value4,blue_value4,red_value5,green_value5,blue_value5,red_value6,green_value6,blue_value6,red_value7,green_value7,blue_value7);
		   delay_reduce(20);
		   if (red_value0<red_aim_value0)
		   {
			   red_value0++;
		   }
		   else if (red_value0>red_aim_value0)
		   {
			   red_value0--;
		   }
		   if (green_value0<green_aim_value0)
		   {
			   green_value0++;
		   }
		   else if (green_value0>green_aim_value0)
		   {
			   green_value0--;
		   }
		   if (blue_value0<blue_aim_value0)
		   {
			   blue_value0++;
		   }
		   else if (blue_value0>blue_aim_value0)
		   {
			   blue_value0--;
		   }
		   
		   if (red_value1<red_aim_value1)
		   {
			   red_value1++;
		   }
		   else if (red_value1>red_aim_value1)
		   {
			   red_value1--;
		   }
		   if (green_value1<green_aim_value1)
		   {
			   green_value1++;
		   }
		   else if (green_value1>green_aim_value1)
		   {
			   green_value1--;
		   }
		   if (blue_value1<blue_aim_value1)
		   {
			   blue_value1++;
		   }
		   else if (blue_value1>blue_aim_value1)
		   {
			   blue_value1--;
		   }
		   
		   if (red_value2<red_aim_value2)
		   {
			   red_value2++;
		   }
		   else if (red_value2>red_aim_value2)
		   {
			   red_value2--;
		   }
		   if (green_value2<green_aim_value2)
		   {
			   green_value2++;
		   }
		   else if (green_value2>green_aim_value2)
		   {
			   green_value2--;
		   }
		   if (blue_value2<blue_aim_value2)
		   {
			   blue_value2++;
		   }
		   else if (blue_value2>blue_aim_value2)
		   {
			   blue_value2--;
		   }
		   
		   if (red_value3<red_aim_value3)
		   {
			   red_value3++;
		   }
		   else if (red_value3>red_aim_value3)
		   {
			   red_value3--;
		   }
		   if (green_value3<green_aim_value3)
		   {
			   green_value3++;
		   }
		   else if (green_value3>green_aim_value3)
		   {
			   green_value3--;
		   }
		   if (blue_value3<blue_aim_value3)
		   {
			   blue_value3++;
		   }
		   else if (blue_value3>blue_aim_value3)
		   {
			   blue_value3--;
		   }
		   BUS8_RGBLED_SHOW(red_value0,green_value0,blue_value0,red_value1,green_value1,blue_value1,red_value2,green_value2,blue_value2,red_value3,green_value3,blue_value3,red_value4,green_value4,blue_value4,red_value5,green_value5,blue_value5,red_value6,green_value6,blue_value6,red_value7,green_value7,blue_value7);
		   delay_reduce(20);
		   if (red_value4<red_aim_value4)
		   {
			   red_value4++;
		   }
		   else if (red_value4>red_aim_value4)
		   {
			   red_value4--;
		   }
		   if (green_value4<green_aim_value4)
		   {
			   green_value4++;
		   }
		   else if (green_value4>green_aim_value4)
		   {
			   green_value4--;
		   }
		   if (blue_value4<blue_aim_value4)
		   {
			   blue_value4++;
		   }
		   else if (blue_value4>blue_aim_value4)
		   {
			   blue_value4--;
		   }
		   
		   if (red_value5<red_aim_value5)
		   {
			   red_value5++;
		   }
		   else if (red_value5>red_aim_value5)
		   {
			   red_value5--;
		   }
		   if (green_value5<green_aim_value5)
		   {
			   green_value5++;
		   }
		   else if (green_value5>green_aim_value5)
		   {
			   green_value5--;
		   }
		   if (blue_value5<blue_aim_value5)
		   {
			   blue_value5++;
		   }
		   else if (blue_value5>blue_aim_value5)
		   {
			   blue_value5--;
		   }
		   
		   if (red_value6<red_aim_value6)
		   {
			   red_value6++;
		   }
		   else if (red_value6>red_aim_value6)
		   {
			   red_value6--;
		   }
		   if (green_value6<green_aim_value6)
		   {
			   green_value6++;
		   }
		   else if (green_value6>green_aim_value6)
		   {
			   green_value6--;
		   }
		   if (blue_value6<blue_aim_value6)
		   {
			   blue_value6++;
		   }
		   else if (blue_value6>blue_aim_value6)
		   {
			   blue_value6--;
		   }
		   
		   if (red_value7<red_aim_value7)
		   {
			   red_value7++;
		   }
		   else if (red_value7>red_aim_value7)
		   {
			   red_value7--;
		   }
		   if (green_value7<green_aim_value7)
		   {
			   green_value7++;
		   }
		   else if (green_value7>green_aim_value7)
		   {
			   green_value7--;
		   }
		   if (blue_value7<blue_aim_value7)
		   {
			   blue_value7++;
		   }
		   else if (blue_value7>blue_aim_value7)
		   {
			   blue_value7--;
		   }
		   
	   
	   }	
}
//********************************************************************************************************************************//
//**********************PWM增量式 RGBLED FLOW模式*******************//
void BUS8_RGBLED_FLOW()
{
	uchar red_flow_value0=0;
	uchar green_flow_value0=0;
	uchar blue_flow_value0=0;
	uchar red_flow_value1=0;
	uchar green_flow_value1=0;
	uchar blue_flow_value1=0;
	uchar red_flow_value2=0;
	uchar green_flow_value2=0;
	uchar blue_flow_value2=0;
	uchar red_flow_value3=0;
	uchar green_flow_value3=0;
	uchar blue_flow_value3=0;
	uchar red_flow_value4=0;
	uchar green_flow_value4=0;
	uchar blue_flow_value4=0;
	uchar red_flow_value5=0;
	uchar green_flow_value5=0;
	uchar blue_flow_value5=0;
	uchar red_flow_value6=0;
	uchar green_flow_value6=0;
	uchar blue_flow_value6=0;
	uchar red_flow_value7=0;
	uchar green_flow_value7=0;
	uchar blue_flow_value7=0;
	
	uchar flow_time=0;
	uint change_time=1;
	BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
		red_flow_value2++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
		red_flow_value2++;
		red_flow_value3++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
		red_flow_value2++;
		red_flow_value3++;
		red_flow_value4++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
		red_flow_value2++;
		red_flow_value3++;
		red_flow_value4++;
		red_flow_value5++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
		red_flow_value2++;
		red_flow_value3++;
		red_flow_value4++;
		red_flow_value5++;
		red_flow_value6++;
	}
	for (flow_time=0;flow_time<31;flow_time++)
	{
		
		BUS8_RGBLED_SHOW(red_flow_value0,green_flow_value0,blue_flow_value0,red_flow_value1,green_flow_value1,blue_flow_value1,red_flow_value2,green_flow_value2,blue_flow_value2,red_flow_value3,green_flow_value3,blue_flow_value3,red_flow_value4,green_flow_value4,blue_flow_value4,red_flow_value5,green_flow_value5,blue_flow_value5,red_flow_value6,green_flow_value6,blue_flow_value6,red_flow_value7,green_flow_value7,blue_flow_value7);
		
		red_flow_value0++;
		red_flow_value1++;
		red_flow_value2++;
		red_flow_value3++;
		red_flow_value4++;
		red_flow_value5++;
		red_flow_value6++;
		red_flow_value7++;
	}
}



//********************************************************************************************************************************//

//********************PWM增量式 8线总线方法 led片选的方法
//********************红绿蓝由总线控制 led的阳极由端口控制
//********************************************************************************************************************************//

void SIMPLE8_RGBLED_SHOW(uchar red_valuer0,uchar green_valuer0,uchar blue_valuer0,uchar red_valuer1,uchar green_valuer1,uchar blue_valuer1,uchar red_valuer2,uchar green_valuer2,uchar blue_valuer2,uchar red_valuer3,uchar green_valuer3,uchar blue_valuer3,uchar red_valuer4,uchar green_valuer4,uchar blue_valuer4,uchar red_valuer5,uchar green_valuer5,uchar blue_valuer5,uchar red_valuer6,uchar green_valuer6,uchar blue_valuer6,uchar red_valuer7,uchar green_valuer7,uchar blue_valuer7)
{
	
	uchar wait_time = 1;
	
	for(uint PWM_VIRTUAL_COUNT=1;PWM_VIRTUAL_COUNT<257;PWM_VIRTUAL_COUNT++)
	{
		    RGB_CON_PORT = 0Xff;
		
			//*****************red bus
		
			red_clr_bit();
			green_set_bit();
			blue_set_bit();
			if (red_valuer0>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(0);
			}
			else
			{
				rgbled_clr_bit(0);
			}
			
			
			if (red_valuer1>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(1);
			}
			else
			{
				rgbled_clr_bit(1);
		    }
			
			
		    if (red_valuer2>PWM_VIRTUAL_COUNT)
		    {
			rgbled_set_bit(2);
		    }
		   else
		   {
			rgbled_clr_bit(2);
	       }
		   
		   
	       if (red_valuer3>PWM_VIRTUAL_COUNT)
	       {
	 	    rgbled_set_bit(3);
	       }
	       else
	      {
		   rgbled_clr_bit(3);
          }
		  
		  
		  if (red_valuer4>PWM_VIRTUAL_COUNT)
         {
	      rgbled_set_bit(4);
          }
          else
          {
	      rgbled_clr_bit(4);
          }
		  
		  
		  if (red_valuer5>PWM_VIRTUAL_COUNT)
		 {
		  rgbled_set_bit(5);
		 }
		  else
		 {
		  rgbled_clr_bit(5);
		 }
		 
		 
		 if (red_valuer6>PWM_VIRTUAL_COUNT)
		{
			rgbled_set_bit(6);
		}
		else
		{
			rgbled_clr_bit(6);
	    }
		
		
		if (red_valuer7>PWM_VIRTUAL_COUNT)
	   {
		rgbled_set_bit(7);
	    }
	    else
	   {
		rgbled_clr_bit(7);
	    }
		delay_reduce(wait_time);
	    }
			
		for(uint PWM_VIRTUAL_COUNT=1;PWM_VIRTUAL_COUNT<257;PWM_VIRTUAL_COUNT++)
		{
			
		RGB_CON_PORT = 0Xff;
		//*****************green bus
		
			green_clr_bit();
			red_set_bit();
			blue_set_bit();
			if (green_valuer0>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(0);
			}
			else
			{
				rgbled_clr_bit(0);
			}
			
			
			if (green_valuer1>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(1);
			}
			else
			{
				rgbled_clr_bit(1);
			}
			
			
			if (green_valuer2>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(2);
			}
			else
			{
				rgbled_clr_bit(2);
			}
			
			
			if (green_valuer3>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(3);
			}
			else
			{
				rgbled_clr_bit(3);
			}
			
			
			if (green_valuer4>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(4);
			}
			else
			{
				rgbled_clr_bit(4);
			}
			
			
			if (green_valuer5>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(5);
			}
			else
			{
				rgbled_clr_bit(5);
			}
			
			
			if (green_valuer6>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(6);
			}
			else
			{
				rgbled_clr_bit(6);
			}
			
			
			if (green_valuer7>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(7);
			}
			else
			{
				rgbled_clr_bit(7);
			}
		delay_reduce(wait_time);
		}		
		
		
		for(uint PWM_VIRTUAL_COUNT=1;PWM_VIRTUAL_COUNT<257;PWM_VIRTUAL_COUNT++)
		{
			
		
		RGB_CON_PORT = 0Xff;
		//*****************blue bus
		
			blue_clr_bit();
			green_set_bit();
			red_set_bit();
			if (blue_valuer0>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(0);
			}
			else
			{
				rgbled_clr_bit(0);
			}
			
			
			if (blue_valuer1>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(1);
			}
			else
			{
				rgbled_clr_bit(1);
			}
			
			
			if (blue_valuer2>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(2);
			}
			else
			{
				rgbled_clr_bit(2);
			}
			
			
			if (blue_valuer3>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(3);
			}
			else
			{
				rgbled_clr_bit(3);
			}
			
			
			if (blue_valuer4>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(4);
			}
			else
			{
				rgbled_clr_bit(4);
			}
			
			
			if (blue_valuer5>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(5);
			}
			else
			{
				rgbled_clr_bit(5);
			}
			
			
			if (blue_valuer6>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(6);
			}
			else
			{
				rgbled_clr_bit(6);
			}
			
			
			if (blue_valuer7>PWM_VIRTUAL_COUNT)
			{
				rgbled_set_bit(7);
			}
			else
			{
				rgbled_clr_bit(7);
			}
			delay_reduce(wait_time);
			RGB_CON_PORT = 0Xff;
		}		  
		
}


		
//********************PWM增量式 总线方法 led片选的方法
//********************红绿蓝由总线控制 led的阳极由端口控制
//********************************************************************************************************************************//

void BUS8_PORT_SHOW(uchar red_valuer,uchar green_valuer,uchar blue_valuer)
{
	
	
	uint PWM_VIRTUAL_OCR1A=1;
	uint PWM_VIRTUAL_ICR1=255;
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	
	for(uint PWM_VIRTUAL_COUNT=0;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)
	{
		RGB_CON_PORT = 0XFF;
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		
			//*****************red bus
		
			red_clr_bit();
			green_set_bit();
			blue_set_bit();
			if (red_value>PWM_VIRTUAL_OCR1A)
			{
				RGB_CON_PORT = 0X00;
			}
			else
			{
				RGB_CON_PORT = 0XFF;
			}
			
		
		RGB_CON_PORT = 0XFF;
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		//*****************green bus
		
			green_clr_bit();
			red_set_bit();
			blue_set_bit();
			if (green_value>PWM_VIRTUAL_OCR1A)
			{
				RGB_CON_PORT = 0X00;
			}
			else
			{
				RGB_CON_PORT = 0XFF;
			}
		
		RGB_CON_PORT = 0XFF;
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		//*****************blue bus
		
			blue_clr_bit();
			green_set_bit();
			red_set_bit();
			if (blue_value>PWM_VIRTUAL_OCR1A)
			{
				RGB_CON_PORT = 0X00;
			}
			else
			{
				RGB_CON_PORT = 0XFF;
			}
			
		    PWM_VIRTUAL_OCR1A++;
		
		
		
		}
}
//**********************PWM增量式 RGBLED FLOW模式*******************//
void BUS8_PORT_FLOW()
{
	uchar red_flow_value=255;
	uchar green_flow_value=0;
	uchar blue_flow_value=0;
	uchar flow_time=0;
	uint change_time=3000;
	BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value++;
	}
	BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		red_flow_value--;
	}
	BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		blue_flow_value++;
	}
	BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		green_flow_value--;
	}
	BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		red_flow_value++;
	}
	BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
	delay_reduce(change_time);
	for (flow_time=0;flow_time<255;flow_time++)
	{
		
		BUS8_PORT_SHOW(red_flow_value,green_flow_value,blue_flow_value);
		delay_reduce(change_time);
		blue_flow_value--;
	}
}
	
//*********************PWM增量式 总线方式 指向目标颜色

void BUS8_PORT_CHANGE_TO(uchar red_aim_value,uchar green_aim_value,uchar blue_aim_value)
{
	   uint change_time=500;
	   uchar change_value;
	   
	   for(change_value=255;change_value>0;change_value--)
	   {
	      BUS8_PORT_SHOW(red_value,green_value,blue_value);
		   if (red_value<red_aim_value)
		   {
			   red_value++;
		   }
		   else if (red_value>red_aim_value)
		   {
			   red_value--;
		   }
		   if (green_value<green_aim_value)
		   {
			   green_value++;
		   }
		   else if (green_value>green_aim_value)
		   {
			   green_value--;
		   }
		   if (blue_value<blue_aim_value)
		   {
			   blue_value++;
		   }
		   else if (blue_value>blue_aim_value)
		   {
			   blue_value--;
		   }
	   delay_reduce(change_time);
	   }	
}
//********************************************************************************************************************************//

//********************************************************************************************************************************//
//********************************************************************************************************************************//

//********************PWM增量式 总线方法 led片选的方法
//********************红绿蓝由总线控制 led的阳极由端口控制
//********************************************************************************************************************************//

void BUS8_TEST(uchar red_valuer,uchar green_valuer,uchar blue_valuer,uchar led_num)
{
	
	
	uint PWM_VIRTUAL_OCR1A=1;
	uint PWM_VIRTUAL_ICR1=255;
	red_value=red_valuer;
	green_value=green_valuer;
	blue_value=blue_valuer;
	
	for(uint PWM_VIRTUAL_COUNT=0;PWM_VIRTUAL_COUNT<PWM_VIRTUAL_ICR1;PWM_VIRTUAL_COUNT++)
	{
		RGB_CON_PORT = 0XFF;
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		
			//*****************red bus
		
			red_clr_bit();
			green_set_bit();
			blue_set_bit();
			if (red_value>PWM_VIRTUAL_OCR1A)
			{
				RGB_CON_PORT = 0X00;
			}
			else
			{
				RGB_CON_PORT = 0XFF;
			}
			
		
		RGB_CON_PORT = 0XFF;
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		//*****************green bus
		
			green_clr_bit();
			red_set_bit();
			blue_set_bit();
			if (green_value>PWM_VIRTUAL_OCR1A)
			{
				RGB_CON_PORT = 0X00;
			}
			else
			{
				RGB_CON_PORT = 0XFF;
			}
		
		RGB_CON_PORT = 0XFF;
		red_set_bit();
		green_clr_bit();
		blue_clr_bit();
		//*****************blue bus
		
			blue_clr_bit();
			green_set_bit();
			red_set_bit();
			if (blue_value>PWM_VIRTUAL_OCR1A)
			{
				RGB_CON_PORT = 0X00;
			}
			else
			{
				RGB_CON_PORT = 0XFF;
			}
			
		    PWM_VIRTUAL_OCR1A++;
		
		
		
		}
}
		
void BUS8_FLOWER_TEST()
{
	uchar red_bus = 0;
	uchar green_bus = 0;
	uchar blue_bus = 0;
	
	for (uchar time = 0;time < 255;time++)
	{
		BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    BUS8_RGBLED_SHOW(red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus,red_bus,green_bus,blue_bus);
	    
		red_bus ++;
	
	}
}
#endif /* LIB_VIRTUAL_RGBLED_BUS_H_ */