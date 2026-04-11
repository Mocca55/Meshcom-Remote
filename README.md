# Meshcom-Remote
Meshcom RX Remote Admin

Arduino Programm für einen Arduino Micro Pro oder anderen Mikrocontroller gleicher Bauart.

Es ist möglich einen Lora ESP32 (Lilygo Lora T3 V1.6.1 getestet) aus der ferne via HF zu Administrieren.
Es wird der TX Pin vom Lora ESP32 ausgelesen.

---------- WICHTIGE HINWEISE ----------

Wichtig am Lora Node müssen folgende Serial Ausgaben aktiviert werden (zum aktivieren folgende Commands in der Serial Console eingeben)
--softserread on

--loradebug on



!!! Wichtig beim Verbinden des TX vom Arduino Pro Micro mit dem RX Pin des Lilygo Lora 32 !!!
Hier muss zwischen TX und RX Pin ein 3k Ohm Wiederstand eingesetzt werden und auf den 3.3V Pegel zu kommen, da der Arduino mit 5V Pegel arbeitet.
Ohne Wiederstand Riskiert man eine Beschädigung des Lilygo Lora 32.

---------- ENDE DER WICHTIGEN HINWEISE ----------

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

       ARDUINO PRO MICRO                         LILYGO LoRa32 (ESP32)
    +-----------------------+                 +-----------------------+

    |                       |                 |                       |
    |      [ VCC ] Pin  <---|-----------------|--- [ 3V3 ] Pin        | (Power 3.3V vom Lora ESP32)
    |                       |                 |                       |
    |      [ GND ] Pin  ----|-----------------|--- [ GND ] Pin        | (gemeinsame Masse)
    |                       |                 |                       |
    |      [ TX1 ] (1)  ----|---[ 3k Ohm ]----|--> [ RX ]  Pin        | (Serial1 Senden (3.3V Pegel)
    |                       |                 |                       |
    |      [ RX1 ] (0)  <---|-----------------|--- [ TX ]  Pin        | (Serial Empfangen)
    |                       |                 |                       |
    |      [ Pin 7 ]    ----|-----------------|--> [ RST ] Pin        | (Hardware Reset)
    |                       |                 |                       |
    +-----------------------+                 +-----------------------+

