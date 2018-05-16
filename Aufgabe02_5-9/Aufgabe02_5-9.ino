#include <SoftwareSerial.h>

#define tonePin 12
boolean led = true;
int prescalers[7] = {1, 8, 32, 64, 128, 256, 1024};

void setup(){
  Serial.begin(9600);
  pinMode(tonePin, OUTPUT);
}


// Excercise 5
void tone100Hz() {
  noInterrupts();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 154;
  TCCR2B |= (1 << CS21);
  TCCR2B |= (1 << CS22);
  TIMSK2 |= (1 << OCIE1A);  
  interrupts();             
}


// Excercise 6
void toneAdjustableFreq(int freq) {
  noInterrupts();
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  TIMSK2 |= (1 << OCIE1A);
  for (int i = 0; i < 7; i++) {
    int result = round( (8000000 / (prescalers[i] * freq)) - 1);
    if (result < 256) {
      OCR2A = result;
      switch (prescalers[i]) {
        case (1):
        Serial.println("yooffo");
          break;
        case (8):
        Serial.println("yooasdfo");
          TCCR2B |= (1 << CS21);
          break; 
        case (32):
        Serial.println("yoooahgrae");
          TCCR2B |= (1 << CS20);
          TCCR2B |= (1 << CS21);
          break; 
        case (64):
       Serial.println("yoooaregr");
          TCCR2B |= (1 << CS22);
          break; 
        case (128):
        Serial.println("yooargeg");
          TCCR2B |= (1 << CS20);
          TCCR2B |= (1 << CS22);
          break; 
        case (256):
       Serial.println("yoooa43r");
          TCCR2B |= (1 << CS21);
          TCCR2B |= (1 << CS22);
          break; 
        case (1024):
          Serial.println("yooo3");
          TCCR2B |= (1 << CS20);
          TCCR2B |= (1 << CS21);
          TCCR2B |= (1 << CS22);
          break; 
        }
      break;
      }
    }
    interrupts();
  }


// Interrupt
ISR(TIMER2_COMPA_vect) {
  TCNT2 = 0;  
  led = not led;
  digitalWrite(tonePin, led);
  }


void loop()
{
  
}
