# Práctica 5 - Punto 2: Implementación de la Detección de Flancos con UART y Anti-rebote

En este punto de la Práctica 5, se debe implementar un programa que utilice el módulo UART junto con el módulo de anti-rebote para informar al usuario cuando se producen los flancos ascendentes y descendentes. Además, se debe cambiar la frecuencia de toggleo del LED2 entre 100 ms y 500 ms cada vez que se presione la tecla, utilizando las funciones de anti-rebote del módulo `API_debounce` y los retardos no bloqueantes del módulo `API_delay`.

## Implementación del Módulo de Anti-rebote

Primero, se debe implementar un módulo de software en un archivo fuente `API_debounce.c` con su correspondiente archivo de cabecera `API_debounce.h`. Ambos archivos deben ubicarse en el proyecto dentro de las carpetas `/drivers/API/src` y `/drivers/API/inc`, respectivamente. Estas carpetas están destinadas a contener los archivos relacionados con los controladores de bajo nivel (drivers) utilizados en el proyecto.

En `API_debounce.h`, se deben ubicar los prototipos de las funciones públicas y las declaraciones:

```c
void debounceFSM_init();
void debounceFSM_update();

/* La función readKey debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada.  
Si devuelve true, debe resetear (poner en false) el estado de la variable. */
bool_t readKey();
```

En API_debounce.c, se deben ubicar las declaraciones privadas, los prototipos de las funciones privadas y la implementación de todas las funciones del módulo, privadas y públicas.

La declaración de debounceState_t debe ser privada en el archivo .c, y la variable de estado de tipo debounceState_t debe ser global privada (con static).

Se debe declarar una variable tipo bool_t global privada que se ponga en true cuando ocurra un flanco descendente y se ponga en false cuando se llame a la función readKey().

## Implementación del Programa Principal

Una vez implementado el módulo de anti-rebote, se debe desarrollar el programa principal que utiliza tanto el módulo UART como el módulo de anti-rebote.

El programa debe realizar las siguientes acciones:

1. Inicializar la UART y el módulo de anti-rebote (debounceFSM_init()).
2. Configurar los LEDs adicionales para que se activen cuando ocurran flancos ascendentes y descendentes, respectivamente.
3. Configurar el LED2 para que realice un toggleo con una frecuencia inicial de 100 ms utilizando los retardos no bloqueantes del módulo API_delay.
4. Monitorear la tecla utilizando el módulo de anti-rebote. Cuando se presione la tecla y se detecte un flanco descendente, la variable global privada debe establecerse en true.
5. Si la variable global privada está en true, cambiar la frecuencia del toggleo del LED2 a 500 ms. Después de realizar el cambio, se debe restablecer la variable global privada a false.
6. Activar el LED correspondiente para visualizar el flanco ascendente o descendente, dependiendo del estado de la variable global privada.
7. Repetir los pasos 4, 5 y 6 cada vez que se presione la tecla y se detecte un flanco descendente.

## Consideraciones Finales

La implementación de este programa permitirá informar al usuario cuando se produzcan flancos ascendentes y descendentes al presionar la tecla, y los LEDs adicionales permitirán visualizar estos eventos. Además, el programa cambiará la frecuencia de toggleo del LED2 entre 100 ms y 500 ms cada vez que se presione la tecla, utilizando el módulo de anti-rebote y los retardos no bloqueantes.
