#include "Waveforms.h"
#include "sineWave.h"
#include "sawTooth.h"

char userInput;

void setup()
{
  analogWriteResolution(10);
  Serial.begin(9600); 
}

static __inline__ void syncDAC() __attribute__((always_inline, unused));
static void syncDAC() {
  while (DAC->STATUS.bit.SYNCBUSY == 1)
    ;
}

// Can create wave.h file

void loop(){
  int i = 0;
  int value = 0;
  int wave = 0;
    if(Serial.available() > 0){
      userInput = Serial.read();
      
      if(userInput == 's'){
      
          while(1){
            value = sinewave[i]; // use sinewave for the reference lookup table, or sine for the one created in python
            syncDAC();
            DAC->DATA.reg = value & 0x3FF;  // DAC on 10 bits.  // This is a mask - RJ
            syncDAC();
            DAC->CTRLA.bit.ENABLE = 0x01;     // Enable DAC // This enables the output - RJ
            syncDAC();                                  
            i = i + 1;
            if(i == 256){
              i = 0;
            } // if reset index 
          } // while true loop
          
      } // if 's' loop

      if(userInput == 't'){
        while(1){
          value = sinewave[i];
          analogWrite(A0,value);
          
          i = i + 1;
          if(i == 256){
            i = 0;
          } // if reset index 
        } // if 't' loop
      } // while true
    } // Serial.available
} // main loop
