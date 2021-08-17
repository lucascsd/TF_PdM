/*=============================================================================
 * TP Final
 * file: TF_memoria.c
 * Authors: Lucas Zalazar <lucas.zalazar6@gmail.com>
 * Date: 2021/08/15
 * Version: 1.0
 *===========================================================================*/

#include "TF_memoria.h"
#include "sapi.h"

int main( void )
{
   // ----- Setup -----------------------------------
   boardInit();

   /* Verificación TICK_RATE rango permitido de tiempo: 1 a 50 ms */
   if ( ( TICK_RATE < TICK_RATE_MIN ) || ( TICK_RATE > TICK_RATE_MAX ) )  blinkError( ERROR_TIME );
   if ( !tickConfig ( TICK_RATE ) )  blinkError( ERROR_TIME );

   /* Inicialización de UART e impresión de menú */
   inicializarUART();
   infoUART();

   /* TODO: HACER LOCAL LA VARIABLE DEL TIPO memoryFSM_t */
   /* Reset e inicialización de memoria */
   rstCircularMemory ( );

   /* Se inicializa la MEF de las teclas */
   teclaUNO 	= inicializarKeyFSM ( TEC1, KEY1 );
   teclaDOS 	= inicializarKeyFSM ( TEC2, KEY2 );
   teclaTRES 	= inicializarKeyFSM ( TEC3, KEY3 );
   //teclaCUATRO 	= inicializarKeyFSM ( TEC4, KEY4 );

   /* SUPER LOOP */
   while( true ) {
	   if ( !updateMemoryStatus() ) blinkError ( ERROR_TIME );
   }

   // YOU NEVER REACH HERE, because this program runs directly or on a
   // microcontroller and is not called by any Operating System, as in the 
   // case of a PC program.
   return 0;
}
