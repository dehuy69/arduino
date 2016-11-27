class Timer {
  private:
    unsigned long _lastTick;
    unsigned long _currentTick;
    
    Timer() { }

    ~Timer() { }
  public:
  static Timer* getInstance() {
    static Timer* instance = new Timer();
    return instance; 
  }
  
  /*
   * G?i trong h�m setup 1 l?n duy nh?t
   */
  void initialize() {
    _lastTick = millis(); 
  }
  
  /*
   * G?i �?u ti�n nh?t trong h�m loop()
   */
  void update() {
    _currentTick = millis();
  }
  
  /*
   * Tr? v? th?i gian gi?a 2 l?n loop()
   * gi� tr? delta l� millisecond
   */
  unsigned long delta() {
    return _currentTick - _lastTick;
  }
  
  /*
   * Y�u c?u g?i cu?i c�ng trong h�m loop()
   */
  void resetTick() {
    _lastTick = _currentTick;
  }
};
class WorkScheduler {
  private:
    unsigned long _ellapsedTime;
    unsigned long _workTime;
    int _workPin;
    void (*func)(int);
  public:
    WorkScheduler(int workPin, unsigned long time,void (*func)(int)) {
      _workPin = workPin;
      _workTime = time;
      _ellapsedTime = 0;
      this->func = func;
    }
    
    ~WorkScheduler() {
      _workPin = 0;
      _workTime = 0; 
      _ellapsedTime = 0;
      func = NULL;
    }
    
    void update() {
      _ellapsedTime += Timer::getInstance()->delta();
      if (_ellapsedTime >= _workTime) {
        _ellapsedTime -= _workTime;
       if (func != NULL) {
         func(_workPin);
       } 
      }
    }
};
const int pinGreen = 4;
const int pinYellow = 10;
const int pinRed = 9;

WorkScheduler *greenPinWorkScheduler;
WorkScheduler *yellowPinWorkScheduler;
WorkScheduler *redPinWorkScheduler;

void OnRedPin_Work(int pin) {
  static boolean wasLightedUp = false;
  digitalWrite(pin, !wasLightedUp ? HIGH: LOW);
  wasLightedUp = !wasLightedUp;
}
void OnGreenPin_Work(int pin) {
  static boolean wasLightedUp = false;
  digitalWrite(pin, !wasLightedUp ? HIGH: LOW);
  wasLightedUp = !wasLightedUp;
}
void OnYellowPin_Work(int pin) {
  static boolean wasLightedUp = false;
  digitalWrite(pin, !wasLightedUp ? HIGH: LOW);
  wasLightedUp = !wasLightedUp;
}
void setup() {
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinYellow, OUTPUT);
  Timer::getInstance()->initialize();
  
  redPinWorkScheduler = new WorkScheduler(pinRed, 1000UL, OnRedPin_Work);  
  greenPinWorkScheduler = new WorkScheduler(pinGreen, 500UL, OnGreenPin_Work);
  yellowPinWorkScheduler = new WorkScheduler(pinYellow, 200UL, OnYellowPin_Work);
}

void loop() {
  Timer::getInstance()->update();
  
  redPinWorkScheduler->update();
  greenPinWorkScheduler->update();
  yellowPinWorkScheduler->update();
  Timer::getInstance()->resetTick();
}
