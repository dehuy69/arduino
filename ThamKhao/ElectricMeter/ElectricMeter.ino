#include <FilterDerivative.h>
#include <FilterOnePole.h>
#include <Filters.h>
#include <FilterTwoPole.h>
#include <FloatDefine.h>
#include <RunningStatistics.h>


float testFrequency = 60;                     // nhà bạn dùng điện bao nhiêu Hz? Ở VN là 60Hz
float windowLength = 20.0 / testFrequency;   // mỗi tín hiệu thu về cách nhau bao nhiêu thời gian
int sensorValue = 0;
float intercept = -0.1310; //  cẩn sửa trong quá trình hiệu chuẩn
float slope = 0.04099; // cẩn sửa trong quá trình hiệu chuẩn
float current_amps; // giá trị cường độ dòng điện thực sự được đo lường

unsigned long printPeriod = 1000; // bao lâu in kết quả 1 lần (tính theo ms)
// lần cuối in kết quả là thời điển nào (tính theo ms)
unsigned long previousMillis = 0;
RunningStatistics inputStats;                 // tạo đối tượng để đo lường

void setup() {
  Serial.begin(9600);    // bật serial ở mức baudrate 57600
  inputStats.setWindowSecs(windowLength);
}

void loop() {

  sensorValue = analogRead(A1);  //đọc giá trị
  inputStats.input(sensorValue);  // đưa nó vào bộ kiểm tra
  float voltage = inputStats.sigma() * 5 / 1024; // von

  //float voltage = inputStats.sigma() - 2.5; // von, offset voltage is 2.5v

  float amps = voltage * 1000 / 66; //apme

  if ((unsigned long)(millis() - previousMillis) >= printPeriod) {
    previousMillis = millis();   // cập nhập thời điểm cuối in giá trị


    Serial.print(voltage);     Serial.println("von");

    Serial.print(amps);           Serial.println("ampe");

  }

}
