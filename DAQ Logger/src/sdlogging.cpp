#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <stdio.h>
#include "sdlogging.h"

//Arduino.h has it's own built in string library just with an uppercase S (E.x: String instead of string)

char logFile [50];

//Creating a new log.txt file. Should not overwrite other log files.
void createLog(){

    int i = 0;
    sprintf(logFile, "logFile0.txt");

    while (SD.exists(logFile)){
        i++;

        sprintf(logFile, "logFile%d.txt", i);
    }

    sprintf(logFile, "logFile%d.txt", i);
}

//Should write an input to a file. Possibly an issue with file not being opened due to code structure.
void writeToLog(char input [50]){
    File writeFile = SD.open(logFile);
    int time = millis();

    sprintf(input, "%d %s\0", time, input);

    writeFile.seek(EOF);

    for(int i = 0; input[i] != '\0'; i++){
    writeFile.print(input[i]);
    }
    writeFile.println();
    writeFile.close();
}

