#include "matrix.h"

void __ISR(_TIMER_2_VECTOR, IPL5SOFT) polling_sr_buttons(void)
{
	IFS0bits.T2IF = 0;
	LATBbits.LATB11 = 0; // PLn
	asm("nop");
	LATBbits.LATB11 = 1;
	LATBbits.LATB12 = 0; // SS1
	SPI1BUF = 0;
}

void __ISR(_TIMER_3_VECTOR, IPL5SOFT) led_temoin_timer(void)
{
	IFS0bits.T3IF = 0;
	t3_flag = 1;
}

void __ISR(_TIMER_4_VECTOR, IPL5SOFT) reset_after_25_seconds(void)
{
	IFS0bits.T4IF = 0;
	t4_flag = 1;
}

void __ISR(_TIMER_5_VECTOR, IPL5SOFT) reset_uart(void)
{
	IFS0bits.T5IF = 0;
	IEC0bits.T2IE = 1;
	IEC0bits.T3IE = 1;
	IEC1bits.SPI1RXIE = 1;
	IEC1bits.SPI2RXIE = 1;
	compteur = 4500;
	reset_cluster();
	LATAbits.LATA4 = 1; // pin pour demander reception UART
	T5CONbits.ON = 0;
	TMR5 = 0;
}

void __ISR(_SPI_1_VECTOR, IPL6SOFT) spi_ps_finish_receive(void)
{
	buff = (SPI1BUF)^127;
	IFS1bits.SPI1RXIF = 0;
	LATBbits.LATB12 = 1;
	uart_timer = 0;

	if (buff != 0)
	{
		T3CONbits.TCKPS = 7;
		gol_on = 0;
		gol_delay = 0;
		if ((buff & 0b0000111) != 0) {
			led_clusters = buff & 0b0000111;
			if ((buff & 0b0000111) == 1) {
				current_cluster = CLUSTER1;
			} else if ((buff & 0b0000111) == 2) {
				current_cluster = CLUSTER2;
			} else if ((buff & 0b0000111) == 4) {
				current_cluster = CLUSTER3;
			}
		}
		if ((buff & 0b1111000) != 0)
		{
			nb_cote_a_cote = 0;
			led_places = buff & 0b1111000;
			if (led_places >= 64)
				nb_cote_a_cote = 3;
			else if (led_places >= 32)
				nb_cote_a_cote = 2;
			else if (led_places >= 16)
				nb_cote_a_cote = 1;
			else if (led_places >= 8)
				nb_cote_a_cote = 0;
		}
		create_mask_side_by_side();
		if (loading == 1)
		{
			draw_cluster();
			reset_timer = 0;
			T4CONbits.ON = 1;
			LATBbits.LATB7 = 1; // SS2
			SPI2BUF = led_clusters + led_places;
		}
	}
}

void __ISR(_SPI_2_VECTOR, IPL5SOFT) spi_sp_finish_receive(void)
{
	garbage = SPI2BUF;
	IFS1bits.SPI2RXIF = 0;
	LATBbits.LATB7 = 0; //SS2
}

void    __ISR(_UART1_VECTOR, IPL7SOFT)  interrupt_receive_uart(void)
{
	timer_give_me_uart = 0;
	LATAbits.LATA4 = 0; // pin pour demander la nouvelle reception UART
	u8 data;
	data = U1RXREG;
	if (U1STAbits.OERR || U1STAbits.FERR)
	{
		LATAbits.LATA4 = 1;
		U1STAbits.OERR = 0;
	}
	IFS1bits.U1RXIF = 0; // Interrupt Flag
	if (loading == 0)
	{
		T3CONbits.TCKPS = 7;
		gol_on = 0;
		loading = 1;
	}
	time = 0;
	T5CONbits.ON = 1;
	TMR5 = 0;
	if(compteur == 4500) {
		adresse = data;
		if (adresse == ADRCLUST)
			reset_cluster();
		compteur = 0;
	}
	else {
		if (data == UARTSTOP && compteur == 156) {
			if (adresse == ADRCLUST) {
				T5CONbits.ON = 0;
				TMR5 = 0;
				SPI1CONbits.ON = 1;
				SPI2CONbits.ON = 1;
				compteur = 4500;
				create_mask_side_by_side();
				draw_cluster();
				adresse = 0;
				LATBbits.LATB7 = 1; // SS2
				SPI2BUF = led_clusters + led_places;
			}
		}
		else if (adresse == ADRCLUST && compteur > 156)
			LATAbits.LATA4 = 1;
		else {
			if (adresse == ADRCLUST) {
				store_cluster(data);
			}
			compteur++;
		}
	}
	TMR3 = 0;
}

