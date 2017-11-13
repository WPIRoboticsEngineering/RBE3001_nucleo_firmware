#ifndef  DummyServer_H
#define DummyServer_H
#include <PID_Bowler.h>
#include <PacketEvent.h>
#include "../drivers/MyPid.h"
#include <cmath>        // std::abs


class DummyServer: public PacketEventAbstract{

public:
  // Packet ID needs to be set
   DummyServer ()
   : PacketEventAbstract( 42){
  }
  //User function to be called when a packet comes in
  // Buffer contains data from the packet coming in at the start of the function
  // User data is written into the buffer to send it back
  void event(float * buffer);
};


#endif /* end of include guard: Pid_server */
