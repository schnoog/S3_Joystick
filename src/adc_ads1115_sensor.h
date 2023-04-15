
#include<ADS1115_WE.h> 
#define ADS1115_I2C_ADDRESS 0x48
ADS1115_WE adc = ADS1115_WE(ADS1115_I2C_ADDRESS);


int16_t readChannelRaw(ADS1115_MUX channel) {
  int16_t rawresult = 0.0;
  adc.setCompareChannels(channel);
  rawresult = adc.getRawResult(); // alternative: getResult_mV for Millivolt
  return rawresult;
}


float readChannelmV(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}




void ads_setup(){
    if(!adc.init()){
        Serial.println("ADS1115 not connected!");
    }
    adc.setVoltageRange_mV(ADS1115_RANGE_6144); 
    adc.setCompareChannels(ADS1115_COMP_0_GND);
    adc.setMeasureMode(ADS1115_CONTINUOUS); 

}


void ads_read() {
  float voltage = 0.0;

  Serial.print("0: ");
  voltage = readChannelRaw(ADS1115_COMP_0_GND);
  Serial.print(voltage);

  Serial.print(",   1: ");
  voltage = readChannelRaw(ADS1115_COMP_1_GND);
  Serial.print(voltage);
  
  Serial.print(",   2: ");
  voltage = readChannelRaw(ADS1115_COMP_2_GND);
  Serial.print(voltage);

  Serial.print(",   3: ");
  voltage = readChannelRaw(ADS1115_COMP_3_GND);
  Serial.println(voltage);
}