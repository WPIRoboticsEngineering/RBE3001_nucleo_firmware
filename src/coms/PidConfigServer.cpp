#include "PidConfigServer.h"

void PidConfigServer::event(float * buffer){

  for(int i=0; i<myPumberOfPidChannels;i++){
    // read values from the packet buffer
    float kpn        = buffer[(i*3)+0];
    float kin  = buffer[(i*3)+1];
    float kdn     = buffer[(i*3)+2];
    // Set the PID constants
    myPidObjects[i]->setPIDConstants(kpn, kin, kdn);

  }

}
