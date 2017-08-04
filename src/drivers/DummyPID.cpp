
#include "DummyPID.h"
#include "Clock.h"
DummyPID::DummyPID(){

}
// Return the current position of the system
float DummyPID::getPosition( ){
  return state.interpolate.set+1;
}
//Send controller signel to the motors, bounded and scaled by the configurations
void DummyPID::setOutputLocal( float currentOutputValue){}
float DummyPID::resetPosition( float newCenter){
  // optionally reset the encoder object
  return getPosition();
}
void DummyPID::onPidConfigureLocal(){}

void DummyPID::MathCalculationPosition( float currentTime){}

void DummyPID::MathCalculationVelocity( float currentTime){}
// User provided the events tat constitute stall or error conditions.
PidLimitEvent* DummyPID::checkPIDLimitEvents(){
  currentEvent.type=NO_LIMIT;
  return &currentEvent;
}
// rturn the current time in ms, this is needed by  the PID controller
float DummyPID::getMs(){
  return ((float)clock_us())/1000.0;

}
