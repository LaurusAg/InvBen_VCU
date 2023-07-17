# InvBen_VCU

Desarrolado para microcontrolador ESP8266.
-



# Código fuente y headers:
-
- Connect.cpp: Incluye las funciones setup_wifi, setup_mqtt, reconnect y callback. Con ellas nos aseguramos de realizar la conexion a wifi, al servidor mqtt, reconexion y mantenimiento.
- delay.cpp: Incluye las funciones start, isExpired, reset. Funciones utiles para realizar un manejo temporizado de sensado y envío de datos sin hacer uso de funciones bloqueantes.
- sensor.cpp: Incluye sensorFilter (filtro de aproximacion media), errorHandler (aviso de errores en mediciones), publishSensorValues (publicacion de datos).
