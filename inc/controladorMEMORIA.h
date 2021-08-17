/*=============================================================================
 * TP Final
 * file: controladorMEMORIA.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORMEMORIA_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORMEMORIA_H_

#include "sapi.h"

#define SIZEMEMORY	128
#define BLOQMEMORY	16

typedef enum
{
	MEMORY_RESET,
	MEMORY_ADQ,
	MEMORY_STATUS,
	MEMORY_WRITE,
	MEMORY_READ,
	MEMORY_WAIT_KEY,
	MEMORY_CLEAN,
}stateMem_t ;	//Estado de la FSM de las teclas

typedef struct
{
	uint16_t	*ptrWrite;
	uint16_t	*ptrRead;
	stateMem_t	memoryState;
	uint16_t	memorySize;
	uint16_t		indexW;
	uint16_t		indexR;
}memoryFSM_t;	//Estructura de datos para control de FSM de la memoria

memoryFSM_t rstCircularMemory ( void );
memoryFSM_t initCircularMemory ( void );

void writeMemory ( uint16_t *blockMemory, memoryFSM_t * memory );
bool_t readMemory ( uint16_t *blockMemory, memoryFSM_t * memory );
bool_t cleanMemory ( uint16_t *blockMemory );
bool_t updateMemoryStatus ( void );

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORMEMORIA_H_ */
