# Meshcom-Remote
Meshcom RX Remote Admin

Arduino Programm für einen Arduino Micro Pro oder anderen Mikrocontroller gleicher Bauart.

Es ist möglich einen Lora ESP32 (Lilygo Lora T3 V1.6.1 getestet) aus der ferne via HF zu Administrieren.
Es wird der TX vom Lora ESP32 ausgelesen.

Damit alles funktioniert wird der 3V und Ground Pin vom LoraESP32 zur Stromversorgung des Arduino Micro Pro genutzt.
Zusätzlich wird der TX Pin vom LoraESP32 mit dem RX Pin des Arduino Micro Pro verbunden.
Zum Triggern des Reboots wird der RST Pin vom Lora32ESP mit dem Pin7 des Arduino Micro Pro verbunden.

Folgende Befehle können via HF an den Node gesendet werden


remotereboot -> Startet den Lora ESP via RST Pin am LoraESP32 neu.



Pinbelegung

       LILYGO LoRa32 (ESP32)                   ARDUINO PRO MICRO
      +-----------------------+               +-----------------------+

      |                       |               |                       |
      |   [3V3] Pin ----------|-------------->| [VCC] Pin             | (Stromversorgung 3.3V)
      |                       |               |                       |
      |   [GND] Pin ----------|---------------| [GND] Pin             | (Gemeinsame Masse)
      |                       |               |                       |
      |   [TX]  Pin ----------|-------------->| [RX1] Pin (0)         | (Daten vom ESP lesen)
      |                       |               |                       |
      |   [RST] Pin <---------|---------------| [Pin 7]               | (Reset-Impuls auslösen)
      |                       |               |                       |
      +-----------------------+               +-----------------------+
