#include <SoftwareSerial.h>

#define tonePin 12
boolean led = true;

void setup()
{
  pinMode(tonePin, OUTPUT);  // Ausgabe LED festlegen
  Serial.begin(9600);
  // Timer 1
  noInterrupts();           // Alle Interrupts temporär abschalten
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 154;
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS22);
  TIMSK2 |= (1 << OCIE1A);  
  interrupts();             
}

ISR(TIMER2_COMPA_vect)        
{
  TCNT2 = 0;    
  led = not led;
  digitalWrite(tonePin, led);
  // LED ein und aus
}

void loop()
{
  // Wir könnten hier zusätzlichen Code integrieren
}