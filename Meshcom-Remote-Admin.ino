const int resetPin = 7;

// RX Befehle und Status Infos
const char* cmdReboot = "CALL-1>CALL-2:remotereboot"; //Amateurfunk CALL Sender und Empfänger einsetzen
const char* cmdStarted = "CLIENT STARTED";

// Befehle definieren für Prgramm
int posReboot = 0;
int posStarted = 0;

void setup() {
  // Baudrate muss gleich sein bei Serial und Serial1 (ESP32 115200)
  Serial.begin(115200);
  Serial1.begin(115200);

  pinMode(resetPin, OUTPUT);
  digitalWrite(resetPin, HIGH);

  while (!Serial);
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
      }
    } else {
      posStarted = (c == cmdStarted[0]) ? 1 : 0;
    }
  }
}

void executeReset() {
  Serial.println("\n----------\n[Info Arduino] Lora Remotereboot Befehl erkannt der Reset-Impuls wird ausgelöst!\n----------");
  digitalWrite(resetPin, LOW);
  delay(100);
  digitalWrite(resetPin, HIGH);
  // Nach Reset kurz warten, um Datenmüll während des Neustarts zu ignorieren
  posReboot = 0;
  posStarted = 0;
}
