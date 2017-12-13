#include "matrix.h"

inline void    init_sr_buttons(void)
{
	// PLn
	LATBbits.LATB11 = 1; // PLn a 1 pour demarrer la transmission
	TRISBbits.TRISB11 = 0; // PLn en output

	// SS1 en GPIO
	LATBbits.LATB12 = 1;
	TRISBbits.TRISB12 = 0;

	// Interrupt Flag
	IFS1bits.SPI1RXIF = 0;
	// Interrupt Enable
	IEC1bits.SPI1RXIE = 1;
	// Interrupt Priority
	IPC7bits.SPI1IP = 6;

	// Stop + Reset SPI
	SPI1CON = 0;

	// Baud rate
	SPI1BRG = 3;

	// Settings SPI
	SPI1CONbits.MSTEN = 1;
	SPI1CONbits.SMP = 1;
	SPI1CONbits.CKP = 1;
	SPI1CONbits.CKE = 1;

	// Clear Overflow flag
	SPI1STATbits.SPIRBF = 0;
	SPI1STATbits.SPIROV = 0;


	// Active le SPI1
	SPI1CONbits.ON = 0;
}

