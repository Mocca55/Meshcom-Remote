// RX und TX LEDs auf dem Arduino Pro Micro Bpoard steuerbar machen

void ledTx( boolean on)
{
  if( on)
  {
    pinMode( LED_BUILTIN_TX, OUTPUT);    // TX LED an
    digitalWrite( LED_BUILTIN_TX, LOW);  // TX LED aus    
  }
  else
  {
    pinMode( LED_BUILTIN_TX, INPUT);
  }
}

void ledRx( boolean on)
{
  if( on)
  {
    pinMode( LED_BUILTIN_RX, OUTPUT);  // RX LED an
    digitalWrite( LED_BUILTIN_RX, LOW); // RX LED aus
  }
  else
  {
    pinMode( LED_BUILTIN_RX, INPUT);    
  }
}

//Reset Pin am Arduino Micro Pro zuweisen Pin7
const int resetPin = 7;


//---------- Setup Main und Remote Node --------- Hier müssen die Rufzeichen der Nodes Call1 Main Node und Call2 RemoteNode zu Administrierender Node eingetragen werden.
String MainNode = ("CALL-1");
String RemoteNode = ("CALL-2");




// RX und TX Befehle und Status Infos definieren
String cmdRebootConfig = MainNode + ">" + RemoteNode + ":remotereboot";  //Reboot Infos aus den Call Strings zusammenfügen

const char* cmdReboot = cmdRebootConfig.c_str();
const char* cmdStarted = "CLIENT STARTED";  // Prüfen oder der Node erfolgreich gestartet ist
const char* cmdRXLED = "RX-LoRa2"; // RX LED funktion beim Empfang kurz blinken
const char* cmdTXLED = "TX-LoRa"; // TX LED beim Senden kurz blinken

// Status der Befehle definieren
int posReboot = 0;
int posStarted = 0;
int posRXLED = 0;
int posTXLED = 0;

void setup() {


// Arduino Pro Micro Board-LEDs abschalten
  delay(500);
  ledTx( false);
  delay(500);
  ledRx( false);


  // Seial Baudrate definieren, muss gleich sein bei Serial und Serial1 für Meshcom wir 115200 verwendet
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  //while (!Serial); //Warten auf Serial USB VErbindung -> ---------- Achtung bei Nutzung ohne PC muss es auskommentiert werden ----------
  Serial.println("[Info Arduino] Überwachung aktiv (RX Pin vom Lilygo Lora32 ESP wird ausgelesen)...");
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
        Serial.println("\n----------\n[Info Arduino V1.0.2] Lora ESP32 Node gestartet und bereit.\n----------"); //Beim erfolgreichem Start des lora Nodes Blinkt das RX LED 3x kurz
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
          //delay(1000); //Zum Energie Sparen Display nach 1 Sek aus
          //Serial1.println("--Display off"); //Zum Energie Sparen Display aus
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
}
