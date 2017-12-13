/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on June 27, 2017, 11:14 AM
 */

#include "matrix.h"
#include <plib.h>

inline void    pic_init(void)
{
	SYSTEMConfigPerformance(12000000);

	/***************** Remapable pins *****************/

	CFGCONbits.IOLOCK = 0;
	RPB8Rbits.RPB8R = 4; //RPB8 pin is SDO2
	SDI1Rbits.SDI1R = 1; //RPB5 pin is SDI1
	U1RXRbits.U1RXR = 0; //RPA2 is U1RX
	CFGCONbits.IOLOCK = 1;


	/***************** Open Drain *****************/

	ODCBbits.ODCB10 = 1;
	LATBbits.LATB10 = 0;
	TRISBbits.TRISB10 = 0;
	ODCBbits.ODCB9 = 1;
	LATBbits.LATB9 = 0;
	TRISBbits.TRISB9 = 0;

	/***************** Dip switch *****************/

	// Disable Analogic
	ANSELB = 0;

	LATBbits.LATB2 = 0;
	TRISBbits.TRISB2 = 1;
	LATBbits.LATB3 = 0;
	TRISBbits.TRISB3 = 1;

	// Lecture de l'etat du dip switch
	dip = (PORTBbits.RB3 + (PORTBbits.RB2 << 1)) ^ 3;


	/***************** Timers *****************/

	// Initialisation
	T2CON = 0;
	T3CON = 0;
	T4CON = 0;
	T5CON = 0;
	TMR2 = 0;
	TMR3 = 0;
	TMR4 = 0;
	TMR5 = 0;
	PR2 = 40000;
	PR3 = 60000;
	PR4 = 60000;
	PR5 = 65535;
	T2CONbits.TCKPS = 4;
	T3CONbits.TCKPS = 7;
	T4CONbits.TCKPS = 7;
	T5CONbits.TCKPS = 7;

	// Interrupts
	IPC2bits.T2IP = 5;
	IPC3bits.T3IP = 5;
	IPC4bits.T4IP = 5;
	IPC5bits.T5IP = 5;
	INTCONbits.MVEC = 1;
	IEC0bits.T2IE = 1;
	IEC0bits.T3IE = 1;
	IEC0bits.T4IE = 1;
	IEC0bits.T5IE = 1;

	//Timers ON
	T2CONbits.ON = 1;
	T3CONbits.ON = 1;
	T4CONbits.ON = 0;

	// Pin reset uart
	LATAbits.LATA4 = 0;
	TRISAbits.TRISA4 = 0;

	//cluster par defaut
	if (dip != 0)
		current_cluster = dip - 1; // init to default_cluster
	else
	{
		current_cluster = CLUSTER1;
		T4CONbits.ON = 1;
	}
}

static inline void ft_t4(void)
{
	if (loading == 1)
	{
		reset_timer++;
		if (reset_timer == 20)
		{
			dip = (PORTBbits.RB3 + (PORTBbits.RB2 << 1)) ^ 3;
			if (dip == 0)
			{
				if (current_cluster < CLUSTER3)
					current_cluster++;
				else
					current_cluster = 0;
			}
			else
			{
				T4CONbits.ON = 0;
				current_cluster = dip - 1;
				TMR4 = 0;
			}
			reset_timer = 0;
			led_places = 8;
			nb_cote_a_cote = 0;
			create_mask_side_by_side();
			draw_cluster();
			LATBbits.LATB7 = 1; // SS2
			led_clusters = (current_cluster == 0) + ((current_cluster == 1) << 1) + ((current_cluster == 2) << 2);
			SPI2BUF = led_clusters + led_places;
		}
	}
	t4_flag = 0;
}

int main(void)
{
	//    init_vars();
	pic_init();
	led_init();
	init_sr_leds();
	init_sr_buttons();
	init_uart();
	compteur = 4500;
	led_temoin_x = 7;
	led_temoin_y = 0;
	gol_on = 0;
	gol_delay = 0;
	gol_count = 0;
	led_temoin_x2 = 17;
	led_temoin_y2 = 12;
	time = 0;
	loading = 0;
	init_GOL();
	timer_give_me_uart = 0;

	__builtin_enable_interrupts();
	while (1)
	{
		WDTCONbits.WDTCLR = 1;
		if (t3_flag)
		{
			timer_give_me_uart++;
			LATAbits.LATA4 = 0; // reset pin envoi uart
			if (gol_on == 0) {
				if (led_temoin_x == 7 && led_temoin_y >=0 && led_temoin_y < 12)
					led_temoin_y++; //couloir gauche
				else if (led_temoin_x < 17 && led_temoin_x >= 7 && led_temoin_y == 12)
					led_temoin_x++; //couloir haut
				else if (led_temoin_x == 17 && led_temoin_y > 0 && led_temoin_y <= 12)
					led_temoin_y--; //couloir droite
				else if (led_temoin_x <= 17 && led_temoin_x > 7 && led_temoin_y == 0)
					led_temoin_x--; //couloir bas
				if (led_temoin_x2 == 7 && led_temoin_y2 >=0 && led_temoin_y2 < 12)
					led_temoin_y2++; //couloir gauche
				else if (led_temoin_x2 < 17 && led_temoin_x2 >= 7 && led_temoin_y2 == 12)
					led_temoin_x2++; //couloir haut
				else if (led_temoin_x2 == 17 && led_temoin_y2 > 0 && led_temoin_y2 <= 12)
					led_temoin_y2--; //couloir droite
				else if (led_temoin_x2 <= 17 && led_temoin_x2 > 7 && led_temoin_y2 == 0)
					led_temoin_x2--; //couloir bas
				draw_cluster();
				if (loading == 1)
					gol_delay++;
				time++;
			} else {
				if (loading == 0)
				{
					LATBbits.LATB6 = 0; // master reset sr leds
					asm("nop");
					LATBbits.LATB6 = 1;
				}
				gol_count++;
				update_GOL();
				if (gol_count >= 100 && loading == 1) {
					gol_on = 0;
					T3CONbits.TCKPS = 7;
				}
			}
			if (gol_delay >= 100) {
				init_GOL();
			}
			if (timer_give_me_uart > 50 && (gol_on == 0 || loading == 0))
			{
				SPI1CONbits.ON = 0;
				SPI2CONbits.ON = 0;
				LATAbits.LATA4 = 1; // envoi uart
				if (timer_give_me_uart > 1000)
					timer_give_me_uart = 200;
			}
			t3_flag = 0;

		}
		if (t4_flag)
		{
			ft_t4();
		}
	}
	return (0);
}
