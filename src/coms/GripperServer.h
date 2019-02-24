#ifndef GripperServer_H
#define GripperServer_H
#include <PacketEvent.h>
#define GRIPPERSERVER_ID 103

class GripperServer: public PacketEventAbstract{

public:
DummyServer ()
 :PacketEventAbstract(GRIPPERSERVER_ID){
 }
 void event(float*buffer)
 };
 
 #endif
