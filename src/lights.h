#ifndef LIGHTS_H
#define LIGHTS_H

class Lights{
  private:
  bool state;
  bool ON;
  short pin;

  public:
  /**
   * state to ON is LOW
   * default pin is 13
   * default it is OFF
   */
  Lights();

  /**
   * state to ON is LOW
   * default pin is p
   * default it is OFF
   */
  Lights(short p);

  /**
   * state to ON is on_ver
   * default pin is p
   * default it is OFF
   */
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
