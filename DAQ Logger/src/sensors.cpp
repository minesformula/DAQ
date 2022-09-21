#include <string>
#include <Arduino.h>
#include "config.h"

class QuadSensor {      
  public:
      const int chanA = QUAD_CHANNELA;
      const int chanB = QUAD_CHANNELB;

    int detectRev(void);
};

int QuadSensor::detectRev(void) {
  const int startval = ((analogRead(chanA)/1024)+0.5);
  int readval = startval;

  double time = 0;

  while (readval == startval && time < 1000){
    delay(1000);
    time += 1;

    readval = ((analogRead(chanA)/1024)+0.5);
  }

  return time;
}


