#include "matrix.h"

inline void    led_init(void)
{
	u8 i;
	for (i = 0; i < 100; i++)
	{
		asm("nop");
	}
	for (i = 0; i < 175; i++)
	{
		color(0, 1);//off(1);
	}
	for (i = 0; i < 150; i++)
	{
		color(0,2);//off(2);
	}
	for (i = 0; i < 100; i++)
	{
		asm("nop");
	}
}
