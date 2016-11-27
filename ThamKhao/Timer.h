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
   * G?i trong hàm setup 1 l?n duy nh?t
   */
  void initialize() {
    _lastTick = millis(); 
  }
  
  /*
   * G?i ð?u tiên nh?t trong hàm loop()
   */
  void update() {
    _currentTick = millis();
  }
  
  /*
   * Tr? v? th?i gian gi?a 2 l?n loop()
   * giá tr? delta là millisecond
   */
  unsigned long delta() {
    return _currentTick - _lastTick;
  }
  
  /*
   * Yêu c?u g?i cu?i cùng trong hàm loop()
   */
  void resetTick() {
    _lastTick = _currentTick;
  }
};