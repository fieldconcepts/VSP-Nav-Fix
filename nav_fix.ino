void setup() {
  Serial.begin(9600); // open the serial port at 9600 bps:
}

void loop() {


  // %s = str placeholder
  // %8d = int placeholder 8 digits wide
  // %8.1f - float placeholder 8 digits wide and precision of 1 dec place

  
  //The following (32bit) C fragment demonstrates how to generate a %FIX message. 
  //Do remember to bounds check the variables to make sure errors do not upset the 
  //formatting. The fix number must be within the range 0 to 99999999 and the coordinates 
  //must be within the range -99999.9 to +99999.9 metres.  
  
  //int fix; //fix number, unique for each shot  
  //double SCX; //easting relative to wellhead, metres  
  //double SCY; //northing relative to wellhead, metres  
  //printf(“%s%8d%+8.1f%+8.1f”, “%FIX”, fix, SCX, SCY); 
  


    Serial.print("%FIX");  // prints a label
    Serial.print("99999999");
    Serial.print("-99999.9");         
    Serial.print("-99999.9"); 
    Serial.println();
    delay(1000);

    //Output should look like this "%FIX99999999-99999.9-99999.9"
  
  
}
