#include "config.h"
#include "BoardLEDs.h"

//Pin am Arduino Micro Pro zuweisen um den ESP RST Pin zu Triggern -> Pin7
const int resetPin = 7;


// RX und TX Befehle und Status Infos definieren
String cmdRebootConfig = MainNode + ">" + RemoteNode + ":remotereboot";  //Zusammensetzen der Reboot Infos aus den Call Strings
String cmdSendPosConfig = MainNode + ">" + RemoteNode + ":sendpos";  //Zusammensetzen SendPos -> Bake Senden mit Position
String NodeRestartInfo = "::{" + MainNode + "}" + RemoteNode + " wurde erfolgreich neugestartet."; //Zusammensetzen der Neustart TX Nachricht

const char* cmdReboot = cmdRebootConfig.c_str();
const char* cmdSendPos = cmdSendPosConfig.c_str();
const char* cmdStarted = "CLIENT STARTED";  // Prüfen oder der Node erfolgreich gestartet ist
const char* cmdRXLED = "RX-LoRa2"; // RX LED funktion beim Empfang kurz blinken
const char* cmdTXLED = "TX-LoRa"; // TX LED beim Senden kurz blinken

// Variable der Befehle definieren
int posReboot = 0;
int posStarted = 0;
int posRXLED = 0;
int posTXLED = 0;
int posSendPos = 0;


void setup() {


// Arduino Pro Micro Board-LEDs abschalten zum Energie Sparen und um die Funktionen RX TX LEDs zu nutzen
  delay(500);
  ledTx( false);
  delay(500);
  ledRx( false);
  

// Seial Baudrate definieren, muss gleich sein bei Serial und Serial1 für Meshcom wir 115200 verwendet
  Serial.begin(115200); //Baudrate für USB
  Serial1.begin(115200); //Baudrate für den RX / TX Pin auf dem Board

  Serial1.println("--Display off"); //Display aus zum Energie sparen

  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  //while (!Serial); //Warten auf Serial USB VErbindung -> ---------- Achtung bei Nutzung ohne PC muss es auskommentiert werden ----------
  Serial.println("\n\n----------\n[Info Arduino] Überwachung aktiv " + RemoteVersion + " (RX Pin vom Lilygo Lora32 ESP wird ausgelesen)\n----------\n\n");
}

void loop() {
  // Verarbeitung der RX Befehle
  while (Serial1.available() > 0) {
    char c = (char)Serial1.read();
    
    // 1. Sofortige Weiterleitung (Serial.write ist schneller als .print)
    Serial.write(c);

    // 2. Prüfung auf "remotereboot"
    if (c == cmdReboot[posReboot]) {
      posReboot++;
      if (cmdReboot[posReboot] == '\0') {
        executeReset();
        posReboot = 0;
      }
    } else {
      // Falls nicht erkannt, zurücksetzen
      posReboot = (c == cmdReboot[0]) ? 1 : 0;
    }

    // 3. Prüfung auf "CLIENT STARTED"
    if (c == cmdStarted[posStarted]) {
      posStarted++;
      if (cmdStarted[posStarted] == '\0') {
        Serial.println("\n----------\n[Info Arduino] Lora ESP32 Node gestartet und bereit.\n----------"); //Beim erfolgreichem Start des lora Nodes Blinkt das RX LED 3x kurz
        Serial.println(RemoteVersion);
        posStarted = 0;
          ledRx( true);
          delay(200);
          ledRx( false);
          delay(200);
          ledRx( true);
          delay(200);
          ledRx( false);
          delay(200);
          ledRx( true);
          delay(200);
          ledRx( false);
      }
    } else {
      posStarted = (c == cmdStarted[0]) ? 1 : 0;
    }

    //4. RX LED bei Empfang leuchten "RX-LoRa2"
    if (c == cmdRXLED[posRXLED]) {
      posRXLED++;
      if (cmdRXLED[posRXLED] == '\0') {
        //Serial.println("\n----------\n[Info Arduino] RX Lora Paket.\n----------");  //Aktivieren für eine RX Info Anzeige via Serial
        posRXLED = 0;
          ledRx( true);
          delay(300);
          ledRx( false);
          delay(5000); //Zum Energie Sparen Display nach 5 Sek aus
          Serial1.println("--Display off"); //Zum Energie Sparen Display aus
      }
    } else {
      posRXLED = (c == cmdRXLED[0]) ? 1 : 0;
    }

    //5. TX LED bei Senden leuchten "TX-LoRa"
    if (c == cmdTXLED[posTXLED]) {
      posTXLED++;
      if (cmdTXLED[posTXLED] == '\0') {
        //Serial.println("\n----------\n[Info Arduino] TX Lora Paket.\n----------");  //Aktivieren für eine TX Info Anzeige via Serial
        posTXLED = 0;
          ledTx( true);
          delay(500);
          ledTx( false);
      }
    } else {
      posTXLED = (c == cmdTXLED[0]) ? 1 : 0;
    }


        //5. Manuelles aussende der Position -> SendPos
    if (c == cmdSendPos[posSendPos]) {
      posSendPos++;
      if (cmdSendPos[posSendPos] == '\0') {
        //Serial.println("\n----------\n[Info Arduino] TX SendPos\n----------");  //Aktivieren für eine SendPos Info Anzeige via Serial
        posSendPos = 0;
          ledTx( true);
          ledRx( true);
          delay(200);
          ledTx( false);
          ledRx( false);
          delay(200);
          ledTx( true);
          ledRx( true);
          delay(200);
          ledTx( false);
          ledRx( false);
          Serial1.println("--sendpos");//Sende den Serial Befehl --sendpos
          //delay(1000); //Zum Energie Sparen Display nach 1 Sek aus
          //Serial1.println("--Display off"); //Zum Energie Sparen Display aus
      }
    } else {
      posSendPos = (c == cmdSendPos[0]) ? 1 : 0;
    }

  }
}

void executeReset() {
  Serial.println("\n----------\n[Info Arduino] Lora Remotereboot Befehl erkannt der Reset-Impuls wird ausgelöst!\n----------");
  digitalWrite(resetPin, LOW); //Reboot via Pin 7
  delay(100); //Reboot via Pin 7
  digitalWrite(resetPin, HIGH); //Reboot via Pin 7
  //Serial1.println("--reboot"); //Alternativ kann der Node auch via Serialbefehl neu gestartet werden
          ledRx( true);
          delay(200);
          ledRx( false);
          delay(200);
          ledRx( true);
          delay(200);
          ledRx( false);
  // Nach Reset kurz warten, um fehlerhaftes lesen des RX Pins während des Neustarts zu ignorieren
  posReboot = 0;
  posStarted = 0;
  delay(15000);
  Serial1.println(NodeRestartInfo.c_str());
}
