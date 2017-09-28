#include "PDVelocityConfigServer.h"

void PDVelocityConfigServer::event(float * buffer){

  for(int i=0; i<myPumberOfPidChannels;i++){
    // Set the PD constants
    myPidObjects[i]->state.config.V.P=buffer[(i*2)+0];
    myPidObjects[i]->state.config.V.D=buffer[(i*2)+1];

  }

}
