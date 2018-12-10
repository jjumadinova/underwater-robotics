/*
 * file DFRobot_EC.ino
 * @ https://github.com/DFRobot/DFRobot_EC
 *
 * This is the sample code for Gravity: Analog Electrical Conductivity Sensor / Meter Kit V2 (K=1.0), SKU: DFR0300.
 * In order to guarantee precision, a temperature sensor such as DS18B20 is needed, to execute automatic temperature compensation.
 * You can send commands in the serial monitor to execute the calibration.
 * Serial Commands:
 *   enter -> enter the calibration mode
 *   cal -> calibrate with the standard buffer solution, two buffer solutions(1413us/cm and 12.88ms/cm) will be automaticlly recognized
 *   exit -> save the calibrated parameters and exit from calibration mode
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2018
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2018-03-21
 */

#include "DFRobot_EC.h"
#include <EEPROM.h>
#include <OneWire.h>

#define EC_PIN A1
float voltage,ecValue,temperature = 25;
DFRobot_EC ec;

void setup()
{
  Serial.begin(115200);  
  ec.begin();
}

void loop()
{
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U)  //time interval: 1s
    {
      timepoint = millis();
      voltage = analogRead(EC_PIN)/1024.0*5000;  // read the voltage
      //temperature = readTemperature();  // read your temperature sensor to execute temperature compensation
      ecValue =  ec.readEC(voltage,temperature);  // convert voltage to EC with temperature compensation
      Serial.print("temperature:");
      Serial.print(temperature,1);
      Serial.print("^C  EC:");
      Serial.print(ecValue,2);
      Serial.println("ms/cm");
    }
    ec.calibration(voltage,temperature);  // calibration process by Serail CMD
}

//float readTemperature()
//{
//  int DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
//
//  //Temperature chip i/o
//  OneWire ds(DS18S20_Pin);  // on digital pin 2
//
//  void setup(void) {
//    Serial.begin(9600);
//  }
//
//  void loop(void) {
//    float temperature = getTemp();
//    Serial.println(temperature);
//  
//    delay(100); //just here to slow down the output so it is easier to read
//  
//  }
//}
//
//float getTemp(){
//  //returns the temperature from one DS18S20 in DEG Celsius
//
//  byte data[12];
//  byte addr[8];
//
//  if ( !ds.search(addr)) {
//      //no more sensors on chain, reset search
//      ds.reset_search();
//      return -1000;
//  }
//
//  if ( OneWire::crc8( addr, 7) != addr[7]) {
//      Serial.println("CRC is not valid!");
//      return -1000;
//  }
//
//  if ( addr[0] != 0x10 && addr[0] != 0x28) {
//      Serial.print("Device is not recognized");
//      return -1000;
//  }
//
//  ds.reset();
//  ds.select(addr);
//  ds.write(0x44,1); // start conversion, with parasite power on at the end
//
//  byte present = ds.reset();
//  ds.select(addr);    
//  ds.write(0xBE); // Read Scratchpad
//
//  
//  for (int i = 0; i < 9; i++) { // we need 9 bytes
//    data[i] = ds.read();
//  }
//  
//  ds.reset_search();
//  
//  byte MSB = data[1];
//  byte LSB = data[0];
//
//  float tempRead = ((MSB << 8) | LSB); //using two's compliment
//  float TemperatureSum = tempRead / 16;
//  
//  return TemperatureSum;
  
//}//add your code here to get the temperature from your temperature sensor
