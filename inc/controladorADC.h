/*=============================================================================
 * TP Final
 * file: controladorADC.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORADC_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORADC_H_

/* sAPI */
#include "sapi.h"

/* DELAY PARA ADC */
#define DELAYADC	100

/* FUNCIONES PARA ADC */
void inicializarADC (); //Se inicializa y configura la adquisición ADC.
void adquirirADC ( uint16_t * bufferAux );	//Adquiere ADC.
void finalizarADC (); //Se deshabilita la adquisición de ADC.
char* itoa ( uint16_t value, char* result, uint16_t base );

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORADC_H_ */
