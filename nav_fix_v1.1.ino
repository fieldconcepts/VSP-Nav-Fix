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
void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {
  
  //Print %FIX identifier at front of string
  Serial.print("%FIX");

  //Print fix long integer of 8 chars wide. Use sprintf to add buffer spaces
  unsigned long fix = 1;
  char bufferFIX[10];
  sprintf(bufferFIX, "%8lu", fix);   // print with leading spaces
  Serial.print(bufferFIX);
  
  //Print X coord float of 1 decimal precision 8 chars wide. Use dtostrf to add buffer spaces
  char bufferX[10];
  float SCX = 11.1;
  dtostrf(SCX,8,1,bufferX);
  Serial.print(bufferX);

  //Print Y coord float of 1 decimal precision 8 chars wide. Use dtostrf to add buffer spaces
  char bufferY[10];
  float SCY = 99.9;
  dtostrf(SCY,8,1,bufferY);
  Serial.print(bufferY);
  
  //Print a new line
  Serial.print("\n");

  delay(1000);

  //Should look like   "%FIX       1   -11.1   -99.9"
}
