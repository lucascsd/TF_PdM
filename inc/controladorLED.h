/*=============================================================================
 * TP Final
 * file: controladorLED.h
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#ifndef PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORLED_H_
#define PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORLED_H_

#include "sapi.h"

// TIEMPOS DE ERROR (ms)
#define ERROR_OFF		500
#define ERROR_ON		500
#define ERROR_SEQ		1000
#define ERROR_TIME		1000

#define WAITKEY			500
#define ADQ				500
#define ERROR_ADQ		1000

#define CANTIDADLEDS	6

//const uint8_t sequenceLength = sizeof ( ledSequence ) / sizeof ( gpioMap_t );

// FUNCIONES DE CONTROL DE LEDS
bool_t ledsOff ( const gpioMap_t *_ledSequence, const uint8_t _sequenceLength );
bool_t ledOn ( gpioMap_t led );
bool_t ledOff ( gpioMap_t led );
bool_t ledToggle( gpioMap_t led );
void blinkError ( tick_t delayError );

#endif /* PRACTICAFINAL_PDM_TF_MEMORIA_INC_CONTROLADORLED_H_ */
