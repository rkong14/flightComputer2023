#include <Adafruit_Sensor.h> //altimeter
#include "Adafruit_BMP3XX.h"

#define SEALEVELPRESSURE_HPA (1013.25) //for altimerter

Adafruit_BMP3XX bmp; //for altimeter

//setup
void altSet() {
  Serial.println("here alt");
  if (!bmp.begin_I2C()) {   // hardware I2C mode, can pass in address & alt Wire
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);
  } else
    Serial.println("Adafruit alt Ready.");

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);


}
  //bmp.temperature //*C
  //bmp.pressure // /100.0 hPa
  //bmp.readAltitude(SEALEVELPRESSURE_HPA) //m

float alt() {
  if (! bmp.performReading()) {
     Serial.println("couldn't perform alt reading :(");
     return;
  }

  float altData = bmp.readAltitude(SEALEVELPRESSURE_HPA);
  
  Serial.print(altData);
  Serial.println(" m");
  Serial.println();
  
  return altData; //idk why i returned the altData when I didn't for the accel, but i am too lazy to change it atm
}

 //RETURN HEIGHT OR HEIGHT CHECK BOOL FOR THE MAIN FILE, BUT ALSO SAVE IT TO SD HERE
