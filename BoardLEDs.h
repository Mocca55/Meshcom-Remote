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
