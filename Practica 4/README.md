# Práctica 4: MEF Anti-rebote por Software

## Objetivo
El objetivo de esta práctica es implementar una MEF (Máquina de Estados Finitos) para trabajar con anti-rebotes por software en la placa NUCLEO-F429ZI. Se utilizará un LED para mostrar el estado y una tecla para generar acciones o eventos ante un flanco descendente o ascendente.

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
