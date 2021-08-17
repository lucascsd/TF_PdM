/*=============================================================================
 * TP Final
 * file: controladorADC.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "controladorADC.h"

delay_t delayADC;

void inicializarADC( )
{
	/* Inicializar AnalogIO */
	adcConfig( ADC_ENABLE ); /* ADC */
	dacConfig( DAC_DISABLE ); /* DAC */
	delayConfig( &delayADC, DELAYADC );
}

void adquirirADC ( uint16_t * bufferAux)
{
	/* Buffer */
	static char uartBuff[10];
	/* Variable para almacenar el valor leido del ADC CH1 */
	uint16_t muestra = 0;
	uint8_t indice = 0;

	for ( indice = 0; indice < 16; indice++)
	{
		/* Leo la Entrada Analogica AI0 - ADC0 CH1 */
		bufferAux[indice] = 0;
		muestra = adcRead( CH1 );
		bufferAux[indice] = muestra;
		/* Envío la primer parte del mnesaje a la Uart */
		uartWriteString( UART_USB, "VALOR ADC CH1 LEIDO:\t\t" );
		/* Conversión de muestra entera a ascii con base decimal */
		itoa( muestra, uartBuff, 10 ); /* 10 significa decimal */
		/* Enviar muestra y Enter */
		uartWriteString( UART_USB, uartBuff );
		uartWriteString( UART_USB, ";\r\n" );
	}

}

void finalizarADC ()
{
	/* Inicializar AnalogIO */
	adcConfig( ADC_DISABLE ); /* ADC */
	dacConfig( DAC_DISABLE ); /* DAC */
}

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
char* itoa(int value, char* result, int base) {
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while(ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}
