#include <Wire.h>
#include <SD.h>

File sdFileWRITE;

//all declared globally up here so it can be accessed in all functions

//track time  
double msElasped = millis();
String msString;

//track height
float currentAlt = 0.00;
float prevAlt = 0.00;
float initialHeight = 0.00;
float heightGained = 0.00;

//track acceleration
float accelX = 0.00;
float accelY = 0.00;
float accelZ = 0.00;

//check how much the rocket has fallen, conditions for ignition (rhyme!)
bool checkingFalling = false;
float heightATM = 0.00; //initial height for when alt thinks we beginning to fall (apogee), ATM = at the moment
float heightFallen = 0.00;
bool haveDeployed = false;
int  falling = 0; //track how long the computer thinks rocket has been falling, compensate for noise
int explosiveCharge = 7; //pin the ignition charge is wired to, send voltage there on deployment

void setup() {
  while (!Serial) { //for when using usb, waits until connected
    delay(50);
  }
  Serial.begin(115200);
  Wire.begin();
  
  if (!SD.begin(10)) { //10 is for the cs pin defined here, checks if SD card good
    while (1);
  }
  
  sdFileWRITE = SD.open("file.txt", FILE_WRITE); //file name can't be too long
  sdFileWRITE.println(F("FILE BEGIN 1/29/23 B.1")); //unclear if this will actually get into the sd card
  sdFileWRITE.println();
  sdFileWRITE.close();

  accelSet();
  altSet();
  alt(); //first reading always a little ridiculous, don't know why
  initialHeight = alt();//second reading always back to normal

  pinMode(explosiveCharge, OUTPUT); //tels pin with igniter to be ready to output voltage
  digitalWrite(explosiveCharge, LOW);  //turns off the voltage from that pin
}

void loop() {
  accel(); //reads and saves accelerometer data

  prevAlt = currentAlt;
  currentAlt = alt();
  
  if (!haveDeployed) {
    heightGained = currentAlt - initialHeight;
  }

  //read and save altimeter data
  sdFileWRITE = SD.open("file.txt", FILE_WRITE);
  sdFileWRITE.println();
  sdFileWRITE.print(currentAlt);
  sdFileWRITE.println(F(" m, current height")); //was advised to wrap all strings in F()
  sdFileWRITE.print(heightGained);
  sdFileWRITE.println(F(" m, traveled"));

  sdFileWRITE.println();
  
  sdFileWRITE.print(F("have deployed? "));
  sdFileWRITE.println(haveDeployed); //bool, 0 for false, 1 for true;

  sdFileWRITE.println();

  if (prevAlt - currentAlt >= 0) {
    falling += 1; //checks how many times alt says been falling, noise may give msiread, so count how many tiems alt says we're falling to make sure consistently falling
    sdFileWRITE.print(falling);
    sdFileWRITE.println(F(" 1/6s falling"));
    sdFileWRITE.print(heightFallen);
    sdFileWRITE.println(F(" m, fallen"));
    sdFileWRITE.println();
    if(!checkingFalling) {
      heightATM = currentAlt;
      checkingFalling = true;
    }
  } else { //reset if noise set off condition once
    checkingFalling = false;
    falling = 0;
  }

  heightFallen = heightATM - currentAlt;

  //
  if (falling >= 3 && !haveDeployed && heightFallen>=1.00 && heightGained>=100.00){ //if been falling for 1/2s + haven't deployed already + fallen 1m and flown >70m
    sdFileWRITE.println(F("----------------"));
    sdFileWRITE.println(F("DEPLOYING"));
    sdFileWRITE.println(F("----------------"));
    haveDeployed = true;
    digitalWrite(explosiveCharge, HIGH);
  }

  msElasped = millis();
  msString = String(msElasped/60000);
  if (msString[msString.length()-2] == '0' && msString[msString.length()-1] == '0') {
    sdFileWRITE.print(F("mins elasped: "));
    sdFileWRITE.println(msElasped/60000);
  }

  sdFileWRITE.println(F("--------------------------------"));
  sdFileWRITE.close();

  delay(200); //200ms, 1/5s
}
