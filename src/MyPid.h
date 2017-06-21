#ifndef MYPID_BOWLER_H
#define MYPID_BOWLER_H
#include <PID_Bowler.h>
#include "AS5050.h"
#include "Servo.h"
#include "RunEvery.h"
class PIDimp : public PIDBowler{
public:
  PIDimp(Servo * myServo, AS5050 * myEncoder);
  float getPosition();
  void setOutputLocal( float);
  float resetPosition( float);
  void onPidConfigureLocal();
  void MathCalculationPosition( float);
  void MathCalculationVelocity( float);
  PidLimitEvent* checkPIDLimitEvents();
  float getMs();
  AS5050 * encoder;
  Servo * servo;
  RunEveryObject * printer;

};
#endif
