#include "sineLookup.h"

char userInput;

void setup()
{
  analogWriteResolution(10);                // Set DAC output resolution to 10 bits
  Serial.begin(9600);                       // Initialize serial communication
}

static __inline__ void syncDAC() __attribute__((always_inline, unused));
static void syncDAC() {
  while (DAC->STATUS.bit.SYNCBUSY == 1)     // Check DAC Status register 
    ;
}

char selectSpeedTest(){
  Serial.println("Which speed test would you like to run?");
  char userInputSpeed;
  while(1){
    if(Serial.available() > 0){
      userInputSpeed = Serial.read();
      if((userInputSpeed == '1')||(userInputSpeed == '2')||(userInputSpeed == '3')||(userInputSpeed == '4')){
        Serial.println(userInputSpeed);
        return userInputSpeed;
      }
      else{
        Serial.println("Please Enter a value of 1 to 4!");
      }
    }
  }
}
void loop(){
  int i = 0;
  int value = 0;
  
    if(Serial.available() > 0){
      userInput = Serial.read();

     if(userInput == 'b'){
        while(1){
          value = sinewave[i];              // Use lookup table
          analogWrite(A0,value);            
          
          i = i + 1;
          if(i == 256){                     // Loop through lookup table & reset index at end
            i = 0;
          }
        } 
      } // if user selects 'b' - default analogWrite() 
      
      if(userInput == 's'){
        char userSpeedTestType;
        Serial.println("Getting userInput");
        userSpeedTestType = selectSpeedTest();
        Serial.println("Got speedtest vaule");
        Serial.println(userSpeedTestType);
        if(userSpeedTestType == '1'){
            while(1){
              value = sinewave[i];            // Use lookup table for sine wave values 
              syncDAC();
              DAC->DATA.reg = value & 0x3FF;  // This is a mask for the 10 bits of Data value for the DAC
              syncDAC();                      
              DAC->CTRLA.bit.ENABLE = 0x01;   // This enables the DAC output
              syncDAC();
                                                
              i = i + 1;
              if(i == 256){                   // Loop through lookup table & reset index at end
                i = 0;
              }
           } // while True                                
          } // if user '1' - using all syncDAC()

        if(userSpeedTestType == '2'){
            while(1){
              value = sinewave[i];            // Use lookup table for sine wave values 
              syncDAC();
              DAC->DATA.reg = value & 0x3FF;  // This is a mask for the 10 bits of Data value for the DAC
              syncDAC(); 
              DAC->CTRLA.bit.ENABLE = 0x01;   // This enables the DAC output
              //syncDAC();
                                                
              i = i + 1;
              if(i == 256){                   // Loop through lookup table & reset index at end
                i = 0;
              }
           } // while True                                
          } // if user '2' - removing last syncDAC()

        if(userSpeedTestType == '3'){
            while(1){
              value = sinewave[i];            // Use lookup table for sine wave values 
              //syncDAC();
              DAC->DATA.reg = value & 0x3FF;  // This is a mask for the 10 bits of Data value for the DAC
              syncDAC(); 
              DAC->CTRLA.bit.ENABLE = 0x01;   // This enables the DAC output
              //syncDAC();
                                                
              i = i + 1;
              if(i == 256){                   // Loop through lookup table & reset index at end
                i = 0;
              }
           } // while True                                
          } // if user '3' - synchDAC() after value is write to data register

        if(userSpeedTestType == '4'){
            while(1){
              value = sinewave[i];            // Use lookup table for sine wave values 
              //syncDAC();
              DAC->DATA.reg = value & 0x3FF;  // This is a mask for the 10 bits of Data value for the DAC
              //syncDAC(); 
              DAC->CTRLA.bit.ENABLE = 0x01;   // This enables the DAC output
              //syncDAC();
                                                
              i = i + 1;
              if(i == 256){                   // Loop through lookup table & reset index at end
                i = 0;
              }
             } // while True                                
          } // if user '4' - removing all syncDAC()
          
        } // if user selects 's'                                 
      } // main if Serial.available                                     
    } // void loop 
