#include "VelocityTarget.h"

void VelocityTarget::event(float * buffer){

  for(int i=0; i<myPumberOfPidChannels;i++){
    //If the velocity controller is running, update the target velocity
	  if( myPidObjects[i]->state.vel.enabled)
		  myPidObjects[i]->state.vel.unitsPerSeCond=buffer[i];
	  else{
		  // Initialize the velocity controller
		  myPidObjects[i]->StartPDVel(buffer[i],0);

	  }
  }
}
