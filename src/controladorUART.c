/*=============================================================================
 * TP Final
 * file: controladorUART.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "controladorUART.h"

/* FUNCION PARA INICIALIZAR LA UART */
void inicializarUART() {

	uartInit ( UART_USB, 115200 );
	uartWriteString	(UART_USB, "UART_USB configurada.\n\r" );

}

/* FUNCION PARA IMPRESION DE MENSAJE INICIAL */
void infoUART(){

	uartWriteString( UART_USB, menu );

}

/* FUNCION PARA IMPRESION DEL ESTADO DE LAS TECLAS */
void printStateDebounce( stateKey_t estadoTecla ){

	char *estadoAntirebote[] = {
			"\t\tTECLA PRESIONADA \n\r",
			"\t\tTECLA EN FLANCO ASCENDENTE \n\r",
			"\t\tTECLA NO PRESIONADA \n\r",
			"\t\tTECLA EN FLANCO DESCENDENTE \n\r"};

	uartWriteString( UART_USB, "MEF ANTIRREBOTE:");
	uartWriteString( UART_USB, estadoAntirebote[estadoTecla] );
}

/* FUNCION PARA IMPRESION DE LAS TECLAS */
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

/* FUNCION PARA IMPRESION DEL ESTADO DE LA MEF DE LA MEMORIA */
void printStateMem( stateMem_t state ){

	char *_estadoSecuencia[] = {
			"\tMEMORY_RESET			\n\r",
			"\tMEMORY_ADQ 			\n\r",
			"\tMEMORY_STATUS 		\n\r",
			"\tMEMORY_WRITE 		\n\r",
			"\tMEMORY_READ 			\n\r",
			"\tMEMORY_WAIT_KEY		\n\r",
			"\tMEMORY_CLEAN 		\n\r",
			"\tMEMORY_READ_BLOCK 	\n\r"

	};
	uartWriteString( UART_USB, "MEF CONTROLADOR MEMORIA:");
	uartWriteString( UART_USB, _estadoSecuencia[state] );

}


/* FUNCION PARA IMPRESION DE LOS VALORES LEIDOS EN MEMORIA */
void printMemoryRead( memoryFSM_t * memory ){

	char indice[2], valor[10];

	for ( uint8_t i = 0; i < memory->memorySize; i++)
	{
		itoa( i, indice, 10 ); /* 10 significa decimal */
		uartWriteString( UART_USB, "DATO " );
		uartWriteString( UART_USB, indice );
		uartWriteString( UART_USB, " ALMACENADO:\t\t" );
		/* Conversión de muestra entera a ascii con base decimal */
		itoa( *( memory->ptrRead + i ), valor, 10 ); /* 10 significa decimal */
		/* Enviar muestra y Enter */
		uartWriteString( UART_USB, valor );
		uartWriteString( UART_USB, ";\r\n" );
	}
}
/* FUNCION PARA IMPRESION DE LOS VALORES LEIDOS EN BLOQUES MEMORIA */
void printBlockMemoryRead( memoryFSM_t * memory ){

	char indice[2], valor[10];

	if ( memory->indexR >= memory->memorySize )
	{
		memory->indexR = 0;
		uartWriteString( UART_USB, "\t ->\t SE SUPERO EL TAMAÑO DE LA MEMORIA \t<- \n\r");
		uartWriteString( UART_USB, "\t ->\t SE REINICIA EL PUNTERO DE LECTURA \t<- \n\r");

	}

	for ( uint8_t i = 0; i < memory->bufferSize; i++)
	{

		/* Conversión de indice de entera a ascii con base decimal */
		itoa( memory->indexR, indice, 10 ); /* 10 significa decimal */
		uartWriteString( UART_USB, "DATO " );
		uartWriteString( UART_USB, indice );
		uartWriteString( UART_USB, " ALMACENADO:\t\t" );

		/* Conversión de muestra entera a ascii con base decimal */
		itoa( *(memory->ptrWrite + memory->indexR), valor, 10 ); /* 10 significa decimal */

		/* Enviar muestra y Enter */
		uartWriteString( UART_USB, valor );
		uartWriteString( UART_USB, ";\r\n" );

		/* INCREMENTO INDICE DEL PUNTERO */
		memory->indexR++;

	}

}

