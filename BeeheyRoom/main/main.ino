#include "FlowMeter.h"
unsigned long oldTime;

FlowMeter flowmeter;

void setup() {
  Serial.begin(9600);
  flowmeter.Setup();
}

void loop() {
  if ((millis() - oldTime) > 1000) {
    flowmeter.Loop();
    int WaterUsed = 0;
    if (WaterUsed = ! flowmeter.totalLitres) {
      Serial.write("/flowmeter/(totalLitres:" + flowmeter.totalLitres);
      WaterUsed = flowmeter.totalLitres;
    }
  }
  oldTime = millis();
}


