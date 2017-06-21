
#include "MyPid.h"
#include "Clock.h"
PIDimp::PIDimp(Servo * myServo, AS5050 * myEncoder){
  servo = myServo;
  encoder = myEncoder;
}

float PIDimp::getPosition( ){
  return (float)encoder->angle();
}
void PIDimp::setOutputLocal( float currentOutputValue){
   if(currentOutputValue>1)
    currentOutputValue=1;
  if(currentOutputValue<-1)
    currentOutputValue=-1;
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
  return ((float)clock_us())/1000.0;

}
