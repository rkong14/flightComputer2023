#include <Wire.h>
#include <SD.h>

//all declared globally up here so it can be accessed in all functions
float currentAlt = 0.00;
float prevAlt = 0.00;
float initialHeight = 0.00;
float heightGained = 0.00;

float accelX = 0.00;
float accelY = 0.00;
float accelZ = 0.00;

bool on = false;
int explosiveCharge = 7;

void setup() {
 while(!Serial){ //for whne using usb, waits until connected
    delay(50);
  }
  Serial.begin(115200);
  Wire.begin();
  Serial.println("started");

  accelSet();
  altSet();
  alt(); //this first reading is always a little ridiculous, don't know why, don't have time to research
  initialHeight = alt(); //this second reading is always back to normal so it's a better reading for the set initial height
  
  Serial.println("all set up");
  
  pinMode(explosiveCharge, OUTPUT); //stolen from BComins, tels pin with igniter to be ready to output voltage
  digitalWrite(explosiveCharge, LOW);  //also stolen from BComins, turns off the voltage from that pin
}

void loop() {

  //ACCEL DATA IS JUST TO SAVE DATA AND PLOT ARC
  accel(); //saves x and y and z data to a global variable

  prevAlt = currentAlt;
  currentAlt = alt();
  heightGained = currentAlt - initialHeight;

  Serial.print("prevAlt: ");
  Serial.println(prevAlt);
  Serial.print("currentAlt: ");
  Serial.println(currentAlt);
  Serial.print("heightGained: ");
  Serial.println(heightGained);

  if(on) { //flash LED on/off (presumably connected where ignition would be)
    digitalWrite(explosiveCharge, HIGH);
    on = false;
  } else {
    digitalWrite(explosiveCharge, LOW);
    on = true;
  }

  delay(250); //1/4 second
}
