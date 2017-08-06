#ifndef MYPID_BOWLER_H
#define MYPID_BOWLER_H
#include <PID_Bowler.h>
#include "AS5050.h"
#include "Servo.h"
#include "RunEvery.h"
#define kp 0.005
#define ki 0
#define kd 0
#define vkp 0.01
#define vkd 0
class PIDimp : public PIDBowler{
public:
  // constructor taking in the hardware objects
  PIDimp(Servo * myServo, AS5050 * myEncoder);
  // these are implementations of the abstract functions
  float getPosition();
  void setOutputLocal( float);
  float resetPosition( float);
  void onPidConfigureLocal();
  void MathCalculationPosition( float);
  void MathCalculationVelocity( float);
  PidLimitEvent* checkPIDLimitEvents();
  float getMs();
  // These are parts of the concrete class
  AS5050 * encoder;
  Servo * servo;

};
#endif
