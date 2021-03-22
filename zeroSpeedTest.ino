#include "sineLookup.h"

char userInput;

void setup()
{
  analogWriteResolution(10);                // Set DAC output resolution to 8 bits
  Serial.begin(9600);                       // Initialize serial communication
}

static __inline__ void syncDAC() __attribute__((always_inline, unused));
static void syncDAC() {
  while (DAC->STATUS.bit.SYNCBUSY == 1)     // Check DAC Status register 
    ;
}

void loop(){
  int i = 0;
  int value = 0;
  
    if(Serial.available() > 0){
      userInput = Serial.read();

     if(userInput == 'b'){
        while(1){
          value = sinewave[i];              // Use lookup table
          analogWrite(A0,value);            // Use built in analogwirte function
          
          i = i + 1;
          if(i == 256){                     // Loop through lookup table & reset index at end
            i = 0;
          }
        } 
      } 
      
      if(userInput == 's'){
      
          while(1){
            value = sinewave[i];            // Use lookup table for sine wave values 
            syncDAC();
            DAC->DATA.reg = value & 0x3FF;  // This is a mask for the 8 bit Data value for the DAC
            syncDAC();
            DAC->CTRLA.bit.ENABLE = 0x01;   // This enables the DAC output
            syncDAC();
                                              
            i = i + 1;
            if(i == 256){                   // Loop through lookup table & reset index at end
              i = 0;
            }                                
          }                                 
      }                                     
    } 
} 
