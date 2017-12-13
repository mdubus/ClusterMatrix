
#include "matrix.h"

void    init_sr_leds(void)
{
	// MASTER RESET SR LEDS
	LATBbits.LATB6 = 1;
	TRISBbits.TRISB6 = 0;

	// SLAVE SELECT
	LATBbits.LATB7 = 0;
	TRISBbits.TRISB7 = 0;

	// CONFIG SPI
	SPI2CON = 0;
	SPI2BRG = 3;
	SPI2CONbits.CKE = 1;
	SPI2CONbits.MSTEN = 1;

	// Interrupt Flag
	IFS1bits.SPI2RXIF = 0;

	// Interrupt Enable
	IEC1bits.SPI2RXIE = 1;

	// Interrupt Priority of SPI2
	IPC9 = 0b10100;

	garbage = SPI2BUF;
	SPI2CONbits.ON = 0;

	LATBbits.LATB7 = 1; // SS2

	// Allumage des leds temoin au lancement
	// en fonction de l'etat du dip switch

	if (dip == 0){
		led_clusters = 1;
		led_places = 8;
	}
	else
	{
		led_clusters = (1 << (dip - 1));
		led_places = 8;
	}
}
