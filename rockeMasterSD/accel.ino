#include <SparkFun_Qwiic_KX13X.h>
QwiicKX134 kxAccel; //for accelrometer

outputData accelData;

void accelSet() { //setup code specific to sensor
  if (!kxAccel.begin() ) {
    while (1);
  }
  if (!kxAccel.initialize(DEFAULT_SETTINGS)) {
    while (1);
  }
  kxAccel.setRange(KX134_RANGE32G); //range is 32G
}

void accel() {
  accelData = kxAccel.getAccelData();

  accelX = accelData.xData, 32;
  accelY = accelData.yData, 32;
  accelZ = accelData.zData, 32;

  sdFileWRITE = SD.open("file.txt", FILE_WRITE);
  sdFileWRITE.print(F("accelX, accelY, accelZ (g): "));
  sdFileWRITE.print(accelX); sdFileWRITE.print(F(", "));
  sdFileWRITE.print(accelY); sdFileWRITE.print(F(", "));
  sdFileWRITE.print(accelZ);
  sdFileWRITE.println();
  sdFileWRITE.close();

}
