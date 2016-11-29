#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>

int PinAnalog = A0;
int testFrequency;  // nhà bạn dùng điện bao nhiêu Hz? Ở VN là 60Hz
float windowLength; // mỗi tín hiệu thu về cách nhau bao nhiêu thời gian
int sensorValue;
float amps; // giá trị cường độ dòng điện thực sự được đo lường
float watts;
float kwatth;

// lần cuối in kết quả là thời điển nào (tính theo ms)
unsigned long previousMillis;
unsigned long previousMillis1;
RunningStatistics inputStats; // tạo đối tượng để đo lường

void ElectricMeter_Setup()
{
  testFrequency = 60;                  // nhà bạn dùng điện bao nhiêu Hz? Ở VN là 60Hz
  windowLength = 20.0 / testFrequency; // mỗi tín hiệu thu về cách nhau bao nhiêu thời gian
  sensorValue = 0;
  amps = 0; // giá trị cường độ dòng điện thực sự được đo lường
  watts = 0;
  kwatth = 0;

  // lần cuối in kết quả là thời điển nào (tính theo ms)
  previousMillis = 0;
  inputStats.setWindowSecs(windowLength);

}

void Loop()
{

  sensorValue = analogRead(PinAnalog);             //đọc giá trị
  inputStats.input(sensorValue);                   // đưa nó vào bộ kiểm tra
  float voltage = inputStats.sigma() * 5.2 / 1024; // von

  //float voltage = inputStats.sigma() - 2.5; // von, offset voltage is 2.5v

  amps = voltage * 1000 / 66; //apme

  if ((millis() - previousMillis) >= 1000)
  {
    previousMillis = millis(); // cập nhập thời điểm cuối in giá trị
    watts += amps * 220;
    kwatth = watts / 1000 / 3600;
    /*
      Serial.print(voltage);
      Serial.println("von");
      Serial.print(amps);
      Serial.println("ampe");
      Serial.print(amps * 220 / 1000);
      Serial.println("kWatt.h");
    */
  }
}

