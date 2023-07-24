# Punto 1: Implementación de una MEF Anti-rebote por Software

## Objetivo
El objetivo de este punto es implementar una MEF (Máquina de Estados Finitos) para trabajar con anti-rebotes por software en la placa NUCLEO-F401RE. Se utilizará dos LED para mostrar el estado y una tecla para generar acciones o eventos ante un flanco descendente o ascendente como se evudencia en el siguiente video:

https://github.com/Kzamudioq/PdM_workspace/assets/138271936/877fd9fa-adfd-44b5-9fd2-8a9f64bb42ad


## Estructura de la MEF
La MEF anti-rebote se implementará utilizando los siguientes estados:

![estados](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/25d3b435-9151-40aa-a613-eb9f44ab7e35)


- BUTTON_UP: Estado inicial de la MEF cuando el pulsador no está presionado.
- BUTTON_FALLING: Transición hacia este estado cuando se detecta un flanco descendente en el pulsador (pulsador presionado).
- BUTTON_DOWN: Estado cuando el pulsador está presionado, se ha registrado el evento y se espera el flanco ascendente.
- BUTTON_RAISING: Transición hacia este estado cuando se detecta un flanco ascendente en el pulsador (pulsador liberado).
  

La MEF se representará mediante un diagrama de estados con las transiciones entre ellos.

## Implementación en main.c
1. Crear un nuevo proyecto como copia del proyecto realizado para la práctica 3.
2. Implementar la MEF anti-rebote en el archivo "main.c" de acuerdo al siguiente imagen:

![Anti-rebotes con MEF](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/2f6c0794-4590-43ef-87e6-a1e6223f3177)


3. El estado inicial de la MEF debe ser BUTTON_UP.
4. Implementar las siguientes funciones dentro de "main.c":
   ```c
   void debounceFSM_init();    // debe cargar el estado inicial
   void debounceFSM_update();  // debe leer las entradas, resolver la lógica de transición de estados y actualizar las salidas
   void buttonPressed();       // debe invertir el estado del LED1
   void buttonReleased();      // debe invertir el estado del LED3
