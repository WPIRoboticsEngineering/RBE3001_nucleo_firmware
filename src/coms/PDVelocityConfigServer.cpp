#include "PDVelocityConfigServer.h"

void PDVelocityConfigServer::event(float * buffer){

  for(int i=0; i<myPumberOfPidChannels;i++){
    // Set the PD constants
    myPidObjects[i]->state.config.V.P=buffer[(i*3)+0];
    myPidObjects[i]->state.config.V.D=buffer[(i*3)+1];

  }

}
