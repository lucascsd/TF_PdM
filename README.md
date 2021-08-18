CESE 15Co2021

# Programación de microprocesadores
## Práctica final

Repositorio para la práctica final de la materia Programación de Microcontroladores.

Autores: Lucas Zalazar lucas.zalazar6@gmail.com

### Funciones de la plataforma

 - Adquirir datos desde ADC.
 - Guardar en buffer en memoria de tamaño a definir. 
 - Indicar estado de MEF de memoria.
 - Enviar por UART datos y estado de MEF de la memoria.
 - Iniciar la adquisición con el flanco ascendente de una tecla uno. 
 - Detener la adquisición de datos con el flanco descendente de la tecla uno.
 - Verificar disponibilidad de espacio en memoria.
 - Escribir en memoria. 
 - Implementar MEF para controlar la memoria.
 - Implementar MEF para el antirebote de las teclas.

### Dependencias externas:
 - sAPI.h;

### Periféricos:
 - ADC;
 - UART;
 - GPIO;

#### Modularización
![](https://github.com/lucascsd/TF_PdM/blob/main/image/modularizacion.svg)

#### Máquina de estado finito del controlador de memoria
![](https://github.com/lucascsd/TF_PdM/blob/main/image/MEF_memoria_1.svg)

#### Código del controlador de memoria

```
/* Estados de la FSM de las teclas */
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
```

```
/* Estructura de datos para control de FSM de la memoria */
typedef struct
{
	uint16_t	*ptrWrite;		/* Puntero de escritura */
	uint16_t	*ptrRead;		/* Puntero de lectura */
	stateMem_t	memoryState;	/* Estados de la MEF */
	uint16_t	memorySize;		/* Tamaño de la memoria completa */
	uint16_t	bufferSize;		/* Tamaño de bloque de memoria para leer y escribir */
	uint16_t		indexW;		/* Índice de escritura */
	uint16_t		indexR;		/* Índice de lectura */
}memoryFSM_t;

```

```
/* FUNCIONES DE MEMORIA */
memoryFSM_t rstCircularMemory ( void );
memoryFSM_t initCircularMemory ( void );
void writeMemory ( memoryFSM_t * memory );
void readMemory ( memoryFSM_t * memory );
void readBlockMemory ( memoryFSM_t * memory );
bool_t cleanMemory ( memoryFSM_t * memory );
bool_t updateMemoryStatus ( memoryFSM_t * memory );

```
###### Archivos de modularización
| File name | hearders                    |
| ------------- | ------------------------------ |
| [TF_memoria.c](https://github.com/lucascsd/TF_PdM/blob/main/src/TF_memoria.c)|[TF_memoria.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/TF_memoria.h)|
| [controladorMEMORIA.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorMEMORIA.c)|[controladorMEMORIA.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorMEMORIA.h)|
| [controladorADC.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorADC.c)|[controladorADC.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorADC.h)|
| [controladorLED.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorLED.c)|[controladorLED.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorLED.h)|
| [controladorTECLA.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorTECLA.c)|[controladorTECLA.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorTECLA.h)|
| [controladorUART.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorUART.c)|[controladorUART.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorUART.h)|


