#include "PidServer.h"

void PidServer::event(float * buffer){
  printf("\nPid Server Event");
  for(int i=0; i<myPumberOfPidChannels;i++){

    float position = myPidObjects[i]->GetPIDPosition();
    float velocity =0;
    float torque = 0;
    // read values from the packet buffer
    float setpoint        = buffer[(i*3)+0];
    float velocityTarget  = buffer[(i*3)+1];
    float forceTarget     = buffer[(i*3)+2];
    // write upstream packets
    buffer[(i*3)+0] = position;
    buffer[(i*3)+1] = velocity;
    buffer[(i*3)+2] = torque;
    printf("\n data index %i position = %f setpoint = %f",i,position,setpoint);
    //perform stat update
    float timeOfMotion=0;
    if(velocityTarget>0)
     timeOfMotion=std::abs(setpoint-position)/velocityTarget;

    __disable_irq();    // Disable Interrupts
    if(timeOfMotion>0){
      myPidObjects[i]->SetPIDTimed(i, timeOfMotion);// go to setpoint in timeBetweenPrints ms, linear interpolation
    }
    else
      myPidObjects[i]->SetPIDTimed(i, 0);// go to setpoint in 0 ms, no interpolation
     __enable_irq();
  }
}
