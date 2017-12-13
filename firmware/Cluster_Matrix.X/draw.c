#include "matrix.h"


static inline void    draw_one(u8 where, u8 place) {
	if (place == YELLOW) {
		color(0x050f00, where);
	} else if (place == BLUE) {
		color(0x000020, where);
	} else if (place == RED) {
		color(0x000f00, where);
	} else if (place == TEMOIN){
		if (time < 240) //5 min sans com uart
			color(0x0f0000, where);//green
		else
			color(0x030f00, where);//orange
	} else if (place == LBLUE) {
		color(0x000007, where);
	} else if (place == LLBLUE) {
		color(0x000003, where);
	} else {
		color(0, where);//off
	}
}

static inline void     draw_line(u8 row, u8 where, u8 i) {
	u8 place = 0;
	if (gol_on == 0) {
		if (((mask_exist[current_cluster][row] >> (31 - i)) & 1) == 1) {
			if (((cluster_data[current_cluster][row] >> (31 - i)) & 1) == 1) {
				if (((conseil[row] >> (31 - i)) & 1) == 1) {
					place = BLUE;
				} else {
					place = YELLOW;
				}
			} else {
				place = RED;
			}
		} else {
			if (led_temoin_x == i && led_temoin_y == row){
				place = TEMOIN;
				led_previous_x = i;
				led_previous_y = row;
			} else if (led_temoin_x2 == i && led_temoin_y2 == row){
				place = TEMOIN;
				led_previous_x2 = i;
				led_previous_y2 = row;
			} else {
				place = 0; //OFF
			}
		}
	} else {
		if (((gameoflife[GOL_CURRENT][row] >> (31 - i)) & 1) == 1) {
			if (((gameoflife[GOL_NEXT][row] >> (31 - i)) & 1) == 1) {
				place = LBLUE;
			} else {
				place = LLBLUE;
			}
		} else {
			if (((gameoflife[GOL_NEXT][row] >> (31 - i)) & 1) == 1) {
				place = BLUE;
			} else {
				place = 0;
			}
		}
	}

	draw_one(where, place);
}

static inline void    draw_even(u8 row, u8 where) {
	u8 i;
	for (i = 0; i < 25; i++) {
		draw_line(row, where, i);
	}
}

static inline void    draw_odd(u8 row, u8 where) {
	u8 i;
	u8 j;

	for (j = 0; j < 25; j++) {
		i = 24 - j;
		draw_line(row, where, i);
	}
}

static inline void    draw_top_and_bot()
{
	u8 i = 0;
	for (i = 0; i < 7; i++) {
		if (i % 2 == 0) {
			draw_even(i, LOW_LEDS);
		} else {
			draw_odd(i, LOW_LEDS);
		}
	}
	for (i = 7; i < 13; i++) {
		if (i % 2 == 1) {
			draw_even(i, HIGH_LEDS);
		} else {
			draw_odd(i, HIGH_LEDS);
		}
	}
}

void    draw_cluster() {
	u8 i;

	__builtin_disable_interrupts();

	draw_top_and_bot();
	for (i = 0; i < 100; i++)
		asm("nop");

	__builtin_enable_interrupts();
}
