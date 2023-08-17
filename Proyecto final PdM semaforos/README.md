# Proyecto Semáforo Inteligente

![Semáforo](link_to_image)

## Descripción

¡Bienvenido al proyecto del Semáforo Inteligente! En este emocionante proyecto, hemos creado un sistema de semáforo avanzado utilizando tecnologías de microcontroladores y programación en C. Este semáforo no es solo un sistema de control de tráfico básico, ¡es inteligente y receptivo a su entorno!

## Características Destacadas

- **Secuencia Dinámica:** A diferencia de los semáforos tradicionales, nuestro semáforo inteligente ajusta su secuencia de luces en tiempo real según las condiciones de tráfico y el comportamiento del usuario.

- **Botón Interactivo:** Hemos incorporado un botón interactivo que permite a los usuarios influir en la secuencia de semáforo. ¡Presionar el botón cambia instantáneamente la fase actual de los semáforos!

- **Comunicación Serial:** Implementamos una comunicación serial a través del puerto UART, lo que permite la interacción con el sistema y la visualización de mensajes a través de una interfaz de terminal.

## Máquinas de Estados Finitos

El corazón del funcionamiento de nuestro Semáforo Inteligente es la implementación de máquinas de estados finitos (MEFs). Estas MEFs son esenciales para el control preciso de la secuencia de luces y la interacción con el botón. 

### MEF de Secuencia de Semáforos

La MEF de Secuencia de Semáforos controla el ciclo de cambio de luces entre los semáforos 1 y 2. Se basa en los tiempos predefinidos para cada estado (rojo, amarillo, verde) y cambia de estado después de alcanzar el tiempo correspondiente. Esta MEF asegura que los semáforos cambien en sincronización.

### MEF de Interacción con el Botón

La MEF de Interacción con el Botón monitorea el estado del botón interactivo. Detecta si el botón ha sido presionado o liberado y actúa en consecuencia. Si el botón se presiona, la MEF cambia la fase actual de ambos semáforos a amarillo, creando una fase de precaución. Esta MEF garantiza una respuesta rápida y precisa al botón del usuario.

## Configuración y Uso

1. **Herramientas Necesarias:** Asegúrate de tener acceso a las herramientas de desarrollo necesarias, como el entorno de desarrollo integrado y las bibliotecas requeridas.

2. **Conexiones de Hardware:** Asegúrate de conectar correctamente los componentes según el esquema de conexiones proporcionado en el proyecto.

3. **Cargar el Código:** Carga el código fuente proporcionado en tu microcontrolador utilizando las herramientas de programación adecuadas.

4. **Interacción:** Observa cómo el semáforo sigue su secuencia y reacciona al botón interactivo. Utiliza la comunicación serial para ver los mensajes informativos.

## Contribuciones

Siéntete libre de contribuir a este proyecto. Puedes agregar nuevas funciones, mejorar la eficiencia del código o realizar ajustes en la secuencia de luces o en las MEFs. ¡Esperamos ver tus contribuciones!

## Créditos

Este proyecto fue desarrollado por [Tu Nombre] como parte del trabajo final para [Nombre del Curso o Asignatura]. Agradecemos a [Profesor/Instructor] por su orientación y apoyo durante el proceso de desarrollo.
