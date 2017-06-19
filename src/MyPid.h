#ifndef MYPID_BOWLER_H
#define MYPID_BOWLER_H
#include <PID_Bowler.h>
class PIDimp : public PIDBowler{
public:
  PIDimp();
  float getPosition();
  void setOutputLocal( float);
  int resetPosition( int);
  void onPidConfigureLocal();
  void MathCalculationPosition( float);
  void MathCalculationVelocity( float);
  PidLimitEvent* checkPIDLimitEvents();
   float getMs();

};
#endif
