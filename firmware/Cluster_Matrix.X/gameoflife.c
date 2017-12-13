#include "matrix.h"

void init_GOL() {
	u8 i;

	gol_on = 1;
	gol_delay = 0;
	gol_count = 0;
	T3CONbits.TCKPS = 6;
	for (i = 0; i < 13; i++) {
		gameoflife[GOL_CURRENT][i] = cluster_data[current_cluster][i];
	}
}

u8 count_voisins(u8 i, u8 j) {
	u8 voisins = 0;
	if (i == 0) {
		voisins += bit_sum((gameoflife[GOL_CURRENT][j] & 0b01000000000000000000000010000000), 32)
			+ bit_sum((gameoflife[GOL_CURRENT][(j + 1) % 13] & 0b11000000000000000000000010000000), 32)
			+ bit_sum((gameoflife[GOL_CURRENT][(j + 12) % 13] & 0b11000000000000000000000010000000), 32);
	} else if (i == 24) {
		voisins += bit_sum((gameoflife[GOL_CURRENT][j] & 0b10000000000000000000000100000000), 32)
			+ bit_sum((gameoflife[GOL_CURRENT][(j + 1) % 13] & 0b10000000000000000000000110000000), 32)
			+ bit_sum((gameoflife[GOL_CURRENT][(j + 12) % 13] & 0b10000000000000000000000110000000), 32);
	} else {
		voisins += bit_sum(((gameoflife[GOL_CURRENT][j] >> (30 - i)) & 0b101), 3)
			+ bit_sum(((gameoflife[GOL_CURRENT][(j + 1) % 13] >> (30 - i)) & 0b111), 3)
			+ bit_sum(((gameoflife[GOL_CURRENT][(j + 12) % 13] >> (30 - i)) & 0b111), 3);
	}
	return voisins;
}

void update_GOL() {
	u8 i;
	u8 j;
	u8 voisins = 0;
	for (i = 0; i < 13; i++) {
		gameoflife[GOL_NEXT][i] = 0;
	}
	for (j = 0; j < 13; j++) {
		for (i = 0; i < 25; i++) {
			voisins = count_voisins(i, j);
			if (((gameoflife[GOL_CURRENT][j] >> (31 - i)) & 1) == 1) {
				if (voisins == 2 || voisins == 3) {
					gameoflife[GOL_NEXT][j] |= (1 << (31 - i));
				}
			} else {
				if (voisins == 3) {
					gameoflife[GOL_NEXT][j] |= (1 << (31 - i));
				}
			}
		}
	}
	draw_cluster();
	for (i = 0; i < 13; i++) {
		gameoflife[GOL_CURRENT][i] = gameoflife[GOL_NEXT][i];
	}
}

