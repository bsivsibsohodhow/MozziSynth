

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <PinChangeInt.h>

#define PIN 4  // push button pin

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);


void setup(){
  aSin.setFreq(440);
  pinMode(PIN, INPUT);     //set the pin to input
  digitalWrite(PIN, HIGH); //use the internal pullup resistor
  PCintPort::attachInterrupt(PIN, changeFreq,RISING); // attach a PinChange Interrupt to our pin on the rising edge
  // and execute the function changeFreq when that pin changes
  startMozzi();
}



void updateControl(){
  // everything is done by the pinchange interrupt
}



void changeFreq()
{
  static int freq = 0;
  if (freq==0){
    freq=440;
  }
  else{
    freq=0;
  }
  aSin.setFreq(freq); // set the frequency
}



int updateAudio(){
  return aSin.next(); // return an int signal centred around 0
}



void loop(){
  audioHook(); // required here
}
