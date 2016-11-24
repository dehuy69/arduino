/*
   Thư viện được sử dụng từ http://esp8266.github.io/Arduino/versions/2.3.0/doc/libraries.html#wifi-esp8266wifi-library
   https://github.com/esp8266/Arduino
   Một số hàm bên dưới tương tự thư viện wifi.h giành cho wifi shield. Tham khảo thêm tại https://www.arduino.cc/en/Reference/WiFi
*/
#include <ESP8266WiFi.h>

const char* ssid = "Wifi";// tên wifi mà bạn muốn connect
const char* pass = "123$%^baytamchin"; //pass wifi

const char* server = "www.google.com"; //Dùng tên miền dns
//IPAddress server(74,125,232,128); // Dùng Ip
char url[100];
char data[1000];
char outBuf[64];
WiFiClient client;

void setup() {
  Serial.begin(9600); // Cổng serial dùng để giao tiếp với arduino, bỏ debug
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, pass);
  delay(5000);
}

void loop() {

  Serial.println(Serial.available());
  Serial.readBytesUntil('(', url, 100);


  Serial.readBytes(data, 1000);
  Serial.println(data);
  Serial.println(url);




  /*
    if (client.connect(server, 80)) {
      // Make a HTTP request:
      // send the header
      sprintf(outBuf, "POST %s HTTP/1.1", url);
      client.println(outBuf);
      sprintf(outBuf, "Host: %s", server);
      client.println(outBuf);
      client.println(F("Connection: close\r\nContent-Type: application/x-www-form-urlencoded"));
      sprintf(outBuf, "Content-Length: %u\r\n", strlen(data));
      client.println(outBuf);
    }
  */
}
