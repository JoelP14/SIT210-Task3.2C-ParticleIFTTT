// This #include statement was automatically added by the Particle IDE.
#include <BH1750Lib.h>

BH1750Lib lightmeter;

bool sunny;
int sunnyTime;

void setup(){
  Serial.begin(9600);
  lightmeter.begin(BH1750LIB_MODE_CONTINUOUSHIGHRES);
}


void loop() {
  uint16_t lux = lightmeter.lightLevel();
  Particle.publish("Lux", String(lux));
  if(lux > 1000)
  {
      if(!sunny)
      {
          Particle.publish("Sunny", "True", PUBLIC);
          sunny = true;
      }
      sunnyTime += 1;
  }
  else
  {
      if(sunny)
      {
          Particle.publish("Sunny", "False", PUBLIC);
          sunny = false;
      }
  }
  if(sunnyTime >= 7200)
  {
      Particle.publish("Sunny", "TimeDone", PUBLIC);
  }
  delay(1000);
}