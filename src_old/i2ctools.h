#include <Wire.h>
#define I2C_SDA 36
#define I2C_SCL 37


bool IsI2CDeviceAvailable(uint8_t i2c_addr){
  bool error = true;
  bool addressFound = false;
    Wire.setPins(I2C_SDA, I2C_SCL);
    Wire.begin();
    delay(100);    
    Wire.beginTransmission(i2c_addr);
    error = Wire.endTransmission();
    if(error == 0){
      addressFound = true;
    }
    Wire.end();
  return addressFound;  
}



void scanI2C(long frequency){
  String normal = "standard mode (100 kHz):";
  String fast = "fast mode (400 kHz):";
  String fastPlus = "fast mode plus (1 MHz):";
  String highSpeed = "high speed mode (3.4 MHz):";
  String ultraSpeed = "ultra fast mode (5.0 MHz):";
  String defaultStr = " !!!!! Unzulässige Frequenz !!!!!";
  bool error = true;
  bool addressFound = false;
  Serial.print("Scanne im ");
  switch(frequency){
    case 100000:
      Serial.println(normal);
      break;
    case 400000:
      Serial.println(fast);
      break;
    case 1000000:
      Serial.println(fastPlus);
      break;
    case 3400000:
      Serial.println(highSpeed);
      break;
    case 5000000:
      Serial.println(ultraSpeed);
      break;
    default:
      Serial.println(defaultStr);
      break;
  }
  
  Wire.setClock(frequency);
  for(int i=1; i<128; i++){
    Wire.beginTransmission(i);
    error = Wire.endTransmission();
    if(error == 0){
      addressFound = true;
      Serial.print("0x");
      Serial.println(i,HEX);
    }
  }
  if(!addressFound){
    Serial.println("Keine Adresse erkannt");
  }
  Serial.println();
}

