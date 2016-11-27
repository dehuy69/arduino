#include <Key.h>
#include <Keypad.h>

const byte rows = 4; //số hàng
const byte columns = 4; //số cột
 
int holdDelay = 700; //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3; // 
int state = 0; //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
int ledpin = 4; 
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
void setup()
{
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(9600);
}

void loop()
{
  char key = keypad.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '*':
        digitalWrite(ledpin, LOW);
        break;
      case '#':
        digitalWrite(ledpin, HIGH);
        break;
      default:
        Serial.println(key);
    }
  }
}

