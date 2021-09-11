#ifndef LIGHTS_H
#define LIGHTS_H

class Lights{
  private:
  bool state;
  bool ON;
  short pin;

  public:
  Lights();
  Lights(short p);
  Lights(short p, bool on_ver);

  // returns current lights state
  bool get_state() const {return state;}
  
  // better not to use set_state()
  // you should choose turn_on() or turn_off()
  void set_state(bool o_f);

  // turning on/off the lights
  void turn_on();
  void turn_off();
};

#endif
