/*=============================================================================
 * TP Final
 * file: controladorMEMORIA.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "controladorMEMORIA.h"
#include "controladorUART.h"

/* buffer de tamañó SIZEMEMORY */
static uint16_t buffer[SIZEMEMORY];
static uint16_t bufferAux[16];
const gpioMap_t ledSequence[] = { LEDR, LEDG, LEDB, LED1, LED2, LED3 };

//***** FUNCIÓN DE RESET DE MEMORIA ************************************************************
// Recibe: VACIO.
// Devuelve: ESTRUCTURA DEL TIPO memoryFSM_t CON VALORES POR DEFECTOS.
// *********************************************************************************************
memoryFSM_t rstCircularMemory ( )
{
	memoryFSM_t memoryAux = {
			NULL,
			NULL,
			_MEMORY_RESET,
			0,
			0,
			0,
			0
	};

	printStateMem( memoryAux.memoryState );

	return memoryAux;

}

//***** FUNCIÓN DE INICIO DE MEMORIA ***********************************************************
// Recibe: VACIO.
// Devuelve: ESTRUCTURA DEL TIPO memoryFSM_t CON VALORES INICIALIZADOS.
// *********************************************************************************************
memoryFSM_t initCircularMemory ( )
{

	memoryFSM_t memoryAux;
	/* SE INICIALIZA ESTRUCTURA */
	memoryAux.ptrWrite = buffer;
	memoryAux.ptrRead =	buffer;
	memoryAux.memoryState = _MEMORY_WAIT_KEY;
	memoryAux.memorySize = SIZEMEMORY;
	memoryAux.bufferSize = BLOQMEMORY;
	memoryAux.indexW = 0;
	memoryAux.indexR = 0;

	/* SE IMPRIME ESTADO ACTUAL */
	printStateMem( memoryAux.memoryState );

	/* SE RETORNA LA ESTRUCTURA INICIALIZADA */
	return memoryAux;
}

//***** FUNCIÓN DE ESCRITURA DE MEMORIA ********************************************************
// Recibe: PUNTERO A ESTRUCTURA DEL TIPO memoryFSM_t CON VALORES POR DEFECTOS.
// Devuelve: VOID.
// *********************************************************************************************
void writeMemory ( memoryFSM_t * memory )
{

	/* SE ALMACENAN LOS VALORES LEIDOS DEL ADC ALMACENADOS
	 * EN BUFFER AUXILIAR DE 16 VALORES
	 */
	for ( uint8_t i = 0; i < BLOQMEMORY; i++)
	{
		*(memory->ptrWrite + memory->indexW) = bufferAux[i];
		memory->indexW++;
	}

}

//***** FUNCIÓN DE LECTURA DE MEMORIA *************************************************************
// Recibe: 	PUNTERO A ESTRUCTURA DEL TIPO memoryFSM_t CON TODOS LOS VALORES ALMACENADOS EN MEMORIA.
// Devuelve: VOID.
// ************************************************************************************************
void readMemory ( memoryFSM_t * memory )
{

	/* FUNCION DE IMPRESON DE VALORES */
	printMemoryRead( memory );

}

//***** FUNCIÓN DE LECTURA DE MEMORIA EN BLOQUE DE 16 *********************************************
// Recibe: 	PUNTERO A ESTRUCTURA DE TIPO memoryFSM_t CON TODOS LOS VALORES ALMACENADOS EN MEMORIA.
// Devuelve: BOOLEANO CON EL ESTADO DE LA OPERACION FINALIZADO.
// ************************************************************************************************
bool_t readBlockMemory ( memoryFSM_t * memory )
{
	/* TODO: USAR PUNTERO DE
	 * LECTURA PTRREAD.
	 */
	bool_t readComplete = TRUE;
	for ( uint8_t i = 0; i < BLOQMEMORY; i++)
	{
		printf ("\t\tDato %d: %d \n\r", memory->indexR, *( memory->ptrWrite + memory->indexR ) );
		printf ("\t\tDato %d: %d \n\r", i, buffer[i] );
		memory->indexR++;
	}
	memory->memoryState = _MEMORY_WAIT_KEY ;
	printStateMem( memory->memoryState );
	return readComplete;
}

//***** FUNCIÓN DE LIMPIEZA DE MEMORIA ***********************************************************
// Recibe: 	PUNTERO A ESTRUCTURA DE TIPO memoryFSM_t CON TODOS LOS VALORES ALMACENADOS EN MEMORIA.
// Devuelve: BOOLEANO CON EL ESTADO DE LA OPERACION FINALIZADO.
// ***********************************************************************************************
bool_t cleanMemory ( memoryFSM_t * memory )
{

	bool_t lecturaCompleta = TRUE;

	/* SE PONE A CERO CADA LUGAR DE MEMORIA */
	for ( uint8_t i = 0; i < SIZEMEMORY; i++)
	{

		*(memory->ptrWrite + i) = 0;
		if ( !( buffer[i] == 0 ) ) return FALSE;

	}

	/* DEVUELVO EL ESTADO DE LA OPERACION */
	return lecturaCompleta;
}

//***** FUNCIÓN DE ACTUALIZACION DEL ESTADO DE MEMORIA *******************************************
// Recibe: 	PUNTERO A ESTRUCTURA DE TIPO memoryFSM_t CON TODOS LOS VALORES ALMACENADOS EN MEMORIA.
// Devuelve: BOOLEANO CON EL ESTADO DE LA OPERACION FINALIZADO.
// ***********************************************************************************************
bool_t updateMemoryStatus ( memoryFSM_t * memory )
{

	/* DEFINICION DE VARIABLES LOCALES */
	uint16_t diffPtr;
	static bool_t memLeida = FALSE;
	static bool_t memLimpia = FALSE;

	/* CAMBIOS DE ESTADOS */
	switch ( memory->memoryState )
	{

	/* Estado inicial de la máquina de estado */
	case	_MEMORY_RESET:

		/* FUNCION PARA INICIALIZAR MEMORIA */
		*memory = initCircularMemory();

		/* APAGO LOS LEDS */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		break;

	/* Se está a la espera de acciones asociadas a las teclas */
	case	_MEMORY_WAIT_KEY:

		/* INDICACION VISUAL DEL ESTADO */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LEDB ) ) blinkError (ERROR_OFF);
		finalizarADC ( );

		/* SE VERIFICA ESTADO DE TECLAS */
		if ( actualizarKeyFSM ( &teclaUNO ) ) {

			/* ASIGNACION DE ESTADO SIGUIENTE */
			memory->memoryState = _MEMORY_ADQ;
			printStateMem( memory->memoryState );

			/* FUNCION PARA CONFIGURAR ADC */
			inicializarADC( );

		}
		else if ( actualizarKeyFSM ( &teclaDOS ) ) {
			if ( memLeida == FALSE )
			{
				/* ASIGNACION DE ESTADO SIGUIENTE */
				memory->memoryState = _MEMORY_READ;
				printStateMem( memory->memoryState );
			}
			/* Filtro flanco ascendente de tecla DOS */
			memLeida = FALSE;
		}
		else if ( actualizarKeyFSM ( &teclaTRES ) ) {
			if ( memLimpia == FALSE )
			{
				/* ASIGNACION DE ESTADO SIGUIENTE */
				memory->memoryState = _MEMORY_CLEAN ;
				printStateMem( memory->memoryState );
			}
			/* Filtro flanco ascendente de tecla TRES */
			memLimpia = FALSE;
		}
		/* ASIGNACION DE ESTADO SIGUIENTE */
		else memory->memoryState = _MEMORY_WAIT_KEY;

		break;

	/* Se adquieren datos del conversor analógico digital */
	case	_MEMORY_ADQ:

		/* INDICACION VISUAL DEL ESTADO */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LED1 ) ) blinkError (ERROR_OFF);

		/* SE VERIFICA ESTADO TECLA UNO */
		if ( actualizarKeyFSM ( &teclaUNO ) )
		{

			/* FUNCION PARA ALMACENAR DATOS ADQUIRIDOS POR ADC */
			uartWriteString( UART_USB, "\t ->\t ADQUIRIENDO DATOS \t<- \n\r");
			adquirirADC( bufferAux );
			uartWriteString( UART_USB, "\t ->\t FIN DE ADQUISICIÓN \t<- \n\r");
			/* ASIGNACION DE ESTADO SIGUIENTE */
			memory->memoryState = _MEMORY_STATUS ;
			printStateMem( memory->memoryState );

		}
		break;

	/* Luego de la adquisición, se verifica que haya lugar disponible en memoria */
	case	_MEMORY_STATUS:

		/* SE CALCULA MEMORIA RESTANTE PARA ESCRIBIR */
		diffPtr =  memory->memorySize - memory->indexW;
		if ( diffPtr < BLOQMEMORY ) {

			/* NO SE PUEDE ESCRIBIR HASTA QUE SE HAYA LIMPIADO LA MEMORIA */
			uartWriteString( UART_USB, "\t ->\t NO HAY ESPACIO SUFICIENTE PARA ALMACENAR LOS DATOS \t<- \n\r");
			uartWriteString( UART_USB, "\t ->\t POR FAVOR, LIMPIAR MEMORIA \t<- \n\r");

			/* ASIGNACION DE ESTADO SIGUIENTE */
			memory->memoryState = _MEMORY_WAIT_KEY ;
			printStateMem( memory->memoryState );
		}
		else
		{
			/* ASIGNACION DE ESTADO SIGUIENTE */
			memory->memoryState = _MEMORY_WRITE ;
			printStateMem( memory->memoryState );
		}
		break;

	/* Estado de escritura donde se almacenarán los datos adquiridos */
	case	_MEMORY_WRITE:

		/* FUNCION PARA ESCRIBIR MEMORIA */
		writeMemory( memory );

		/* ASIGNACION DE ESTADO SIGUIENTE */
		memory->memoryState = _MEMORY_WAIT_KEY ;
		printStateMem( memory->memoryState );
		break;

	/* Se leen e imprimen los datos almacenados en memoria */
	case	_MEMORY_READ:

		/* INDICACION VISUAL DEL ESTADO */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LED2 ) ) blinkError (ERROR_OFF);

		/* FUNCION PARA LEER MEMORIA */
		readMemory ( memory );

		/* RETARDO BLOQUEANTE PARA INDICAR VISUALMENTE EL ESTADO */
		delay ( 2000 );
		memLeida = TRUE;

		/* ASIGNACION DE ESTADO SIGUIENTE */
		memory->memoryState = _MEMORY_WAIT_KEY ;
		printStateMem( memory->memoryState );
		break;

	/* Se limpia la memoria completa */
	case	_MEMORY_CLEAN:

		/* INDICACION VISUAL DEL ESTADO */
		if ( !ledsOff( ledSequence, CANTIDADLEDS ) ) blinkError (ERROR_OFF);
		if ( !ledOn ( LED3 ) ) blinkError (ERROR_OFF);

		/* FUNCION PARA LEER MEMORIA */
		if ( cleanMemory ( memory ) )
		{
			/* RETARDO BLOQUEANTE PARA INDICAR VISUALMENTE EL ESTADO */
			delay ( 2000 );
			memLimpia = TRUE;
			uartWriteString( UART_USB, "\t ->\t MEMORIA LIMPIA \t<- \n\r");
		}
		else
		{
			/* NO SE PUEDE BORRAR LA MEMORIA, RESETEO ESTRUCTURA */
			uartWriteString( UART_USB, "\t ->\t NO ES POSIBLE LIMPIAR LA MEMORIA \t<- \n\r");
			uartWriteString( UART_USB, "\t ->\t SE RESETEARA LA MEMORIA Y SU ESTRUCTURA ASOCIADA \t<- \n\r");

			/* FUNCION PARA RESETEAR LA MEMORIA */
			*memory = rstCircularMemory();
			break;
		}

		/* FUNCION PARA INICIALIZAR PUNTERO A MEMORIA */
		*memory = initCircularMemory();
		break;

	/* EN CASO DE NO TENER ASIGNADO NINGUN ESTADO,
	 * SE ASIGNA ESTADO INICIAL DE LA MEF
	 */
	default:

		/* ASIGNACION DE ESTADO SIGUIENTE */
		memory->memoryState = _MEMORY_WAIT_KEY ;
		printStateMem( memory->memoryState );
		break;

	}
	return TRUE;
}
