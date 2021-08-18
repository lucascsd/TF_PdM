/*=============================================================================
 * TP Final
 * file: controladorMEMORIA.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORMEMORIA_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORMEMORIA_H_

/* sAPI */
#include "sapi.h"

/* MODULOS */
#include "controladorLED.h"
#include "controladorTECLA.h"
#include "controladorADC.h"

/* DEFINICION DE BLOQUES DE MEMORIA */
#define SIZEMEMORY	128
#define BLOQMEMORY	16

/* Estado de la FSM de las teclas */
typedef enum
{
	_MEMORY_RESET,
	_MEMORY_ADQ,
	_MEMORY_STATUS,
	_MEMORY_WRITE,
	_MEMORY_READ,
	_MEMORY_WAIT_KEY,
	_MEMORY_CLEAN,
	_MEMORY_READ_BLOCK
}stateMem_t ;

/* Estructura de datos para control de FSM de la memoria */
typedef struct
{
	uint16_t	*ptrWrite;		/* Puntero de escritura */
	uint16_t	*ptrRead;		/* Puntero de lectura */
	stateMem_t	memoryState;	/* Estados de la MEF */
	uint16_t	memorySize;		/* Tamaño de la memoria completa */
	uint16_t	bufferSize;		/* Tamaño de bloque de memoria para leer y escribir */
	uint16_t		indexW;		/* Indice de escritura */
	uint16_t		indexR;		/* Indice de lectura */
}memoryFSM_t;

/* FUNCIONES DE MEMORIA */
memoryFSM_t rstCircularMemory ( void );
memoryFSM_t initCircularMemory ( void );
void writeMemory ( memoryFSM_t * memory );
void readMemory ( memoryFSM_t * memory );
void readBlockMemory ( memoryFSM_t * memory );
bool_t cleanMemory ( memoryFSM_t * memory );
bool_t updateMemoryStatus ( memoryFSM_t * memory );

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORMEMORIA_H_ */
