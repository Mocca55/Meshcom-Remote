// RX TX LEDs schaltbar machen

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

// RX Befehle und Status Infos
const char* cmdReboot = "CALL-1>CALL-2:remotereboot";  //hier müssen die Rufzeichen der Meshcom Nodes eingetragen werden Rufzeichen 1 Sender Rufzeichen 2 Empfänger (zu Administrierender Node)
const char* cmdStarted = "CLIENT STARTED";
const char* cmdRXLED = "RX-LoRa2";
const char* cmdTXLED = "TX-LoRa";

// Befehle definieren für Prgramm
int posReboot = 0;
int posStarted = 0;
int posRXLED = 0;
int posTXLED = 0;

void setup() {


// LEDs abschalten
  delay(500);
  ledTx( false);
  delay(500);
  ledRx( false);


  // Baudrate muss ggleich sein bei Serial und Serial1 (ESP32 115200)
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  //while (!Serial); //abschalten bei Nutzung ohne PC
  Serial.println("[Info Arduino] Überwachung aktiv (RX Pin vom Lilygo Lora32 ESP wird ausgelesen)...");
}

void loop() {
  // Verarbeitund der Werte
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
      // Falls Zeichen nicht passt, zurücksetzen (oder auf Anfang prüfen)
      posReboot = (c == cmdReboot[0]) ? 1 : 0;
    }

    // 3. Prüfung auf "CLIENT STARTED"
    if (c == cmdStarted[posStarted]) {
      posStarted++;
      if (cmdStarted[posStarted] == '\0') {
        Serial.println("\n----------\n[Info Arduino] Lora ESP32 Node gestartet und bereit.\n----------");
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
  digitalWrite(resetPin, LOW);
  delay(100);
  digitalWrite(resetPin, HIGH);
          ledRx( true);
          delay(200);
          ledRx( false);
          delay(200);
          ledRx( true);
          delay(200);
          ledRx( false);
  // Nach Reset kurz warten, um Datenmüll während des Neustarts zu ignorieren
  posReboot = 0;
  posStarted = 0;
}
