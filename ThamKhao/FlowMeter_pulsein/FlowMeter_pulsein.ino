int pin = 7;
unsigned long duration;

void setup() {
    Serial.begin(9600);
    pinMode(pin, INPUT);
}

void loop() {
  duration = pulseIn(pin, HIGH);   
  //Hãy nối chân 7 của Arduino vào đường tín hiệu
  //bạn muốn đọc xung
  
  Serial.print(duration);
  Serial.println(" mili giay");
  
}
