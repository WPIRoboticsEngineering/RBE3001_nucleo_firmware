#include "PidServer.h"

void PidServer::event(float * buffer){
  //printf("\nPid Server Event");
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

    //perform state update
    float timeOfMotion=0;
    if(velocityTarget>0)
     timeOfMotion=(std::abs(setpoint-position)/velocityTarget)*1000;// convert from Tics per second to miliseconds
    bool newUpdate = !myPidObjects[i]->bound(setpoint,
      myPidObjects[i]->state.SetPoint,
      0.1,
     0.1);
    // printf("\n  data index %i position = %f setpoint = %f target = %f update = %i time = %f",
    // i,
    // position,
    // setpoint,
    // myPidObjects[i]->state.SetPoint,
    // newUpdate,
    // timeOfMotion
    // );

    if(newUpdate){

      __disable_irq();    // Disable Interrupts
      myPidObjects[i]->SetPIDEnabled( true);
      myPidObjects[i]->SetPIDTimed(setpoint, 0);// go to setpoint in timeBetweenPrints ms, linear interpolation
      __enable_irq();
      // printf("\n Interpolation Set = %f ,  Start = %f , setTime = %f , startTime = %f",
      // myPidObjects[i]->state.interpolate.set,
      // myPidObjects[i]->state.interpolate.start,
      // myPidObjects[i]->state.interpolate.setTime,
      // myPidObjects[i]->state.interpolate.startTime
      // );
   }
  }
}
