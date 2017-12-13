/* 
 * File:   matrix.h
 * Author: bocal
 *
 * Created on June 30, 2017, 3:02 PM
 */

#ifndef MATRIX_H
#define	MATRIX_H

#ifdef	__cplusplus
extern "C" {
#endif



#define _SUPPRESS_PLIB_WARNING 1

#include <xc.h>
#include <sys/attribs.h>
#include <stdint.h>

	typedef int8_t      s8;
	typedef uint8_t     u8;
	typedef int16_t     s16;
	typedef uint16_t    u16;
	typedef int32_t     s32;
	typedef uint32_t    u32;


	u8 dip;
	u8 buff;
	u8 led_clusters;
	u8 led_places;
	u8 reset_timer;
	u8 garbage;
	u8 nb_voisins;
	u8 nb_cote_a_cote;
	u32 cluster_data[3][13];
	const u32 mask_exist[3][13];
	u32 side_by_side[13];
	u32 conseil[13];
	u32 gameoflife[2][13];
	u8 loading;

	u16 compteur;
	u8 adresse;
	u8 current_cluster;

	u8 led_temoin_x;
	u8 led_previous_x;
	u8 led_temoin_y;
	u8 led_previous_y;
	u8 led_temoin_x2;
	u8 led_previous_x2;
	u8 led_temoin_y2;
	u8 led_previous_y2;
	u32 time;
	u8 gol_on;
	u8 gol_count;
	u16 gol_delay;
	u16 timer_give_me_uart;

	u8 t3_flag;
	u8 t4_flag;

	u8 uart_timer;

	void draw_cluster();
	void draw_color_one(u8 where);
	void draw_color_two(u8 where);
	void off(u8 where);
	void led_init(void);
	void init_sr_leds(void);
	void init_sr_buttons(void);
	void init_interrupt_timer(void);
	void init_uart(void);
	static void draw_line(u8 row, u8 where, u8 i);


#define RED 1
#define BLUE 2
#define YELLOW 3
#define TEMOIN 4
#define LBLUE 5
#define LLBLUE 6

#define ADRCLUST 'c'
#define UARTSTOP 's'
#define CLUSTER1 0
#define CLUSTER2 1
#define CLUSTER3 2
#define LOW_LEDS 1
#define HIGH_LEDS 2
#define GOL_CURRENT 0
#define GOL_NEXT 1


#ifdef	__cplusplus
}
#endif

#endif	/* MATRIX_H */

