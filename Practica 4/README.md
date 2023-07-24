# Práctica 4: MEF Anti-rebote por Software

## Objetivo
El objetivo de esta práctica es implementar una MEF (Máquina de Estados Finitos) para trabajar con anti-rebotes por software en la placa STM 32 NUCLEO-F401RE. Se utilizará un o dos LEDs para mostrar el estado y una tecla para generar acciones o eventos ante un flanco descendente o ascendente.

![IMG20230709235003](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/848a920e-da77-4699-83e7-abf5e1e5b91c)


## Punto 1: Implementación de la MEF Anti-rebote en main.c
1. Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.
2. Implementar una MEF anti-rebote que permita leer el estado del pulsador de la placa NUCLEO-F429ZI y generar acciones ante un flanco descendente o ascendente, según el siguiente diagrama:

![MEF Diagram](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/cbd41b41-f591-4ac2-ba54-c7b0e47fe377)

3. El estado inicial de la MEF debe ser BUTTON_UP.
4. Implementar las siguientes funciones dentro de "main.c":
   ```c
   void debounceFSM_init();    // debe cargar el estado inicial
   void debounceFSM_update();  // debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
   void buttonPressed();       // debe invertir el estado del LED1
   void buttonReleased();      // debe invertir el estado del LED3

## Punto 2: Implementación del módulo de software API_debounce
1. Crear un nuevo proyecto como copia del proyecto con la implementación del punto 1 de la práctica 4.
2. Implementar un módulo de software en un archivo fuente "API_debounce.c" con su correspondiente archivo de cabecera "API_debounce.h" y ubicarlos en el proyecto dentro de las carpetas `/drivers/API/src` y `/drivers/API/inc`, respectivamente.

En **API_debounce.h**, ubicar los prototipos de las funciones públicas y las declaraciones:
```c
void debounceFSM_init();
void debounceFSM_update();
bool_t readKey();
```
3. La función readKey() debe leer una variable interna del módulo y devolver true o false si la tecla fue presionada. Si devuelve true, debe resetear (poner en false) el estado de la variable.

4. En API_debounce.c, ubicar las declaraciones privadas, los prototipos de las funciones privadas y la implementación de todas las funciones del módulo, privadas y públicas.

5. La declaración de debounceState_t debe ser privada en el archivo .c y la variable de estado de tipo debounceState_t debe ser global privada (con static).

6. Declarar una variable tipo bool_t global privada que se ponga en true cuando ocurra un flanco descendente y se ponga en false cuando se llame a la función readKey().

7. Implementar un programa que cambie la frecuencia de toggleo del LED2 entre 100 ms y 500 ms cada vez que se presione la tecla. El programa debe usar las funciones anti-rebote del módulo API_debounce y los retardos no bloqueantes del módulo API_delay.

## Conclusión 

Con esta práctica, se habrá implementado una MEF anti-rebote por software y se habrá creado un módulo de software reutilizable para trabajar con anti-rebotes en futuros proyectos con la placa NUCLEO-F429ZI. El uso de MEF y técnicas de anti-rebote permitirá tener un comportamiento más confiable y robusto en la lectura de pulsadores y el control de LEDs.


