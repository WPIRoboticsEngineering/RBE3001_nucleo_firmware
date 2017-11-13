#ifndef DUMMY_PID_H
#define DUMMY_PID_H
#include <PID_Bowler.h>
#include "MyPid.h"
#include "RunEvery.h"

class DummyPID : public PIDimp{
public:
  DummyPID();

  float getPosition();
  void setOutputLocal( float);
  float resetPosition( float);
  void onPidConfigureLocal();
  void MathCalculationPosition( float);
  void MathCalculationVelocity( float);
  PidLimitEvent* checkPIDLimitEvents();
  float getMs();

};
#endif
