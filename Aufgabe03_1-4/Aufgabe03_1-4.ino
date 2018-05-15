// Copyright 2015: Jan Burchard
// HWP Code: Low level ADC

void setup() {
  float time1 = millis();
  for (int x = 1; x <= 100000; x++) {
    setPin11(true);
    setPin11(false);
    }
  time1 = millis() - time1;

  float time2 = millis();
  for (int x = 1; x <= 100000; x++) {
    setPin11Asm(true);
    setPin11Asm(false);
    }
  time2 = millis() - time2;

  float time3 = millis();
  for (int x = 1; x <= 100000; x++) {
    digitalWrite(11, HIGH);
    digitalWrite(11, LOW);
    }
  time3 = millis() - time3;
}

void loop() {

}

// Excercise 1
void setPin11(boolean high) {
    if (high) {
      PORTB |= (1 << 3);
    }else {
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
   }else {
     asm (
     "cbi %0, %1 \n"
     : : "I" (_SFR_IO_ADDR(PORTB)), "I" (PORTB3)
     );
   }
  }
