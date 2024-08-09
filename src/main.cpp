#include <Wire.h>
#include <FlexCAN_T4.h>
#include "SparkFun_ISM330DHCX.h"
#include <FastLED.h>

SparkFun_ISM330DHCX myISM; 
CRGB leds[18] = {CRGB::Red};
boolean brakeLightOn = false;
int prevMillis = 0;

// Structs for X,Y,Z data
sfe_ism_data_t accelData; 
sfe_ism_data_t gyroData; 

FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> can2;

union {
    int16_t integer;
    uint8_t bytes[2];
}converter;

void mockEBRConfig(){
	CAN_message_t msg;
	msg.id = 0;
	msg.buf[0] = 'E';
	msg.buf[1] = 'B';
	msg.buf[2] = 'R';
	msg.buf[3] = 0;
	msg.buf[4] = 3;

	can2.write(msg);
}

void mockEBRMesssage(int value){
	CAN_message_t msg;
	msg.id = 3;
	msg.len = 1;
	msg.buf[0] = value;
	can2.write(msg);
}

void mockIMU1(){
	myISM.getAccel(&accelData);

	CAN_message_t msg;

	msg.id = 1;
	msg.len = 6;
	converter.integer = int16_t((accelData.xData*9.81));
	msg.buf[0] = converter.bytes[0];
	msg.buf[1] = converter.bytes[1];

	converter.integer = int16_t((accelData.yData*9.81));
	msg.buf[2] = converter.bytes[0];
	msg.buf[3] = converter.bytes[1];

	converter.integer = int16_t((accelData.zData*9.81));
	Serial.printf("Z:%f\n", accelData.zData * 9.81);
	msg.buf[4] = converter.bytes[0];
	msg.buf[5] = converter.bytes[1];
	can2.write(msg);
}

void mockIMU2(){
	myISM.getGyro(&gyroData);

	CAN_message_t msg;

	msg.id = 2;
	msg.len = 6;

	Serial.printf("Gyro X:%f ", gyroData.xData);
	converter.integer = int16_t((gyroData.xData));
	msg.buf[0] = converter.bytes[0];
	msg.buf[1] = converter.bytes[1];

	Serial.printf("Y:%f ", gyroData.yData);
	converter.integer = int16_t((gyroData.yData));
	msg.buf[2] = converter.bytes[0];
	msg.buf[3] = converter.bytes[1];

	Serial.printf("Z:%f\n", gyroData.zData);
	converter.integer = int16_t((gyroData.zData));
	msg.buf[4] = converter.bytes[0];
	msg.buf[5] = converter.bytes[1];
	can2.write(msg);
}

void setup(){

	pinMode(15, INPUT_PULLUP);

	FastLED.addLeds<NEOPIXEL, 6>(leds, 18);
	for (int i = 0; i < 18; i++){
		leds[i] = CRGB(255, 0, 0);
	}
	FastLED.show();

	Wire.begin();

	Serial.begin(115200);

	can2.begin();
	can2.setBaudRate(1000000);
	can2.setMaxMB(16);
	can2.enableFIFO();

	if( !myISM.begin() ){
		Serial.println("Did not begin.");
		while(1);
	}

	delay(400);

	mockEBRConfig();

	pinMode(3, OUTPUT);
	digitalWrite(3, 1);

	Wire.begin();

  // Uncomment the next line to use 400kHz I2C. Essential when running the accel and gyro at 416Hz or faster.
	//Wire.setClock(400000);

	Serial.begin(115200);

	while (!myISM.begin())
	{
		Serial.println("ISM did not begin. Please check the wiring...");
		delay(100);
	}

	// Reset the device to default settings. This if helpful is you're doing multiple
	// uploads testing different settings.
	myISM.deviceReset();

	// Wait for it to finish reseting
	while (!myISM.getDeviceReset())
	{
		delay(1);
	}

	Serial.println("Reset.");
	Serial.println("Applying settings.");
	delay(100);

	myISM.setDeviceConfig();
	myISM.setBlockDataUpdate();

	// Set the output data rate and precision of the accelerometer
  // Note: we're using 208Hz for accel and 104Hz for gyro
	myISM.setAccelDataRate(ISM_XL_ODR_208Hz);
	myISM.setAccelFullScale(ISM_4g);

	// Set the output data rate and precision of the gyroscope
  // Note: we're using 208Hz for accel and 104Hz for gyro
	myISM.setGyroDataRate(ISM_GY_ODR_104Hz);
	myISM.setGyroFullScale(ISM_250dps);

	// Turn on the accelerometer's filter and apply settings.
	myISM.setAccelFilterLP2();
	myISM.setAccelSlopeFilter(ISM_LP_ODR_DIV_100);

	// Turn on the gyroscope's filter and apply settings.
	myISM.setGyroFilterLP1();
	myISM.setGyroLP1Bandwidth(ISM_MEDIUM);

	for (int i = 0; i < 18; i++){
			leds[i] = CRGB(0, 0, 0);
		}

	FastLED.show();
	brakeLightOn = false;
}

void loop(){
	if (!brakeLightOn && analogRead(15) < 80){
		for (int i = 0; i < 18; i++){
			leds[i] = CRGB(255, 0, 0);
		}
		brakeLightOn = true;

		FastLED.show();
	} else if (brakeLightOn && analogRead(15) >= 80) {
		for (int i = 0; i < 18; i++){
			leds[i] = CRGB(0, 0, 0);
		}

		FastLED.show();
		brakeLightOn = false;
	}

	if (millis() - prevMillis > 250){
		mockEBRMesssage(analogRead(15));
		prevMillis = millis();
	}

	if (myISM.checkAccelStatus())
    {
		mockIMU1();
	}

	if (myISM.checkGyroStatus()){
		mockIMU2();
	}
}