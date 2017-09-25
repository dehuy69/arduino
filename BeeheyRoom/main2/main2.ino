#include "ElectricMeter.h"
// Thư viện ElectricMeter
#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>
//----------------------------------------------------------------------------------------------------
// Thư viện FlowMeter

//-------------------------------------------------------------------------------------------------
//_______________________________________________________________________________________________

//Khai báo biến ElectricMeter
  
  // lần cuối in kết quả là thời điển nào (tính theo ms)
  unsigned long previousMillis = 0; // Chu kì cộng kết quả 1 giây
  unsigned long previousMillis1h = 0;// Chu kì gửi giá trị 1 giờ
  RunningStatistics inputStats; // tạo đối tượng để đo lường
//-----------------------------------------------------------------------------------------------

//Khai báo biến Flowmeter
int sensorInterrupt = 0; // 0 = digital pin 2
    int sensorPin = 2;
    float calibrationFactor = 4.5;
    float flowRate = 0;
    unsigned int flowMilliLitres = 0;
    unsigned long totalMilliLitres = 0;
    int totalLitres = 0;
//----------------------------------------------------------------------------------------------
//________________________________________________________________________________________________
unsigned long oldTime;

FlowMeter flowmeter;
ElectricMeter electricmeter;
void ElectricMeter_Setup();
void setup() {
  Serial.begin(9600);
  // Setup
  ElectricMeter_Setup();
  electricmeter.Setup;
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
  if ((millis() - oldTime) > 900) {
    electricmeter.Loop();
  }
  oldTime = millis();
}


