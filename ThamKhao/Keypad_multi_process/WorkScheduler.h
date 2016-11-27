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
