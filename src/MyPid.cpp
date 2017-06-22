
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

  // if(printer->RunEvery(getMs())>0){
  //   printf("\nSetpoint set to: %f systemLevel %f",currentOutputValue,state.Output);
  // }
   servo->write(currentOutputValue);
}
float PIDimp::resetPosition( float newCenter){
  // optionally reset the encoder object
  return getPosition();
}
void PIDimp::onPidConfigureLocal(){
  state.config.Polarity=true;
  state.config.stop=0.5f;// the center value for the servo object
  // this is hte maximum value that shpould come in through setOutputLocal
  state.config.outputMaximum=0.7f;
  // this is hte minimum value that shpould come in through setOutputLocal
  state.config.outputMinimum=0.3f;
  // the smallest increment of change for the output
  state.config.outputIncrement=0.0005f;
  // the upper and lower hystersis values for where the motor starts moving
  state.config.upperHistoresis = state.config.stop+state.config.outputIncrement;
  state.config.lowerHistoresis = state.config.stop-state.config.outputIncrement;
  // a value in encoder units that representst the noise floor of the sensor when detecting stall homing
  state.homing.homingStallBound = 20.0f;
  printf("\nPID initialized");
}

void PIDimp::MathCalculationPosition( float currentTime){
  //optional run user math functions to compute state.Output as a control signal
   RunAbstractPIDCalc( currentTime);
}

void PIDimp::MathCalculationVelocity( float currentTime){
  //optional run user math functions to compute state.Output as a control signal
   RunPDVel();
}

PidLimitEvent* PIDimp::checkPIDLimitEvents(){
  currentEvent.type=NO_LIMIT;
  // if limit hardware is used it can be checked here

  return &currentEvent;
}
float PIDimp::getMs(){
  return ((float)clock_us())/1000.0;

}
