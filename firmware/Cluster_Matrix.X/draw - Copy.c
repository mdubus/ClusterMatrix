#include "matrix.h"

u8 bit_sum(u8 line, u8 size) {
	u8 i = 0;
	u8 result = 0;
	while (i < size) {
		if (((line << i) & 1) == 1)
			result++;
		i++;
	}
	return result;
}

void create_mask_side_by_side()
{
	u8 k = 0;
	u8 j = 0;
	u8 i = 0;
	for (k = 0; k < 3; k++) {
		for (j = 0; j < 13; j++) {
			side_by_side[k][j] = 0;
		}
	}
	for (k = 0; k < 3; k++) {
		for (j = 0; j < 13; j++) {
			for (i = 0; i < 25; i++) {
				if (((cluster_data[k][j] >> (31 - i)) & 1) == 1) {
					nb_voisins = 0;
					nb_voisins += bit_sum(((cluster_data[k][j] >> (29 - i)) & 31), 5);
					if (i % 2 == 0 && j < 12) {
						nb_voisins += bit_sum(((cluster_data[k][j + 1] >> (30 - i)) & 7), 3);
					} else if (i % 2 == 1 && j > 0) {
						nb_voisins += bit_sum(((cluster_data[k][j - 1] >> (30 - i)) & 7), 3);
					}
					if (nb_voisins >= nb_cote_a_cote)
						side_by_side[k][j] += 1 << (31 - i);
				}
			}
		}
	}

void    draw_one(u8 where) {
	if (place == 3) {
		yellow(where);
	} else if (place == 2) {
		blue(where);
	} else if (place == 1) {
		red(where);
	} else if (place == 4){
		if (time < 200) //5 min sans com uart
			green(where);
		else
			orange(where);
	} else
	{
		off(where);
	}
}

static void    draw_even(u32 row, u8 where) {
	u8 i;
	for (i = 0; i < 25; i++) {
		if (((mask_exist[current_cluster][row] >> (31 - i)) & 1) == 1) {
			if (((cluster_data[current_cluster][row] >> (31 - i)) & 1) == 1) {
				if (((side_by_side[current_cluster][row] >> (31 - i)) & 1) == 1) {
					place = 2; //BLEU
				} else {
					place = 3; //YELLOW
				}
			} else {
				place = 1; //RED
			}
		} else {
			if (led_temoin_x == i && led_temoin_y == row){
				place = 4;
				led_previous_x = i;
				led_previous_y = row;
			} else {
				place = 0; //OFF
			}
		}
		draw_one(where);
	}
}

static void    draw_odd(u32 row, u8 where) {
	u8 i;
	u8 j;

	for (j = 0; j < 25; j++) {
		i = 24 - j;
		if (((mask_exist[current_cluster][row] >> (31 - i)) & 1) == 1) {
			if (((cluster_data[current_cluster][row] >> (31 - i)) & 1) == 1) {
				if (((side_by_side[current_cluster][row] >> (31 - i)) & 1) == 1) {
					place = 2; //BLEU
				} else {
					place = 3; //YELLOW
				}
			} else {
				place = 1; //RED
			}
		} else {
			if (led_temoin_x == i && led_temoin_y == row){
				place = 4;
				led_previous_x = i;
				led_previous_y = row;
			} else {
				place = 0; //OFF
			}
		}
		draw_one(where);
	}
}

void    draw_top_and_bot()
{
	u8 i = 0;
	for (i = 0; i < 7; i++) {
		if (i%2 == 0) {
			draw_even(i, LOW_LEDS);
		} else {
			draw_odd(i, LOW_LEDS);
		}
	}
	for (i = 7; i < 13; i++) {
		if (i%2 == 1) {
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
