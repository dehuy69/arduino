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