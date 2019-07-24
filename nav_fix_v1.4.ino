/*
  %FIX Navigation Fix for ACQ

  Arduino to broadcast a nav fix every second via serial communication
  to a comm port on laptop and read by ACQ software and saved in journal.
  The serial string need to be 28 characters long and begin with %FIX. The 
  next 8 charcters is an int of fix number. The next 8 chars are a 8 wide
  float to 1 dec precision for SCX, easting in meters relative to wellhead. 
  The enxt 8 chars are a 8 wide float to 1 dec precision for SCY, northing 
  in meters relativee to wellhead.

  
  
  modified 24 July 2019
  Updated to take variables and display in correct 8 char width format.
  by Ben Sherwell
*/

#include <stdio.h> // for function sprintf

//declare variables
const int pinRH11 =  2;
const int pinRH12 =  3;
const int pinRH15 =  4;
const int pinGun =  5;
const int pinVib =  6;

const int pinLEDPwr = 11;
const int pinLEDTx = 12;

int stateRH11 = 0;
int stateRH12 = 0;
int stateRH15 = 0;
int stateGun = 0;
int stateVib = 0;


void setup() {

  //assign pins, pulling digital pins to GND when switched.
  pinMode(pinRH11, INPUT_PULLUP);
  pinMode(pinRH12, INPUT_PULLUP);
  pinMode(pinRH15, INPUT_PULLUP);
  pinMode(pinGun, INPUT_PULLUP);
  pinMode(pinVib, INPUT_PULLUP);

  //Power and Serial TX LEDs
  pinMode(pinLEDPwr, OUTPUT);
  pinMode(pinLEDTx, OUTPUT);

  
  digitalWrite(pinLEDPwr, HIGH);  // Set Power pin HIGH when finished setup

  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {

  // get status of digital pins
  stateRH11 = digitalRead(pinRH11);
  stateRH12 = digitalRead(pinRH12);
  stateRH15 = digitalRead(pinRH15);
  stateGun = digitalRead(pinGun);
  stateVib = digitalRead(pinVib);

  // Check to see if only a single source is selected
  if (stateGun == LOW && stateVib == LOW){
    Serial.println ("Select only 1 source position");
  }

  // Check to see if only a single source is selected
  else if (stateRH11 == LOW && stateRH12 == LOW){
    Serial.println ("Select only 1 well position");
  }
  else if (stateRH11 == LOW && stateRH15 == LOW){
    Serial.println ("Select only 1 well position");
  }
  else if (stateRH12 == LOW && stateRH15 == LOW){
    Serial.println ("Select only 1 well position");
  }

  else if (stateGun == LOW){
    
    if (stateRH11 == LOW){
      Serial.println("Gunpit, RH11");
      unsigned long fix = 1;
      float relEasting = 30.8;
      float relNorthing = -19.1;
      printFix(fix, relEasting, relNorthing);
      flashTxLED();
    
    } else if (stateRH12 == LOW){
      Serial.println("Gunpit, RH12");
      unsigned long fix = 1;
      float relEasting = 39.8;
      float relNorthing = -15.7;
      printFix(fix, relEasting, relNorthing);
      flashTxLED();
    
    } else if (stateRH15 == LOW){
      Serial.println("Gunpit, RH15");
      unsigned long fix = 1;
      float relEasting = 21.6;
      float relNorthing = -23.2;
      printFix(fix, relEasting, relNorthing);
      flashTxLED();
    }
  }
  
  else if (stateVib == LOW){

    if (stateRH11 == LOW){
      Serial.println("Graveyard, RH11");
      unsigned long fix = 1;
      float relEasting = 120.5;
      float relNorthing = 7.0;
      printFix(fix, relEasting, relNorthing);
      flashTxLED();
    
    } else if (stateRH12 == LOW){
      Serial.println("Graveyard, RH12");
      unsigned long fix = 1;
      float relEasting = 129.6;
      float relNorthing = 10.5;
      printFix(fix, relEasting, relNorthing);
      flashTxLED();
    
    } else if (stateRH15 == LOW){
      Serial.println("Graveyard, RH15");
      unsigned long fix = 1;
      float relEasting = 111.3;
      float relNorthing = 3.0;
      printFix(fix, relEasting, relNorthing);
      flashTxLED();
    }
  }
  delay(900);
}


void printFix(unsigned long fix, float SCX, float SCY){
  
  //Print %FIX identifier at front of string
  Serial.print("%FIX");

  //Print fix long integer of 8 chars wide. Use sprintf to add buffer spaces

  char bufferFIX[10];
  sprintf(bufferFIX, "%8lu", fix);   // print with leading spaces
  Serial.print(bufferFIX);
  
  //Print X coord float of 1 decimal precision 8 chars wide. Use dtostrf to add buffer spaces
  char bufferX[10];
  dtostrf(SCX,8,1,bufferX);
  Serial.print(bufferX);

  //Print Y coord float of 1 decimal precision 8 chars wide. Use dtostrf to add buffer spaces
  char bufferY[10];
  dtostrf(SCY,8,1,bufferY);
  Serial.print(bufferY);
  
  //Print a new line
  Serial.print("\n");
  
}

void flashTxLED(){
  digitalWrite(pinLEDTx, HIGH);
  delay(100);
  digitalWrite(pinLEDTx, LOW);
}
