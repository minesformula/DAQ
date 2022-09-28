#ifndef CONFIG_H
#define CONFIG_H

#define RADIO_BAUD 57600 // Baud rate for radio

//Current pin assignments are arbritrary change upon physical assignment

//Quadrature Speed Sensor Definitions
//Digital Quadrature Speed Sensor Pins: Channel B will take precedence if speed is negative
#define QUAD_VSUPPLY 2
#define QUAD_GROUND 3
#define QUAD_CHANNELA 4
#define QUAD_CHANNELB 5

//Number of gaps + teeth on tone wheel. For Revolutions per second calculation in sensors.cpp
#define TONE_NUM 216

//Linear (millimeter) size of gap from one tooth to another. For Millimeters per second calculation in sensors.cpp
#define TONE_GAP 0.08



//Infrared Brake Temperature Sensor
#define BRAKETEMP_VSUPPLY 6
#define BRAKETEMP_GROUND 7
#define BRAKETEMP_SCLOCK 8
#define BRAKETEMP_IO 9

#endif