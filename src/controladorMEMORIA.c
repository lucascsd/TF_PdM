/*=============================================================================
 * TP Final
 * file: controladorMEMORIA.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "controladorMEMORIA.h"
#include "controladorUART.h"
#include "controladorLED.h"
#include "controladorADC.h"

/* Definición estructura del tipo memoryFSM_t */
memoryFSM_t _memory;

/* buffer de tamañó SIZEMEMORY */
uint16_t buffer[SIZEMEMORY];
uint16_t bufferAux[16];
const gpioMap_t ledSequence[] = { LEDR, LEDG, LEDB, LED1, LED2, LED3 };

memoryFSM_t rstCircularMemory ( )
{
	memoryFSM_t memoryAux = {
			NULL,
			NULL,
			MEMORY_RESET,
			0,
			0,
			0
	};

	printStateMem( memoryAux.memoryState );

	return memoryAux;

}

memoryFSM_t initCircularMemory ( )
{

	memoryFSM_t memoryAux;

	memoryAux.ptrWrite = buffer;
	memoryAux.ptrRead =	buffer;
	memoryAux.memoryState = MEMORY_WAIT_KEY;
	memoryAux.memorySize = SIZEMEMORY;
	memoryAux.indexW = 0;
	memoryAux.indexR = 0;

	printStateMem( memoryAux.memoryState );

	return memoryAux;
}

void writeMemory ( uint16_t *blockMemory, memoryFSM_t * memory )
{
	//TODO: FALTA FUNCION PARA ALMACENAR VALORES EN MEMORIA
	//PASAR POSICION DEL PTR DE ESCRITURA, PTR y MEMORIA
	for ( uint8_t i = 0; i < BLOQMEMORY; i++)
	{
		*(_memory.ptrWrite + _memory.indexW) = bufferAux[i];
		_memory.indexW++;
	}
	_memory.memoryState = MEMORY_WAIT_KEY ;
	printStateMem( _memory.memoryState );
}

bool_t readMemory ( uint16_t *blockMemory, memoryFSM_t * memory )
{
	/* TODO: USAR PUNTERO DE
	 * LECTURA PTRREAD.
	 */
	bool_t readComplete = TRUE;
	for ( uint8_t i = 0; i < _memory.memorySize; i++)
	{
		printf ("\t\tDato %d: %d \n\r", i, *( _memory.ptrWrite + i ) );
		printf ("\t\tDato %d: %d \n\r", i, buffer[i] );

	}
	_memory.memoryState = MEMORY_WAIT_KEY ;
	printStateMem( _memory.memoryState );
	return readComplete;
}

bool_t readBlockMemory ( uint16_t *blockMemory, memoryFSM_t * memory )
{
	/* TODO: USAR PUNTERO DE
	 * LECTURA PTRREAD.
	 */
	bool_t readComplete = TRUE;
	for ( uint8_t i = 0; i < BLOQMEMORY; i++)
	{
		printf ("\t\tDato %d: %d \n\r", _memory.indexR, *( _memory.ptrWrite + _memory.indexR ) );
		printf ("\t\tDato %d: %d \n\r", i, buffer[i] );
		_memory.indexR++;
	}
	_memory.memoryState = MEMORY_WAIT_KEY ;
	printStateMem( _memory.memoryState );
	return readComplete;
}

bool_t cleanMemory ( uint16_t *blockMemory )
{
	bool_t cleanComplete = TRUE;
	/* TODO: HACER FUNCION PARA
	 * BORRAR TODA LA MEMORIA CON
	 * VALOR 0.
	 */
	for ( uint8_t i = 0; i < SIZEMEMORY; i++)
	{
		*(_memory.ptrWrite + i) = 0;
		if ( !( buffer[i] == 0 ) ) return FALSE;
	}
	return cleanComplete;
}

bool_t updateMemoryStatus ()
{

	uint16_t diffPtr;
	static bool_t memLeida = FALSE;
	static bool_t memLimpia = FALSE;

	switch ( _memory.memoryState )
	{
	case	MEMORY_RESET:
		_memory = initCircularMemory();
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		break;

	case	MEMORY_WAIT_KEY:
		/* Acciones que se realizan en este estado */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LEDB ) ) blinkError (ERROR_OFF);
		finalizarADC ( );
		/* Verifico teclas presionadas */
		if ( actualizarKeyFSM ( &teclaUNO ) ) {
			_memory.memoryState = MEMORY_ADQ ;
			printStateMem( _memory.memoryState );
			inicializarADC( );
		}
		else if ( actualizarKeyFSM ( &teclaDOS ) ) {
			if ( memLeida == FALSE )
			{
				_memory.memoryState = MEMORY_READ ;
				printStateMem( _memory.memoryState );
			}
			/* Filtro flanco ascendente de tecla DOS */
			memLeida = FALSE;
		}
		else if ( actualizarKeyFSM ( &teclaTRES ) ) {
			if ( memLimpia == FALSE )
			{
				_memory.memoryState = MEMORY_CLEAN ;
				printStateMem( _memory.memoryState );
			}
			/* Filtro flanco ascendente de tecla TRES */
			memLimpia = FALSE;
		}
		else _memory.memoryState = MEMORY_WAIT_KEY;

		break;

	case	MEMORY_ADQ:
		/* Acciones que se realizan en este estado */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LED1 ) ) blinkError (ERROR_OFF);
		/* Verifico teclas presionadas */
		if ( actualizarKeyFSM ( &teclaUNO ) )
		{
			adquirirADC( bufferAux );
			_memory.memoryState = MEMORY_STATUS ;
			printStateMem( _memory.memoryState );
		}
		break;

	case	MEMORY_STATUS:

		diffPtr =  _memory.memorySize - _memory.indexW;
		if ( diffPtr < BLOQMEMORY ) {
			//NO Se PUEDE ESCRIBIR
			uartWriteString( UART_USB, "NO HAY ESPACIO SUFICIENTE PARA ALMACENAR LOS DATOS \n\r");
			uartWriteString( UART_USB, "POR FAVOR, LIMPIAR MEMORIA \n\r");
			_memory.memoryState = MEMORY_WAIT_KEY ;
			printStateMem( _memory.memoryState );
		}
		else
		{
			_memory.memoryState = MEMORY_WRITE ;
			printStateMem( _memory.memoryState );
		}
		break;

	case	MEMORY_WRITE:
		writeMemory( buffer, &_memory );
		break;

	case	MEMORY_READ:
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LED2 ) ) blinkError (ERROR_OFF);
		/* FUNCION PARA LEER MEMORIA */
		if ( readMemory ( buffer, &_memory ))
		{
			delay ( 2000 );		//TODO: HACERLO NO BLOQUEANTE
			memLeida = TRUE;
			_memory.memoryState = MEMORY_WAIT_KEY ;
			printStateMem( _memory.memoryState );
		}
		break;

	case	MEMORY_CLEAN:

		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LED3 ) ) blinkError (ERROR_OFF);
		if ( cleanMemory ( buffer ))
		{
			delay ( 2000 );		//TODO: HACERLO NO BLOQUEANTE
			memLimpia = TRUE;
			_memory = initCircularMemory();
		}
		break;

	default:
		break;
	}
	return TRUE;
}
