
#include "Adafruit_VL53L0X.h"

//    Wire.begin();



Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Adafruit_VL53L0X::VL53L0X_Sense_config_t long_range = Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY;

void tof_setup() {
  Serial.println("Adafruit VL53L0X test");
 Wire.setPins(I2C_SDA, I2C_SCL);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


uint16_t tof_getrange() {
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  return measure.RangeMilliMeter;
}
