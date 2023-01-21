#include <Arduino.h>
#include "sdlogging.h"

void setup() {
  Serial.begin(19200);

  while(!Serial);


  Serial.println("Initializing SD Card...");
  if(!SD.begin(BUILTIN_SDCARD)){
        Serial.println("Failed to initialize SD Card");
  } else {
    Serial.println("SD Card Initialized");
  }

  createLog();
}

void loop() {

  int val = 11333700;

  char buf[10];
  
  for (int i = 10; i < 10 && val != 0; i++){
    buf[i] = val%10;
    val = val/10;
  }

  char red[50] = ;

  if (Serial.availableForWrite()){
    Serial.write(buf, 10);
    writeToLog(red);
    delay(5000);
  }
}