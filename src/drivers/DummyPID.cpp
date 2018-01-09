#include "DummyPID.h"
#include "Clock.h"

// Return the current position of the system
float DummyPID::getPosition(){
  return state.interpolate.set;
}
//Send controller signel to the motors, bounded and scaled by the configurations
void DummyPID::setOutputLocal( float currentOutputValue){}
float DummyPID::resetPosition( float newCenter){
  // optionally reset the encoder object
  return getPosition();
}
void DummyPID::onPidConfigureLocal(){
  setPIDConstants(kp,ki,kd);
  // pd velocity constants
  state.config.V.P=vkp;
  state.config.V.D=vkd;
  // this will change the sign of the output signal, and will flip between converging and and diverging
  state.config.Polarity=true;
  state.config.stop=0.5f;// the center value for the servo object
  // this is the maximum value that should come in through setOutputLocal
  state.config.outputMaximum=0.7f;
  // this is the minimum value that should come in through setOutputLocal
  state.config.outputMinimum=0.3f;
  // the smallest increment of change for the output
  state.config.outputIncrement=0.0005f;
  // the upper and lower hystersis values for where the motor starts moving
  state.config.upperHistoresis = state.config.stop+0.01;
  state.config.lowerHistoresis = state.config.stop-0.01;
  // a value in encoder units that representst the noise floor of the sensor when detecting stall homing
  state.homing.homingStallBound = 20.0f;
  printf("\nPID initialized");
}

void DummyPID::MathCalculationPosition( float currentTime){RunAbstractPIDCalc( currentTime);}

void DummyPID::MathCalculationVelocity( float currentTime){RunPDVel();}
// User provided the events tat constitute stall or error conditions.
PidLimitEvent* DummyPID::checkPIDLimitEvents(){
  currentEvent.type=NO_LIMIT;
  return &currentEvent;
}
// rturn the current time in ms, this is needed by  the PID controller
float DummyPID::getMs(){
  return ((float)clock_us())/1000.0;

}
