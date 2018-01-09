/**
 * @file DummyPID.h
 * @brief Implementation of a Dummy PID controller for the RBE3001 robotic arm
 * 
 * @section RBE3001 - Nucleo Firmware - DummyPID.h
 *
 * Instructions
 * ------------
 * This class implements the interface of a PID controller but does no 
 * actual work. This class is instantiated when the firmware operates in
 * Dummy mode - i.e. when no robot is connected to the nucleo board, and
 * exists purely for testing purposes.
 *
 * For a real implementation of a PID controller see MyPid.h
 * 
 */

#ifndef RBE3001_DUMMY_PID
#define RBE3001_DUMMY_PID

#include <PID_Bowler.h>
#include "MyPid.h"
#include "RunEvery.h"

class DummyPID : public PIDimp
{
 public:
  DummyPID(){}
  // constructor taking in the hardware objects
  DummyPID(Servo * myServo, AS5050 * myEncoder, AnalogIn * myLoadCell ){}

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
