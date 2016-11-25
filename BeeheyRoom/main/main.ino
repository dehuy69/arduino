#include "FlowMeter.h"
unsigned long oldTime;

FlowMeter flowmeter;

void setup() {
  flowmeter.Setup();
}

void loop() {
  if ((millis() - oldTime) > 1000) {
    flowmeter.Loop();
  }
  oldTime = millis();
}


