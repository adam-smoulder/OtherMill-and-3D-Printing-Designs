/*
Capacitive Synth project by Other Machine Co. http://othermachine.co
Capacitive touch code from http://playground.arduino.cc/Code/CapacitiveSensor
Tone code from http://arduino.cc/en/reference/tone

This project plays notes using the basic tone function. There are many different
ways to configure how the keys work. The default is a (sort of) pentatonic scale
for the right keys that changes depending on which of the left keys is held down.

In the main loop function below, you can change how the keys behave by uncommenting
different functions. If you know basic programming, you can write your own!

Once you build the project, you need to hook it up to some kind of speaker that has
a 3.5mm plug (aka 1/8" or iPod plug). This could be your computer speakers, a portable
speaker, your car stereo, or even a home theater system that has an auxiliary 3.5mm cable.

We advise you NOT to use this device with headphones, unless your headphones have a 
volume control, as the signal is very loud.

*/

#include "pitches.h"

int notelength  = 20;
int outputpin   = 9;
int capacitance = 1;

void setup(void)
{  
  tone(outputpin, NOTE_A4, 500); //beep and flash to show that the device is working
}

/////////////////////////////////////////////////////////////////////////////////////
void loop(void)
{
//  choose how you want the keys to behave by changing which function is uncommented

  pentatonic();   //right keys play pentatonic scale based on left key held
//  aeoliancap();   //full Am scale
//  aeolianbt();    //bass and treble pentatonic
}
/////////////////////////////////////////////////////////////////////////////////////

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher
#include "pins_arduino.h" // Arduino pre-1.0 needs this
uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  // Prevent the timer IRQ from disturbing our measurement
  noInterrupts();
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
       if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // End of timing-critical section
  interrupts();

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

void aeoliancap(void)
{
  if(readCapacitivePin(6) > capacitance)   {tone(outputpin, NOTE_A4, notelength);}
  if(readCapacitivePin(5) > capacitance)   {tone(outputpin, NOTE_B4, notelength);}
  if(readCapacitivePin(4) > capacitance)   {tone(outputpin, NOTE_C5, notelength);}
  if(readCapacitivePin(3) > capacitance)   {tone(outputpin, NOTE_D5, notelength);}
  if(readCapacitivePin(2) > capacitance)   {tone(outputpin, NOTE_E5, notelength);}
  if(readCapacitivePin(7) > capacitance)   {tone(outputpin, NOTE_F5, notelength);}
  if(readCapacitivePin(8) > capacitance)   {tone(outputpin, NOTE_G5, notelength);}
  if(readCapacitivePin(10) > capacitance)  {tone(outputpin, NOTE_A5, notelength);}
  if(readCapacitivePin(11) > capacitance)  {tone(outputpin, NOTE_B5, notelength);}
  if(readCapacitivePin(12) > capacitance)  {tone(outputpin, NOTE_C6, notelength);}
}

void aeolianbt(void)
{
  if(readCapacitivePin(6) > capacitance)    {tone(outputpin, NOTE_A1, notelength);}
  if(readCapacitivePin(5) > capacitance)    {tone(outputpin, NOTE_C2, notelength);}
  if(readCapacitivePin(4) > capacitance)    {tone(outputpin, NOTE_E2, notelength);}
  if(readCapacitivePin(3) > capacitance)    {tone(outputpin, NOTE_G2, notelength);}
  if(readCapacitivePin(2) > capacitance)    {tone(outputpin, NOTE_A2, notelength);}
  if(readCapacitivePin(7) > capacitance)    {tone(outputpin, NOTE_A4, notelength);}
  if(readCapacitivePin(8) > capacitance)    {tone(outputpin, NOTE_C5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_E5, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_G5, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_A5, notelength);}
}

void pentatonic(void) {
  if(readCapacitivePin(6) > capacitance)   {amscale();}
  if(readCapacitivePin(5) > capacitance)   {dmscale();}
  if(readCapacitivePin(4) > capacitance)   {e7scale();}
  if(readCapacitivePin(3) > capacitance)   {fscale();}
  if(readCapacitivePin(2) > capacitance)   {gscale();}
}

void amscale(void) {
  if(readCapacitivePin(7) > capacitance)    {tone(outputpin, NOTE_A4, notelength);}
  if(readCapacitivePin(8) > capacitance)    {tone(outputpin, NOTE_C5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_E5, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_G5, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_A5, notelength);}
}

void dmscale(void) {
  if(readCapacitivePin(7) > capacitance)    {tone(outputpin, NOTE_D5, notelength);}
  if(readCapacitivePin(8) > capacitance)    {tone(outputpin, NOTE_F5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_A5, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_C6, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_D6, notelength);}
}

void e7scale(void) {
  if(readCapacitivePin(7) > capacitance)    {tone(outputpin, NOTE_E5, notelength);}
  if(readCapacitivePin(8) > capacitance)    {tone(outputpin, NOTE_GS5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_B5, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_D6, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_E6, notelength);}
}

void cscale(void) {
  if(readCapacitivePin(7) > capacitance)    {tone(outputpin, NOTE_C5, notelength);}
  if(readCapacitivePin(8) > capacitance)    {tone(outputpin, NOTE_E5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_G5, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_B5, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_C6, notelength);}
}

void fscale(void) {
  if(readCapacitivePin(7) > capacitance)   {tone(outputpin, NOTE_F5, notelength);}
  if(readCapacitivePin(8) > capacitance)   {tone(outputpin, NOTE_A5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_C6, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_E6, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_F6, notelength);}
}

void gscale(void) {
  if(readCapacitivePin(7) > capacitance)   {tone(outputpin, NOTE_G5, notelength);}
  if(readCapacitivePin(8) > capacitance)   {tone(outputpin, NOTE_B5, notelength);}
  if(readCapacitivePin(10) > capacitance)   {tone(outputpin, NOTE_D6, notelength);}
  if(readCapacitivePin(11) > capacitance)   {tone(outputpin, NOTE_F6, notelength);}
  if(readCapacitivePin(12) > capacitance)   {tone(outputpin, NOTE_G6, notelength);}
}




