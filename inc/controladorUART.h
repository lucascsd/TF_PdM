/*=============================================================================
 * TP Final
 * file: controladorUART.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORUART_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORUART_H_

/* sAPI */
#include "sapi.h"

/* MODULOS */
#include "controladorTECLA.h"
#include "controladorMEMORIA.h"

/* DEFINICION DE MENSAJE */
static char menu[] =
		"\n\r"
		"*********************** Trabajo práctico final - PdM **********************\n\r"
		"\n\r"
		"Alumno: Lucas Zalazar														\n\r"
		"***************************************************************************\n\r"
		"FUNCIONES:				 													\n\r"
		"Se informarán cada cambios en la MEF antirrebote							\n\r"
		"Se informarán cada cambio de estado en la MEF del controlador de memoria	\n\r"
		"Se imprimen los datos almacenados en memoria cuando se lo requiera			\n\r"
		"***************************************************************************\n\r"
		"Estados de la memoria: 													\n\r"
		"	- 	_MEMORY_RESET: estado inicial de la máquina de estado				\n\r"
		"	-	_MEMORY_WAIT_KEY: Se espera de acciones asociadas a las teclas		\n\r"
		"	-	_MEMORY_ADQ: se adquieren datos del conversor analógico digital		\n\r"
		"	-	_MEMORY_STATUS: Luego de la adquisición, se verifica que haya lugar	\n\r"
		"		disponible en memoria												\n\r"
		"	-	_MEMORY_WRITE: Estado de escritura donde se almacenarán los datos	\n\r"
		"		adquiridos															\n\r"
		"	-	_MEMORY_READ: Se leen e imprimen los datos almacenados en memoria	\n\r"
		"	-	_MEMORY_CLEAN: Se limpia la memoria completa.						\n\r"
		"Uso de teclas:			 													\n\r"
		"	- 	Tecla UNO: Adquisicion mediante ADC y escritura de valores en memoria			\n\r"
		"	- 	Tecla DOS: Lectura e impresión de valores almacenados en memoria				\n\r"
		"	- 	Tecla TRES: Limpieza de datos almacenados en memoria							\n\r"
		"	- 	Tecla CUATRO: Lectura e impresión de valores almacenados en memoria por bloques	\n\r"
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
