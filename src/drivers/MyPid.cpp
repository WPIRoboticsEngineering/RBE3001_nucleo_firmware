#include "MyPid.h"
#include "Clock.h"

// Parameterized class constructor
PIDimp::PIDimp(Servo * myServo, AS5050 * myEncoder, AnalogIn * myLoadCell )
{
  servo = myServo;
  encoder = myEncoder;
  loadCell = myLoadCell;
  runningTotalIndex=0;
  runningTotal=0;
  
  for (int i=0;i<SENSOR_SUM;i++)
    runningValues[i]=0;
}


// Return the current position of the system
float PIDimp::getPosition( )
{
  runningTotal -=runningValues[runningTotalIndex];
  runningValues[runningTotalIndex]=(float)encoder->totalAngle();
  runningTotal +=runningValues[runningTotalIndex];
  runningTotalIndex++;
  
  if(runningTotalIndex>=SENSOR_SUM)
    runningTotalIndex = 0;
  
  return runningTotal/SENSOR_SUM;
}


//Send controller signel to the motors, bounded and scaled by the configurations
void PIDimp::setOutputLocal( float currentOutputValue)
{
  servo->write(currentOutputValue);
}


float PIDimp::resetPosition( float newCenter)
{
  // optionally reset the encoder object
  return getPosition();
}


void PIDimp::onPidConfigureLocal()
{
  setPIDConstants(kp,ki,kd);
  
  // pd velocity constants
  state.config.V.P=vkp;
  state.config.V.D=vkd;
  
  // this will change the sign of the output signal, and will flip between converging and and diverging
  state.config.Polarity=true;
  state.config.stop=0.5f;// the center value for the servo object
  
  // this is the maximum value that should come in through setOutputLocal
  state.config.outputMaximum=0.7f;
  //state.config.outputMaximum=1.0f;
  
  // this is the minimum value that should come in through setOutputLocal
  state.config.outputMinimum=0.3f;
  //state.config.outputMinimum=0.0f;
  
  // the smallest increment of change for the output
  state.config.outputIncrement=0.0005f;
  
  // the upper and lower hystersis values for where the motor starts moving
  state.config.upperHistoresis = state.config.stop+0.01;
  state.config.lowerHistoresis = state.config.stop-0.01;
  
  //We have hand set the values, the system is calibrated
  state.calibration.calibrated = true;
  state.config.calibrationState= CALIBRARTION_DONE;
  
  // a value in encoder units that representst the noise floor of the sensor when detecting stall homing
  state.homing.homingStallBound = 20.0f;
  //30 sets to 100ms velocity loop
  setVelocityControllerDivisor(60);// Sets the number of PID cycles to run before running one velocity controller
  printf("\r\nPID initialized"); 
  gravityCompTerm=0;
}


void PIDimp::MathCalculationPosition( float currentTime)
{
  //[optional] run user math functions to compute state.Output as a control signal
  RunAbstractPIDCalc( currentTime);
  state.Output+=gravityCompTerm;
}


void PIDimp::MathCalculationVelocity( float currentTime)
{
  //[optional] run user math functions to compute state.Output as a control signal
  RunPDVel();
}


// User provided the events that constitute stall or error conditions.
PidLimitEvent* PIDimp::checkPIDLimitEvents()
{
  currentEvent.type=NO_LIMIT;
  // if limit hardware is used it can be checked here
  
  return &currentEvent;
}


// return the current time in ms, this is needed by  the PID controller
float PIDimp::getMs()
{
  return ((float)clock_us()) / 1000.0;
}
