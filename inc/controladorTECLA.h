/*=============================================================================
 * TP Final
 * file: controladorTECLA.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORTECLA_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORTECLA_H_

#include "sapi.h"

/* TIEMPOS DE REBOTE (ms) */
#define DEBOUNCE_TIME	100

/* TECLAS */
#define	KEY1		0
#define KEY2		1
#define KEY3		2
#define KEY4		3

#define LAST_KEY	4

/* DEFINICION DE ESTADOS PARA LA MEF DE TECLAS */
typedef enum
{
	_TECLA_PRESIONADA,
	_TECLA_FLANCO_ASCENDENTE,
	_TECLA_NO_PRESIONADA,
	_TECLA_FLANCO_DESCENDENTE,
}stateKey_t;

/* ESTRUCUTRA DEL TIPO teclaFSM_t PARA MANEJAR CADA TECLA */
typedef struct
{
	uint8_t		indiceTecla;
	gpioMap_t 	teclaPosicion;
	stateKey_t 	estadoTecla;
	delay_t 	retardoNoBloqueante;
}teclaFSM_t ;

/* DEFINICION DE TECLAS */
teclaFSM_t teclaUNO, teclaDOS, teclaTRES, teclaCUATRO;

/* FUNCIONES PARA LA MAQUINA DE ESTADO FINITO DE LAS TECLAS */
teclaFSM_t inicializarKeyFSM ( gpioMap_t key, uint8_t _indiceTecla );
bool_t actualizarKeyFSM ( teclaFSM_t * teclaX );

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORTECLA_H_ */
