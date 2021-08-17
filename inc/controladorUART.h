/*=============================================================================
 * TP Final
 * file: controladorUART.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORUART_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORUART_H_

#include "sapi.h"
#include "controladorMEMORIA.h"
#include "controladorTECLA.h"

//VARIABLES

static char menu[] =
		"\n\r"
		"*********************** Trabajo práctico final - PdM **********************\n\r"
		"\n\r"
		"Alumno: Lucas Zalazar														\n\r"
		"***************************************************************************\n\r"
		"Se informarán cada cambios en la MEF antirrebote							\n\r"
		"Se informarán cada cambio de estado en la MEF del controlador de memoria	\n\r"
		"Se imprimen los datos almacenados en memoria cuando se lo requiera			\n\r"
		"***************************************************************************\n\r"
		"Estados de la memoria: 													\n\r"
		"	- 	MEMORY_RESET: estado inicial de la máquina de estado				\n\r"
		"	-	MEMORY_ADQ: se adquieren datos del conversor analógico digital		\n\r"
		"	-	MEMORY_STATUS: Luego de la adquisición, se verifica que haya lugar	\n\r"
		"		disponible en memoria												\n\r"
		"	-	MEMORY_WRITE: Estado de escritura donde se almacenarán los datos	\n\r"
		"		adquiridos															\n\r"
		"	-	MEMORY_READ: Se leen e imprimen los datos almacenados en memoria	\n\r"
		"	-	MEMORY_WAIT_KEY: Se espera de acciones asociadas a las teclas		\n\r"
		"	-	MEMORY_CLEAN: Se limpia la memoria completa.						\n\r"
		"\n\r"
		;

//FUNCIONES PARA LA UART
void inicializarUART();
void infoUART();
void printStateDebounce( stateKey_t estadoTecla );
void printStateKey( uint8_t teclaPresionada );
void printStateMem( stateMem_t state );
void printMemoryRead();
void printAddressPtr( uint16_t	* dir );

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORUART_H_ */
