# InvBen_VCU
## Diagrama General
![image](https://github.com/LaurusAg/InvBen_VCU/assets/112956184/179796f9-37e7-41ea-9939-64df46fd6628)


## Descripción

InvBen_VCU (Ventilator Control Unit) es un proyecto de código abierto que se centra en el control de un ventilador mediante un microcontrolador ESP8266. El sistema toma lecturas de presión de un sensor Sensirion SDP2000-l y, según los valores medidos, controla la activación y desactivación de un ventilador de backup y su respectiva válvula, al ser activado inicia un timer y controla un ventilador de presurizacion interna si es necesario. Además, se comunica con un servidor central utilizando el protocolo MQTT para enviar lecturas de presión y estados del ventilador.

## Características clave

- Control del ventilador de backup y la válvula de presurización en función de las lecturas de presión.
- Control del ventilador de presurizacion interna en funcion del tiempo de funcionamiento del backup.
- Comunicación con un servidor central vía MQTT.
- Configuración flexible de umbrales de presión para activar y desactivar el ventilador.
- Modularización del código para facilitar la reutilización, escalabilidad y mantenimiento.

## Documentación

Para obtener información detallada sobre el hardware utilizado, el esquema de conexión y las instrucciones de instalación, consulta la [documentación completa](url/to/documentation).

## Instalación y Uso

1. Clona este repositorio en tu computadora local.
2. Configura el entorno de desarrollo y asegúrate de tener todas las bibliotecas requeridas.
3. Conecta el hardware según las especificaciones documentadas.
4. Abrir el proyecto dentro de Visual Studio Code de acuerdo a configuraciones de platform.io
5. Ajusta los valores de umbral de presión según tus necesidades en la función `logicProcess()` del archivo `logic_process.cpp`.
6. Asegúrate de tener el archivo `connect.h` con los datos de conexión a tu servidor MQTT.
7. Sube el código al microcontrolador ESP8266.
8. Observa las lecturas de presión y el estado del ventilador en la consola serie para corroborar funcionamiento.

## Estructura del Código

El código está organizado en diferentes archivos para mejorar su legibilidad y modularidad:

- `main.cpp`: Archivo principal que contiene las funciones `setup()` y `loop()`.
- `hal.h` y `hal.cpp`: Capa de Abstracción de Hardware (HAL) que maneja las operaciones de entrada/salida y configuraciones específicas del hardware.
- `logic.h` y `logic.cpp`: Contiene la función `logicProcess()` que controla el ventilador y la válvula de presurización según las lecturas de presión. Contiene funciones para leer las lecturas de presión desde el sensor Sensirion SDP2000-l, procesar sus datos y tomar decisiones.
- `sensor.h` y `sensor.cpp`: 
- `connect.h` y `connect.cpp`: Archivo de configuración con datos de conexión a tu servidor MQTT.Funciones de reconnect, handle y aviso de errores. Incluye funcion callback para subscripcion y proceso de texto. Contiene funcion publish de datos del ventilador y presion. 

## Contribuciones

--

