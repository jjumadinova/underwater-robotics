#include <SPI.h>
#include <SD.h>
#include "GravityRtc.h"
#include "SdService.h"

extern GravityRtc rtc;
String dataString = "";

File myFile;
int pinCS = 4;


SdService :: SdService (ISensor * gravitySensor []): chipSelect (pinCS), sdDataUpdateTime ( 0 )
{
  this->gravitySensor = gravitySensor;
}


SdService :: ~ SdService ()
{
}


void SdService::setup() {
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // SD Card Initialization
  Serial.print(F("Initializing SD card..."));
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  
  // Create/Open file 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("sensor.csv", FILE_WRITE);
  if (myFile) {
   myFile.println(F("date,pH,temp(C),DO(mg/l),ec(s/m)"));
   myFile.close();
  }
}

void SdService::update() {
    dataString = "";
    // Year Month Day Hours Minute Seconds
    dataString += String(rtc.year,10);
    dataString += "/";
    dataString += String(rtc.month, 10);
    dataString += "/";
    dataString += String(rtc.day, 10);
    dataString += "/";
    dataString += String(rtc.hour, 10);
    dataString += "/";
    dataString += String(rtc.minute, 10);
    dataString += "/";
    dataString += String(rtc.second, 10);
    dataString += ",";

    // write SD card, write data twice
    myFile = SD.open("sensor.csv", FILE_WRITE);
    if (myFile)
    {
      myFile.print(dataString);
      myFile.close();
    }

    dataString = "";
    //ph
    if (this->gravitySensor[0] != NULL) {
      connectString(this->gravitySensor[0]->getValue());
    }
    else
      connectString(0);
    // temperature
    if (this->gravitySensor[1] != NULL) {
      connectString(this->gravitySensor[1]->getValue());
    }
    else
      connectString(0);
    //DO
    if (this->gravitySensor[2] != NULL) {
      connectString(this->gravitySensor[2]->getValue());
    }
    else
      connectString(0);
    //EC
    if (this->gravitySensor[3] != NULL) {
      connectString(this->gravitySensor[3]->getValue());
    }
    else
      connectString(0);

    // write SD card
    myFile = SD.open("sensor.csv", FILE_WRITE);
    if (myFile)
    {
      myFile.println(dataString);
      myFile.close();
    }
  delay(3000);
}

void SdService::connectString(double value)
{
  dataString += String(value, 10);
  dataString += ",";
}
