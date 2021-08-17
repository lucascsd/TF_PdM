/*=============================================================================
 * TP Final
 * file: controladorADC.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORADC_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORADC_H_

#include "sapi.h"

#define DELAYADC	100

void inicializarADC (); //Se inicializa y configura la adquisición ADC.
void adquirirADC ( uint16_t * bufferAux );	//Adquiere ADC.
void finalizarADC (); //Se deshabilita la adquisición de ADC.
char* itoa(int value, char* result, int base);

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORADC_H_ */
