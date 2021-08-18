CESE 15Co2021

# Programación de microprocesadores
## Practica final

Repositorio para la práctica final de la materia Programación de Microcontroladores.

Autores: Lucas Zalazar lucas.zalazar6@gmail.com

### Resumen
La plataforma recibirá desde el ADC, datos para guardar en un buffer en memoria de tamaño a definir. 
Se indicará el estado que posee y enviará por UART el contenido y estado de la memoria cada vez que se lo requiera. 
La adquisición iniciará con el flanco ascendente de una tecla y se dejará de adquirir datos con el flanco descendente.
Se chequeará la disponibilidad en memoria y se realizará la escritura en memoria. 
El buffer está manejado por una MEF para verificación, escritura y lectura.
Mediante UART, se indicará el estado de la memoria y el tipo de evento que se realiza  sobre la misma. 
Se implementará un controlador para la UART como para el ADC.
Se implementará una MEF para el antirebote de las teclas.

#### Condiciones de funcionamiento
###### Dependencias externas:
 - sAPI.h;

###### Periféricos:
 - ADC;
 - UART;
 - GPIO;

#### Modularización
![](https://github.com/lucascsd/TF_PdM/blob/main/image/modularizacion.svg)

#### Maquina de estado finito del controlador de memoria
![](https://github.com/lucascsd/TF_PdM/blob/main/image/MEF_memoria.svg)

###### Archivos de modularización
| File name | hearders                    |
| ------------- | ------------------------------ |
| [TF_memoria.c](https://github.com/lucascsd/TF_PdM/blob/main/src/TF_memoria.c)|[TF_memoria.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/TF_memoria.h)|
| [controladorMEMORIA.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorMEMORIA.c)|[controladorMEMORIA.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorMEMORIA.h)|
| [controladorADC.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorADC.c)|[controladorADC.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorADC.h)|
| [controladorLED.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorLED.c)|[controladorLED.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorLED.h)|
| [controladorTECLA.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorTECLA.c)|[controladorTECLA.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorTECLA.h)|
| [controladorUART.c](https://github.com/lucascsd/TF_PdM/blob/main/src/controladorUART.c)|[controladorUART.h](https://github.com/lucascsd/TF_PdM/blob/main/inc/controladorUART.h)|


