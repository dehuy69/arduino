#include <Key.h>
#include <Keypad.h>
#include "Timer.h"
#include "WorkScheduler.h"
const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 300; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
 
//Định nghĩa các giá trị trả về
char keys[rows][columns] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
 
byte rowPins[rows] = {12, 11, 10, 9}; //Cách nối chân với Arduino
byte columnPins[columns] = {8, 7, 6, 5};
 
//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

const int pinGreen = 4;
WorkScheduler *greenPinWorkScheduler;
void OnGreenPin_Work(int pin) {
  static boolean wasLightedUp = false;
  digitalWrite(pin, !wasLightedUp ? HIGH: LOW);
  wasLightedUp = !wasLightedUp;  
}

WorkScheduler *KeypadWorkScheduler;
void Keypad_Work(int pin) {
  char temp = keypad.getKey();
  char passw[8];
  if ((int)keypad.getState() ==  PRESSED) {
    if (temp != 0) {
      key = temp;
    }
  }
  if ((int)keypad.getState() ==  HOLD) {
    state++;
    state = constrain(state, 1, n-1);
    //delay(holdDelay);
  }
 
  if ((int)keypad.getState() ==  RELEASED) {
    key += state;
    state = 0;
    //Xuất lên Máy tính để xem kết quả
    Serial.println(key);
    
       
    }
  
    
  }
  //delay(2000);


void setup() {
  Serial.begin(9600);//bật serial, baudrate 9600
  pinMode(pinGreen, OUTPUT);
  Timer::getInstance()->initialize();
  greenPinWorkScheduler = new WorkScheduler(pinGreen, 500UL, OnGreenPin_Work);
  KeypadWorkScheduler = new WorkScheduler(3, 50UL, Keypad_Work);
}
void loop() {
  Timer::getInstance()->update();
  greenPinWorkScheduler->update();
  KeypadWorkScheduler->update();
  Timer::getInstance()->resetTick();
  
  
  
}
