
#include "MyPid.h"
#include "Clock.h"
PIDimp::PIDimp(Servo * myServo, AS5050 * myEncoder){
  servo = myServo;
  encoder = myEncoder;
}
float PIDimp::getPosition( ){
  return encoder->angleRad();
}
void PIDimp::setOutputLocal( float currentOutputValue){
   servo->write(currentOutputValue);
}
float PIDimp::resetPosition( float newCenter){
  // optionally reset the encoder object
  return getPosition();
}
void PIDimp::onPidConfigureLocal(){
  //nothing to do in this implementation
}

void PIDimp::MathCalculationPosition( float currentTime){
   RunAbstractPIDCalc( currentTime);
}
void PIDimp::MathCalculationVelocity( float currentTime){
   RunPDVel();
}

PidLimitEvent* PIDimp::checkPIDLimitEvents(){
  currentEvent.type=NO_LIMIT;
  return &currentEvent;
}
float PIDimp::getMs(){
  float current = clock_us();
  return current/1000.0;
}
