#include <SparkFun_Qwiic_KX13X.h>
QwiicKX134 kxAccel; //for accelrometer

outputData accelData;

void accelSet() {
  Serial.println("here aceelSet");
  Serial.println(kxAccel.begin());
  if (!kxAccel.begin() ) {
    Serial.println("Could not communicate with the the KX13X. Freezing.");
    while (1); //to keep in a loop and not let it do more, only way to stop by hitting reset
  } else
    Serial.println("kxAccel Ready.");

  if (!kxAccel.initialize(DEFAULT_SETTINGS)) { // Loading default settings.
    Serial.println("Could not initialize the chip.");
    while (1); //to keep in a loop and not let it do more, only way to stop by hitting reset
  } else
    Serial.println(F("kxAccel initialized..."));

  kxAccel.setRange(KX134_RANGE32G); //range is 32G
}

void accel() {
  accelData = kxAccel.getAccelData(); 
  
  accelX = accelData.xData, 32;
  accelY = accelData.yData, 32;
  accelZ = accelData.zData, 32;

  /*if (counter < 10) { /to make fake accel data for testing
    if (counter < 5) {
      accelZ += 1;
    } else {
      accelZ -= 1;
    }
  }
  counter ++;*/
  
  //Serial.println(accelX);
  //Serial.println(accelY);
  Serial.print("accelZ: "); //didn't return because can only return one val, can return a pointer to an array if want to return more than one thing
  Serial.println(accelZ);
  Serial.print("accelY: ");
  Serial.println(accelY);
  Serial.print("accelX: ");
  Serial.println(accelX);
  Serial.println();
}
