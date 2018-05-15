// Copyright 2015: Jan Burchard
// HWP Code: Low level ADC

void setup() {
  setPin11Asm(true);
  
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
