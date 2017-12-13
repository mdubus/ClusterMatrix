#include "matrix.h"

u8 bit_sum(u32 line, u8 size) {
	u8 i = 0;
	u8 result = 0;
	while (i < size) {
		if (((line >> i) & 1) == 1)
			result++;
		i++;
	}
	return result;
}

void create_mask_side_by_side()
{
	u8 j = 0;
	u8 i = 0;
	for (j = 0; j < 13; j++) {
		side_by_side[j] = 0;
	}
	for (j = 0; j < 13; j++) {
		for (i = 0; i < 25; i++) {
			if ((((cluster_data[current_cluster][j] >> (31 - i)) & 1) == 1) && ((mask_exist[current_cluster][j] >> (31 - i)) & 1 == 1)) {
				nb_voisins = 0;
				nb_voisins += bit_sum(((cluster_data[current_cluster][j] >> (29 - i)) & 0b11011), 5);
				if (i % 2 == 1 && j < 12) {
					nb_voisins += bit_sum(((cluster_data[current_cluster][j + 1] >> (30 - i)) & 0b101), 3);
				} else if (i % 2 == 0 && j > 0) {
					nb_voisins += bit_sum(((cluster_data[current_cluster][j - 1] >> (30 - i)) & 0b101), 3);
				}
				if (nb_voisins >= nb_cote_a_cote)
					side_by_side[j] += 1 << (31 - i);
			}
		}
	}
	for (j = 0; j < 13; j++) {
		conseil[j] = 0;
	}
	for (j = 0; j < 13; j++) {
		for (i = 0; i < 25; i++) {
			if (((side_by_side[j] >> (31 - i)) & 1) == 1) {
				conseil[j] |= (0b11111 << (29 - i));
				if (i % 2 == 1 && j < 12) {
					conseil[j + 1] |= (0b101 << (30 - i));
				} else if (i % 2 == 0 && j > 0) {
					conseil[j - 1] |= (0b101 << (30 - i));
				}
			}
		}
	}
}
