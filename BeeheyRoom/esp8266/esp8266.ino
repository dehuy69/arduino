/*
   Thư viện được sử dụng từ http://esp8266.github.io/Arduino/versions/2.3.0/doc/libraries.html#wifi-esp8266wifi-library
   https://github.com/esp8266/Arduino
   Một số hàm bên dưới tương tự thư viện wifi.h giành cho wifi shield. Tham khảo thêm tại https://www.arduino.cc/en/Reference/WiFi
*/
#include <ESP8266WiFi.h>

const char* ssid = "Wifi";// tên wifi mà bạn muốn connect
const char* pass = "123$%^baytamchin"; //pass wifi

const char* server = "192.168.1.1"; //Dùng tên miền dns
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
  if (Serial.available()) {
    Serial.println(Serial.available());
    Serial.readBytesUntil('(', url, 100);


    Serial.readBytes(data, 100);
    Serial.println(url);
    Serial.println(data);
    if (client.connect(server, 80) == 1) {
      // Make a HTTP request:
      // send the header
      sprintf(outBuf, "POST %s HTTP/1.1", url);
      client.println(outBuf);
      sprintf(outBuf, "Host: %s", server);      
      client.println(outBuf);
      client.println("User-Agent: Arduino/1.0");
      client.println("Connection: Keep-Alive");
      client.println("Content-Type: application/x-www-form-urlencoded; text/html; charset=utf-8");
      sprintf(outBuf, "Content-Length: %u", strlen(data));
      client.println(outBuf);
      client.println();
      client.print(data);
    }        
  }
  
int connectLoop = 0;
String inChar;
  while (client.connected())
  {
    while (client.available())
    {
      inChar = client.readString();
      Serial.println(inChar);
      connectLoop = 0;
    }

    delay(1);
    connectLoop++;
    if (connectLoop > 10000)
    {
      Serial.println();
      Serial.println(F("Timeout"));
      client.stop();
    }
  }

   
}
