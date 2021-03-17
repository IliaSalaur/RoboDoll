class Actuator
{
  private:
    int _rev_pin = 0;
    int _fwd_pin = 0;
    bool _highSignal = 0;
    bool _lowSignal = 0;
    
  public:
    Actuator(int rev_pin, int fwd_pin, bool standartSignal);
    void reverse();
    void forward();
    void stop();
};

Actuator::Actuator(int rev_pin, int fwd_pin, bool standartSignal = 1)
{
  _rev_pin = rev_pin;
  _fwd_pin = fwd_pin;

  if(standartSignal)
  {
    _highSignal = HIGH;
    _lowSignal = LOW;
  }
  else
  {
    _highSignal = LOW;
    _lowSignal = HIGH;
  }

  pinMode(_rev_pin, OUTPUT);
  pinMode(_fwd_pin, OUTPUT);
}

void Actuator::reverse()
{
  this->stop();
  digitalWrite(_rev_pin, _highSignal);
  digitalWrite(_fwd_pin, _lowSignal);
}

void Actuator::forward()
{
  this->stop();
  digitalWrite(_rev_pin, _lowSignal);
  digitalWrite(_fwd_pin, _highSignal);
}

void Actuator::stop()
{
  digitalWrite(_rev_pin, _lowSignal);
  digitalWrite(_fwd_pin, _lowSignal);
}
