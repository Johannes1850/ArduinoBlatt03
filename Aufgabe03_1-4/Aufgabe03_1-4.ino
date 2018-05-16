#include <SoftwareSerial.h>

// Copyright 2015: Jan Burchard
// HWP Code: Low level ADC

// Zu Aufgabe 3 : die setPin11 Funktion braucht mit 0.12 sek am kürzesten. Danach
// die setPin11Asm Funktion mit 0.13 sek, und mit Abstand am längsten braucht
// digitalWrite, mit 2 Sekunden

// Zu Aufgabe 4 : die nicht optimierte setPin12Asm Funktion braucht mit 1.16 sek am kürzesten. Danach
// die setPin12 Funktion mit 1.37 sek, und am längsten braucht
// digitalWrite, mit 1.8 Sekunden.

void setup() {
  timeTest();
}


void loop() {
}


// Excercise 1
void setPin11(boolean high) {
  if (high) {
    PORTB |= (1 << 3);
  } else {
    PORTB |= (0 << 3);
  }
}


// Excercise 2
void setPin11Asm(boolean high) {
  if (high) {
    asm (
      "sbi %0, %1 \n"
      : : "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB3)
    );
  } else {
    asm (
      "cbi %0, %1 \n"
      : : "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB3)
    );
  }
}


// Excercise 4 setPin12
void __attribute__((optimize("O0"))) setPin12(boolean high) {
  if (high) {
      PORTB |= (1 << 4);
    } else {
      PORTB |= (0 << 4);
    }
  }


// Excercise 4 setPin12Asm
void __attribute__((optimize("O0"))) setPin12Asm(boolean high) {
  if (high) {
    asm (
      "sbi %0, %1 \n"
      : : "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB4)
    );
  } else {
    asm (
      "cbi %0, %1 \n"
      : : "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB4)
    );
  }
 }


// Excercise 3
void timeTest() {
  Serial.begin(9600);
  double time1 = millis();
  for (long x = 1; x <= 100000; x++) {
    setPin11(true);
    setPin11(false);
  }
  time1 = millis() - time1;
  Serial.println("Time 1 optimized: " + String(time1/1000.0));
  double time2 = millis();
  for (long x = 1; x <= 100000; x++) {
    setPin11Asm(true);
    setPin11Asm(false);
  }
  time2 = millis() - time2;
  Serial.println("Time 2 optimized: " + String(time2/1000.0));
  double time3 = millis();
  for (long x = 1; x <= 100000; x++) {
    digitalWrite(11, HIGH);
    digitalWrite(11, LOW);
  }
  time3 = millis() - time3;
  Serial.println("Time 3 optimized: " + String(time3/1000.0));
  time1 = millis();
  for (long x = 1; x <= 100000; x++) {
    setPin12(true);
    setPin12(false);
  }
  time1 = millis() - time1;
  Serial.println("Time 1 not optimized: " + String(time1/1000.0));
  time2 = millis();
  for (long x = 1; x <= 100000; x++) {
    setPin12Asm(true);
    setPin12Asm(false);
  }
  time2 = millis() - time2;
  Serial.println("Time 2 not optimized: " + String(time2/1000.0));
  time3 = millis();
  for (long x = 1; x <= 100000; x++) {
    digitalWrite(12, HIGH);
    digitalWrite(12, LOW);
  }
  time3 = millis() - time3;
  Serial.println("Time 3 not optimized: " + String(time3/1000.0));
  }
