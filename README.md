CESE 15Co2021

# Programación de microprocesadores
## Practica 4

Repositorio para la cuarta práctica de la materia Programación de Microcontroladores.

Autores: Martin Rios jrios@fi.uba.ar - Lucas Zalazar lucas.zalazar6@gmail.com

### Resumen
Implementar mediante el modelo de Máquina de Estados Finitos el antirrebote de teclas y la lógica de funcionamiento de un semáforo.

#### Condiciones de funcionamiento
###### Dependencias externas:
 - sAPI.h;
 - Usar delay no bloqueantes;

#### Modularización
![](https://github.com/lucascsd/Practica4/blob/main/image/Capas_Ejercicio4.svg)

###### Archivos de modularización
| File name | hearders                    |
| ------------- | ------------------------------ |
| [ejercicio4.c](https://github.com/lucascsd/Practica4/blob/main/src/ejercicio4.c)|[ejercicio4.h](https://github.com/lucascsd/Practica4/blob/main/inc/ejercicio4.h)|
| [semaforo.c](https://github.com/lucascsd/Practica4/blob/main/src/semaforo.c)|[semaforo.h](https://github.com/lucascsd/Practica4/blob/main/inc/semaforo.h)|
| [led.c](https://github.com/lucascsd/Practica4/blob/main/src/led.c)|[led.h](https://github.com/lucascsd/Practica4/blob/main/inc/led.h)|
| [teclas.c](https://github.com/lucascsd/Practica4/blob/main/src/teclas.c)|[teclas.h](https://github.com/lucascsd/Practica4/blob/main/inc/teclas.h)|

### Notas de compilación
Seleccionar el punto del ejercicio a compilar comentando o descomentando la macro correspondiente en el archivo [ejercicio4.h](https://github.com/lucascsd/Practica4/blob/main/inc/ejercicio4.h) 

