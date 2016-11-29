#include "ElectricMeter.h"
#include "FlowMeter.h"
int roomid = 123456;
unsigned long oldTime;
unsigned long oldTimeh;

void setup() {
  Serial.begin(9600);
  // Setup
  ElectricMeter_Setup();
  FlowMeter_Setup();
}

void loop() {
  if ((millis() - oldTime) > 1000) {
    FlowMeter_Loop();
    if ((millis() - oldTimeh) > 3600000) {
      Serial.write("/flowmeter/(totalLitres:");
      Serial.write(FLOWMETER.totalLitres);
      Serial.write("&roomid:" + roomid);
      oldTimeh = millis();
    }
  }
  //-------------------------------------------------------------------------------
  if ((millis() - oldTime) > 900) {
    ElectricMeter_Loop();
    if ((millis() - oldTimeh) > 3600000) {
      Serial.write("/electricmeter/(kwatth:");
      Serial.write(ELECTRICMETER.kwatth);
      Serial.write("&roomid:" + roomid);
      oldTimeh = millis();
    }
//----------------------------------------------------------------------------------
    oldTime = millis();
  }
}


