
#include "MyPid.h"
#include "Clock.h"
PIDimp::PIDimp(Servo * myServo, AS5050 * myEncoder){
  servo = myServo;
  encoder = myEncoder;
  printer= new RunEveryObject(0,1000);

}

float PIDimp::getPosition( ){
  return (float)encoder->totalAngle();
}
void PIDimp::setOutputLocal( float currentOutputValue){

  if(printer->RunEvery(getMs())>0){
    printf("\nSetpoint set to: %f systemLevel %f",currentOutputValue,state.Output);
  }
   servo->write(state.Output);
}
float PIDimp::resetPosition( float newCenter){
  // optionally reset the encoder object
  return getPosition();
}
void PIDimp::onPidConfigureLocal(){
  //nothing to do in this implementation
  state.config.stop=0.5f;// the center value for the servo object
  state.config.outputMaximum=1.0f;
  state.config.outputMinimum=0.0f;
  state.config.outputIncrement=0.0005f;
  state.config.upperHistoresis = state.config.stop+state.config.outputIncrement;
  state.config.lowerHistoresis = state.config.stop-state.config.outputIncrement;
  state.homing.homingStallBound = 20.0f;
  printf("\nPID initialized");
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
