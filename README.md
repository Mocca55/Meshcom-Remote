# Meshcom-Remote
Meshcom RX Remote Admin

Arduino Programm für einen Arduino Micro Pro oder anderen Mikrocontroller gleicher Bauart.

Es ist möglich einen Lora ESP32 (Lilygo Lora T3 V1.6.1 getestet) aus der ferne via HF zu Administrieren.
Es wird der TX Pin vom Lora ESP32 ausgelesen.

Damit alles funktioniert wird der 3V und Ground Pin vom LoraESP32 zur Stromversorgung des Arduino Micro Pro genutzt.
Zusätzlich wird der TX Pin vom LoraESP32 mit dem RX Pin des Arduino Micro Pro verbunden.
Zum Triggern des Reboots wird der RST Pin vom Lora32ESP mit dem Pin7 des Arduino Micro Pro verbunden.

LEDs RX / TX / Power 
RX LED befindet sich beim PIN7 auf dem Board
TX-LED befindet sich bei Pin14 auf dem Board
Power LED befindet sich beim USB Anschluss auf dem Board

Die Board LEDs blinken je nach Aktion:
RX Lora Paket -> RX-LED 1x kurz blinken
TX Lora PAket -> TX-LED 1x kurz blinken
Node Remotereboot -> RX-LED 2x kurz blinken
Node erfolgreich gestartet -> RX-LED 3x kurz blinken



Folgende Befehle können via HF an den Node gesendet werden

remotereboot -> Startet den Lora ESP via RST Pin am LoraESP32 neu.



Pinbelegung

    ARDUINO PRO MICRO (5V)                   LILYGO LoRa32 (3.3V)
  +-----------------------+               +-----------------------+


  | [TX1] Pin (1) --------|---[ 3k Ohm ]-----> [RX] Pin           |
  |                       |               |                       |
  | [RX1] Pin (0) <-------|------------------- [TX] Pin           |
  |                       |               |                       |
  | [Pin 7] --------------|------------------> [RST] Pin          |
  |                       |               |                       |
  | [GND] Pin ------------|------------------- [GND] Pin          |
  |                       |               |                       |
  | [VCC] Pin <-----------|------------------- [3V3] Pin          |
  |                       |               |                       |
  +-----------------------+               +-----------------------+

