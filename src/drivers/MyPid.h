/**
 * @file MyPid.h
 * @brief Implementation of a PID controller for the RBE3001 robotic arm
 * 
 * @section RBE3001 - Nucleo Firmware - MyPid.h
 *
 * Instructions
 * ------------
 * This class implements a PID controller. Default values for the controller
 * gains are defined below as C++ macros. You should have no need modify 
 * the code below, however you are highly encouraged to read it and see
 * the PID controller is implemented.
 * 
 */

#ifndef RBE3001_PID
#define RBE3001_PID

#include <PID_Bowler.h>
#include "AS5050.h"
#include "Servo.h"
#include "RunEvery.h"

// Initial values for the PID gains
#define kp 0.005
#define ki 0
#define kd 0
#define vkp 1

#define vkd 0
#define SENSOR_SUM 4.0

class PIDimp : public PIDBowler
{
 public:
  // when the constructor is called with no parameters, do nothing
  PIDimp(){}
  
  // constructor taking in the hardware objects
  PIDimp(Servo * myServo, AS5050 * myEncoder, AnalogIn * myLoadCell);
  
  // Functions inherited from PIDBowler
  float getPosition();
  void setOutputLocal(float);
  float resetPosition(float);
  void onPidConfigureLocal();
  void MathCalculationPosition(float);
  void MathCalculationVelocity(float);
  PidLimitEvent * checkPIDLimitEvents();
  float getMs();
  
  // Class public attributes
  AS5050 * encoder;             // list of encoders
  Servo * servo;                // list of servo motors
  AnalogIn * loadCell;          // list of load cells

  //!FIXME is there a reason why this needs is public?
  double gravityCompTerm;

  // Class private attributes
 private:
  float runningValues[(int)SENSOR_SUM];
  float runningTotal;
  int runningTotalIndex;
};

#endif
