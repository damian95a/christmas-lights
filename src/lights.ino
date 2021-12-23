#include "lights.h"

Lights::Lights(){
  // default setup
  
  ON = LOW; // default turn on by low
  pin = 13; // default pin
  pinMode(pin, OUTPUT); // init

  // turn off by dafault
  turn_off();
}

Lights::Lights(short p){
  // set pin to control the lights
  
  ON = LOW; // default turn on by low
  pin = p;  // set pin number

  pinMode(pin, OUTPUT); // init

  // turn off by dafault
  turn_off();
}

Lights::Lights(short p, bool on_ver){
  // set pin
  // and state that turns on the lights
  
  ON = on_ver; // set turn on state
  pin = p;  // set pin number

  pinMode(pin, OUTPUT);

  // turn off by dafault
  turn_off();
}


void Lights::set_state(bool o_f){
  // set o_f state on control pin
  // not recommanded to use
  
  state = o_f;
  digitalWrite(pin, state);
}

// turn on/off
// it is better to use than set_state()
void Lights::turn_on(){
  set_state(ON);
}
void Lights::turn_off(){
  set_state(!ON);
}
