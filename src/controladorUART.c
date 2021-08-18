/*=============================================================================
 * TP Final
 * file: controladorUART.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "controladorUART.h"

void inicializarUART() {

	bool_t printOk = FALSE;
	uartInit ( UART_USB, 115200 );
	uartWriteString	(UART_USB, "UART_USB configurada.\n\r" );

}

void infoUART(){

	uartWriteString( UART_USB, menu );

}

void printStateDebounce( stateKey_t estadoTecla ){

	char *estadoAntirebote[] = {
			"\t\tTECLA PRESIONADA \n\r",
			"\t\tTECLA EN FLANCO ASCENDENTE \n\r",
			"\t\tTECLA NO PRESIONADA \n\r",
			"\t\tTECLA EN FLANCO DESCENDENTE \n\r"};

	uartWriteString( UART_USB, "MEF ANTIRREBOTE:");
	uartWriteString( UART_USB, estadoAntirebote[estadoTecla] );
}

void printStateKey( uint8_t teclaPresionada )
{
	char *_estadoTecla[] = {
			"\t\tTECLA UNO 		\n\r",
			"\t\tTECLA DOS 		\n\r",
			"\t\tTECLA TRES 	\n\r",
			"\t\tTECLA CUATRO 	\n\r"};

	uartWriteString( UART_USB, "TECLA INICIALIZADA: ");
	uartWriteString( UART_USB, _estadoTecla[teclaPresionada] );
}

void printStateMem( stateMem_t state ){

	char *_estadoSecuencia[] = {
			"\tMEMORY_RESET		\n\r",
			"\tMEMORY_ADQ 		\n\r",
			"\tMEMORY_STATUS 	\n\r",
			"\tMEMORY_WRITE 	\n\r",
			"\tMEMORY_READ 		\n\r",
			"\tMEMORY_WAIT_KEY	\n\r",
			"\tMEMORY_CLEAN 	\n\r"
	};
	uartWriteString( UART_USB, "MEF CONTROLADOR MEMORIA:");
	uartWriteString( UART_USB, _estadoSecuencia[state] );

}

void printMemoryRead( memoryFSM_t * memory ){

	bool_t readComplete = TRUE;
	char indice[2], valor[10];

	for ( uint8_t i = 0; i < memory->memorySize; i++)
	{
		itoa( i, indice, 10 ); /* 10 significa decimal */
		uartWriteString( UART_USB, "DATO " );
		uartWriteString( UART_USB, indice );
		uartWriteString( UART_USB, " ALMACENADO:\t\t" );
		/* Conversión de muestra entera a ascii con base decimal */
		itoa( *( memory->ptrWrite + i ), valor, 10 ); /* 10 significa decimal */
		/* Enviar muestra y Enter */
		uartWriteString( UART_USB, valor );
		uartWriteString( UART_USB, ";\r\n" );
	}
}

void printAddressPtr( uint16_t	* dir ){

	uartWriteString	(UART_USB, "Direccón de memoria:" );
	printf ("\t\t%d \n\r", *dir );
}

