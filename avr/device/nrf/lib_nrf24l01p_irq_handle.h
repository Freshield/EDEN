/*
 * lib_nrf24l01p_irq_handle.h
 *
 * Created: 2013/04/07 11:41:48
 *  Author: Narcissus
 */


#ifndef LIB_NRF24L01P_IRQ_HANDLE_H_
#define LIB_NRF24L01P_IRQ_HANDLE_H_

extern void nrf24l01p_buffer_read(char nrf24l01p_reg_addr,char* buffer,char num);
extern void nrf24l01p_buffer_write(char nrf24l01p_reg_addr,char* buffer,char num);

extern void LCD_SHOW_STRING(uchar x,uchar y,char *str);

//#define M16
#define M128

#ifdef M128
extern char test_send_data[32];


#endif



#ifdef M16

extern char test_send_data[2];
extern uchar spi1_rw(uchar send_data1);
extern uchar MEDIUM_NUM;  

#endif

/*
本头文件内为自定义中断处理函数,外围框架代码自动清除中断和fifo
因此,这里的函数只需要编写想做的事情的代码就可以
如果需要其他变量或者函数请加上extern然后引用即可

/*
本头文件内为自定义中断处理函数,外围框架代码自动清除中断和fifo
因此,这里的函数只需要编写想做的事情的代码就可以
如果需要其他变量或者函数请加上extern然后引用即可

示例代码框架

void nrf24l01p_irq_tx_ds_handle()
{
	
}

void nrf24l01p_irq_rx_dr_handle()
{
	
}

void nrf24l01p_irq_max_rt_handle()
{
	
}

*/

void nrf24l01p_irq_tx_ds_handle()
{
	
	LCD_SHOW_STRING(0,0,"***TRANSLATION**");
	delay_reduce(60000);
	delay_reduce(60000);
	delay_reduce(60000);
	delay_reduce(60000);
	delay_reduce(60000);
	LCD_SHOW_STRING(0,0,"**COLOR--VALUE**"); 
}

void nrf24l01p_irq_rx_dr_handle()
{
	
	#ifdef M16
	nrf24l01p_buffer_read(R_RX_PAYLOAD,test_send_data,2);
	MEDIUM_NUM = test_send_data[1];
	switch(MEDIUM_NUM)
	{
		case 0:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"*****BLACK******");
		spi1_rw(0);
		break;
		
		case 1:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******RED*******");
		spi1_rw(1);
		break;
		
		case 2:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******ORGANGE***");
		spi1_rw(2);
		break;
		
		case 3:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******PINK******");
		spi1_rw(3);
		break;
		
		case 4:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******CYAN******");
		spi1_rw(4);
		break;
		
		case 5:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******GREEN*****");
		spi1_rw(5);
		break;
		
		case 6:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******GRASS*****");
		spi1_rw(6);
		break;
		
		case 7:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"*****MATCHA*****");
		spi1_rw(7);
		break;
		
		case 8:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******MINT******");
		spi1_rw(8);
		break;
		
		case 9:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"******BLUE******");
		spi1_rw(9);
		break;
		
		case 10:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"*****PURPLE*****");
		spi1_rw(10);
		break;
		
		case 11:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"*****ROYAL******");
		spi1_rw(11);
		break;
		
		case 12:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"*****OCEAN******");
		spi1_rw(12);
		break;
		
		case 13:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"****SAPHIRE*****");
		spi1_rw(13);
		break;
		
		case 14:
		LCD_SHOW_STRING(0,0,"******CHANGING***");
		LCD_SHOW_STRING(0,1,"*****AZURE******");
		spi1_rw(14);
		break;
		
		case 15:
		LCD_SHOW_STRING(0,0,"******FLOWING****");
		LCD_SHOW_STRING(0,1,"******FLOWING****");
		spi1_rw(15);
		break;
	}
	#endif
}

void nrf24l01p_irq_max_rt_handle()
{
	
	LCD_SHOW_STRING(0,1,"****FUCK MAX****");
}
#endif /* LIB_NRF24L01P_IRQ_HANDLE_H_ */