/*
 * lib_basic.h
 *
 * Created: 2015/12/17 21:07:33
 * Edited£º	2015/12/17 
 *  Author: FRESHIELD
 */ 

//***Í·ÎÄ¼þ
#ifndef LIB_BASIC_H_
#define LIB_BASIC_H_

#define uchar unsigned char

//***IMPLEMENT

char BASIC_hun;
char BASIC_ten;
char BASIC_poi;

void BASIC_HexToDciAsWord(char num)//here use char
{
	BASIC_hun = num/100;
	BASIC_hun = BASIC_hun + '0';
	BASIC_ten = num%100/10;
	BASIC_ten = BASIC_ten + '0';
	BASIC_poi = num%10;
	BASIC_poi = BASIC_poi + '0';
}

#endif /* LIB_BASIC_H_ */