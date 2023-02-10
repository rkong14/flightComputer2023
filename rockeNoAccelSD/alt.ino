#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP3XX bmp;

//setup
void altSet() {
  if (!bmp.begin_I2C()) { //setup code specific to sensor
    while (1);
  }

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

float alt() {
  if (! bmp.performReading()) {
    return;
  }

  float altData = bmp.readAltitude(SEALEVELPRESSURE_HPA);

  return altData;
}
