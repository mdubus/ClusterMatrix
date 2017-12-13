#include "matrix.h"

void reset_cluster(void)
{
	u8 i;
	u8 j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 13; j++)
		{
			cluster_data[i][j] = 0;
		}
	}
}

void    store_cluster(u8 data) {
	cluster_data[compteur / 52][(compteur % 52) / 4] +=
		data << ((3 - (compteur % 52 % 4)) * 8);
}

inline void    init_uart(void)
{

	//Pic RX
	U1MODEbits.UEN = 0; // UART Enable Bits. UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/UxBCLK pins are controlled by PORT latches
	// U2MODEbits.ABAUD = 0; // Auto-Baud Enable bit. Requires reception of Sync character(0x55)
	U1MODEbits.BRGH = 0; // High Baud Rate Enable bit
	U1BRG = 77;             // Baud Rate 9600
	U1MODEbits.PDSEL = 0; // Parity and Data Selection bits. 8-bit data, no parity
	U1MODEbits.STSEL = 0; // Stop Selection bit. 1 Stop bit.
	U1STAbits.URXEN = 1; // Receiver Enable bit
	U1STAbits.UTXEN = 1; // Transmit Enable bit
	U1STAbits.URXISEL = 0; // Interrupt flag bit is set when a character is received

	IFS1bits.U1RXIF = 0; // UART 1 Receiver Interrupt Request Flag bit
	IEC1bits.U1RXIE = 1; // UART 1 Receiver Interrupt Enable bit
	IEC1bits.U1TXIE = 0;
	IPC8bits.U1IP = 7; // UART 1 Interrupt Priority bits
	IPC8bits.U1IS = 3; // UART 1 Subpriority bits


	//Pic TX
	U2MODEbits.UEN = 0; // UART Enable Bits. UxTX and UxRX pins are enabled and used; UxCTS and UxRTS/UxBCLK pins are controlled by PORT latches
	// U2MODEbits.ABAUD = 0; // Auto-Baud Enable bit. Requires reception of Sync character(0x55)
	U2MODEbits.BRGH = 0; // High Baud Rate Enable bit
	U1BRG = 77;             // Baud Rate 9600
	U2MODEbits.PDSEL = 0; // Parity and Data Selection bits. 8-bit data, no parity
	U2MODEbits.STSEL = 0; // Stop Selection bit. 1 Stop bit.
	U2STAbits.URXEN = 1; // Receiver Enable bit
	U2STAbits.UTXEN = 1; // Transmit Enable bit
	U2STAbits.URXISEL = 0; // Interrupt flag bit is set when a character is received

	IFS1bits.U2RXIF = 0; // UART 2 Receiver Interrupt Request Flag bit
	IEC1bits.U2RXIE = 1; // UART 2 Receiver Interrupt Enable bit
	IEC1bits.U2TXIE = 0;
	IPC9bits.U2IP = 6; // UART 2 Interrupt Priority bits
	IPC9bits.U2IS = 3; // UART 2 Subpriority bits

	U2MODEbits.ON = 1;
	U1MODEbits.ON = 1;
}
