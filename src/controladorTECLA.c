/*=============================================================================
 * TP Final
 * file: controladorTECLA.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "controladorTECLA.h"
#include "controladorUART.h"

//***** FUNCION QUE INICIALIZA LA MEF DE LAS TECLAS ********************************************
// Recibe: el numero de tecla que se quiere consultar/actualizar
// Devuelve: los parametros de la estructura para inicializarla
// *********************************************************************************************
teclaFSM_t inicializarKeyFSM ( gpioMap_t key, uint8_t _indiceTecla ){

	teclaFSM_t tecla = {
			//tecla.indiceTecla = _indiceTecla,
			_indiceTecla,
			key,
			TECLA_NO_PRESIONADA,
			10
	};
	printStateKey( tecla.indiceTecla );
	return tecla;
}

//***** FUNCION DE ACTUALIZACION PARA LA MEF DE LAS TECLAS **************************************
// Recibe: el numero de tecla que se quiere consultar/actualizar
// Devuelve: TRUE si la tecla fue presionada o FALSE en caso contrario
// *********************************************************************************************
bool_t actualizarKeyFSM ( teclaFSM_t * tecla ){

	bool_t changedState = FALSE;

	switch ( tecla->estadoTecla ){

	case TECLA_PRESIONADA:
		if ( gpioRead ( tecla->teclaPosicion ) ) {
			tecla->estadoTecla = TECLA_FLANCO_ASCENDENTE;
			printStateDebounce( tecla->estadoTecla );
			delayInit( &tecla->retardoNoBloqueante, DEBOUNCE_TIME );
		}
		break;

	case TECLA_FLANCO_ASCENDENTE:
		if ( delayRead ( &tecla->retardoNoBloqueante ) ) {
			if ( gpioRead ( tecla->teclaPosicion ) ){
				tecla->estadoTecla = TECLA_NO_PRESIONADA;
				printStateDebounce( tecla->estadoTecla );
				changedState = TRUE;
			}
			else tecla->estadoTecla = TECLA_PRESIONADA;
		}
		break;

	case TECLA_NO_PRESIONADA:
		if ( !gpioRead ( tecla->teclaPosicion ) ){
			tecla->estadoTecla = TECLA_FLANCO_DESCENDENTE;
			printStateDebounce( tecla->estadoTecla );
			delayInit( &tecla->retardoNoBloqueante, DEBOUNCE_TIME );
		}
		break;

	case TECLA_FLANCO_DESCENDENTE:
		if ( delayRead ( &tecla->retardoNoBloqueante ) ) {
			if ( !gpioRead ( tecla->teclaPosicion ) ){
				tecla->estadoTecla = TECLA_PRESIONADA;
				printStateDebounce( tecla->estadoTecla );
				changedState = TRUE;
			}
			else tecla->estadoTecla = TECLA_NO_PRESIONADA;
		}
		break;

	default:
		tecla->estadoTecla = TECLA_NO_PRESIONADA;
		break;
	}
	return changedState;
}
