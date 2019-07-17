/*
  %FIX Navigation Fix for ACQ

  Arduino to broadcast a nav fix every second via serial communication
  to a comm port on laptop and read by ACQ software and saved in journal.
  The serial string need to be 28 characters long and begin with %FIX. The 
  next 8 charcters is an int of fix number. The next 8 chars are a 8 wide
  float to 1 dec precision for SCX, easting in meters relative to wellhead. 
  The enxt 8 chars are a 8 wide float to 1 dec precision for SCY, northing 
  in meters relativee to wellhead.

  
  
  modified 15 July 2019
  Updated to take variables and display in correct 8 char width format.
  by Ben Sherwell
*/

#include <stdio.h> // for function sprintf

const int pinRH11 =  2;
const int pinRH12 =  3;
const int pinRH15 =  4;
const int pinGun =  5;
const int pinVib =  6;

int stateRH11 = 0;
int stateRH12 = 0;
int stateRH15 = 0;
int stateGun = 0;
int stateVib = 0;


void setup() {
  
  pinMode(pinRH11, INPUT_PULLUP);
  pinMode(pinRH12, INPUT_PULLUP);
  pinMode(pinRH15, INPUT_PULLUP);
  pinMode(pinGun, INPUT_PULLUP);
  pinMode(pinVib, INPUT_PULLUP);

  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {

  stateRH11 = digitalRead(pinRH11);
  stateRH12 = digitalRead(pinRH12);
  stateRH15 = digitalRead(pinRH15);
  stateGun = digitalRead(pinGun);
  stateVib = digitalRead(pinVib);

  if (stateGun == LOW && stateRH11 == LOW){
    Serial.println("Airgun, RH11");
  }
  if (stateGun == LOW && stateRH12 == LOW){
    Serial.println("Airgun, RH12");
  }
  if (stateGun == LOW && stateRH15 == LOW){
    Serial.println("Airgun, RH15");
  }
  if (stateVib == LOW && stateRH11 == LOW){
    Serial.println("Vibrator, RH11");
  }
  if (stateVib == LOW && stateRH12 == LOW){
    Serial.println("Vibrator, RH12");
  }
  if (stateVib == LOW && stateRH15 == LOW){
    Serial.println("Vibrator, RH15");
  }
  
  
  //Print %FIX identifier at front of string
  Serial.print("%FIX");

  //Print fix long integer of 8 chars wide. Use sprintf to add buffer spaces
  unsigned long fix = 1;
  char bufferFIX[10];
  sprintf(bufferFIX, "%8lu", fix);   // print with leading spaces
  Serial.print(bufferFIX);
  
  //Print X coord float of 1 decimal precision 8 chars wide. Use dtostrf to add buffer spaces
  char bufferX[10];
  float SCX = 39.8;
  dtostrf(SCX,8,1,bufferX);
  Serial.print(bufferX);

  //Print Y coord float of 1 decimal precision 8 chars wide. Use dtostrf to add buffer spaces
  char bufferY[10];
  float SCY = -15.7;
  dtostrf(SCY,8,1,bufferY);
  Serial.print(bufferY);
  
  //Print a new line
  Serial.print("\n");

  delay(1000);

  //Should look like   "%FIX       1   -11.1   -99.9"
}
