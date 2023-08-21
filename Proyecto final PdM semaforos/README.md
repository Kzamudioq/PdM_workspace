
![image](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/1f974980-4f7d-459e-9394-a240b6df2fda)

# Proyecto intersección semaforizada

https://github.com/Kzamudioq/PdM_workspace/assets/138271936/d22083ae-cab8-4b6e-b80a-3b24f6031ce1


## Descripción

¡Bienvenido al proyecto del Semáforo Inteligente! En este emocionante proyecto, hemos creado un sistema de semáforo avanzado utilizando tecnologías de microcontroladores y programación en C. Este semáforo no es solo un sistema de control de tráfico básico, ¡es inteligente y receptivo a su entorno!

## Componentes Hardware Utilizados

![image](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/fbc3e0a5-45ed-4bd5-9736-347dae7d77a5)


- 6 LEDs para representar las luces de los semáforos.
- 2 placas de semáforos Arduino para controlar los LEDs.
- Cables macho para las conexiones entre los componentes.
- Placa STM32 Nucleo F401RE para la lógica de control.

## Características Destacadas

- **Secuencia Dinámica:** A diferencia de los semáforos tradicionales, nuestro semáforo inteligente ajusta su secuencia de luces en tiempo real según las condiciones de tráfico y el comportamiento del usuario.

- **Botón Interactivo:** Hemos incorporado un botón interactivo que permite a los usuarios influir en la secuencia de semáforo. ¡Presionar el botón cambia instantáneamente la fase actual de los semáforos!

- **Comunicación Serial:** Implementamos una comunicación serial a través del puerto UART, lo que permite la interacción con el sistema y la visualización de mensajes a través de una interfaz de terminal.

## Máquinas de Estados Finitos

El corazón del funcionamiento de nuestro Semáforo Inteligente es la implementación de máquinas de estados finitos (MEFs). Estas MEFs son esenciales para el control preciso de la secuencia de luces y la interacción con el botón. 

### MEF de Secuencia de Semáforos

La MEF de Secuencia de Semáforos controla el ciclo de cambio de luces entre los semáforos 1 y 2. Se basa en los tiempos predefinidos para cada estado (rojo, amarillo, verde) y cambia de estado después de alcanzar el tiempo correspondiente. Esta MEF asegura que los semáforos cambien en sincronización.

![image](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/1ace1c23-2724-49d4-a5f1-a8eef378a4f7)


### MEF de Interacción con el Botón

La MEF de Interacción con el Botón monitorea el estado del botón interactivo. Detecta si el botón ha sido presionado o liberado y actúa en consecuencia. Si el botón se presiona, la MEF cambia la fase actual de ambos semáforos a amarillo, creando una fase de precaución. Esta MEF garantiza una respuesta rápida y precisa al botón del usuario.
![image](https://github.com/Kzamudioq/PdM_workspace/assets/138271936/1bc0ee31-5680-4248-9bb3-918cf02ebd3f)


## Exploración del Código

El archivo `main.c` contiene el código principal para el funcionamiento del semáforo inteligente. Aquí se inicializan las MEFs, se controlan los LEDs y se maneja la interacción con el botón y la comunicación serial.

- La función `api_semaforo_init()` inicializa los LEDs y realiza un efecto visual al encenderlos y apagarlos.
- `semaphore_controlLEDs()` controla los LEDs según los estados de los semáforos.
- `api_semaforo_update()` actualiza el estado de las MEFs y controla la lógica de cambio de estados y las transiciones.

## Estados, Eventos y Transiciones en las MEFs

- **MEF de Secuencia de Semáforos:**
  - Estados: Rojo, Amarillo, Verde.
  - Eventos: Paso del tiempo.
  - Transiciones: Rojo -> Amarillo -> Verde -> Amarillo.

- **MEF de Interacción con el Botón:**
  - Estados: Botón presionado, Botón liberado.
  - Eventos: Cambio de estado del botón.
  - Transiciones: Botón presionado -> Botón liberado (si se cumplen las condiciones).


## Configuración y Uso

1. **Herramientas Necesarias:** Asegúrate de tener acceso a las herramientas de desarrollo necesarias, como el entorno de desarrollo integrado y las bibliotecas requeridas.

2. **Conexiones de Hardware:** Conecta los LEDs, las placas de semáforos Arduino y el botón según el esquema de conexiones proporcionado en el proyecto.

3. **Cargar el Código:** Carga el código fuente proporcionado en tu microcontrolador STM32 Nucleo F401RE utilizando las herramientas de programación adecuadas.

4. **Interacción:** Observa cómo el semáforo sigue su secuencia y reacciona al botón interactivo. Utiliza la comunicación serial para ver los mensajes informativos.

## Contribuciones

Siéntete libre de contribuir a este proyecto. Puedes agregar nuevas funciones, mejorar la eficiencia del código o realizar ajustes en la secuencia de luces o en las MEFs. ¡Esperamos ver tus contribuciones!

## Créditos
Este proyecto fue desarrollado por Karen Tatiana Zamudio como parte del trabajo final para programacion de microcontroladores. Agradecemos a Patricio Bos por su orientación y apoyo durante el proceso de desarrollo.
