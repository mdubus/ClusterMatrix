/* 
 * File:   colors.c
 * Author: bocal
 *
 * Created on June 28, 2017, 4:11 PM
 */

#include "matrix.h"

static inline void one(u8 where)
{
	if (where == 1)
	{
		TRISBbits.TRISB10 = 1;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		TRISBbits.TRISB10 = 0;
		asm("nop");
	}
	else
	{
		TRISBbits.TRISB9 = 1;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		TRISBbits.TRISB9 = 0;
		asm("nop");
	}
}

static inline void zero(u8 where)
{
	if (where == 1)
	{
		TRISBbits.TRISB10 = 1;
		asm("nop");
		TRISBbits.TRISB10 = 0;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
	else
	{
		TRISBbits.TRISB9 = 1;
		asm("nop");
		TRISBbits.TRISB9 = 0;
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
	}
}

void color(u32 color, u8 where)
{
	u8 i;
	for (i = 0; i < 24; i++)
	{
		if ((color & (1 << (23 - i))) != 0)
			one(where);
		else
			zero(where);
	}
}
