/*
   Thư viện được sử dụng từ http://esp8266.github.io/Arduino/versions/2.3.0/doc/libraries.html#wifi-esp8266wifi-library
   https://github.com/esp8266/Arduino
   Một số hàm bên dưới tương tự thư viện wifi.h giành cho wifi shield. Tham khảo thêm tại https://www.arduino.cc/en/Reference/WiFi
*/
#include <ESP8266WiFi.h>

const char* ssid = "Wifi";// tên wifi mà bạn muốn connect
const char* pass = "123$%^baytamchin"; //pass wifi
const char* host = "192.168.1.43"; // ip or weburl
const char* server = "www.google.com"; //Dùng tên miền dns
//IPAddress server(74,125,232,128); // Dùng Ip
WiFiClient client;

void setup() {
  Serial.begin(9600); // Cổng serial dùng để giao tiếp với arduino, bỏ debug
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, pass);
  delay(5000);
}

void loop() {
  int command;
  while (Serial.available() > 0) {
    command = + Serial.read(); // đọc tín hiệu gửi
  }
  if (client.connect(server, 80)) {
    // Make a HTTP request:
    client.println("POST /" + String(command) + " HTTP/1.1");
    client.println("Host: " + String(server));
    client.println("Connection: close");
    client.println();
  }

}
