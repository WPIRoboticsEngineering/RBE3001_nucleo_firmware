#ifndef GripperServer_H
#define GripperServer_H
#include <PacketEvent.h>
#include "mbed.h"
#include "Servo.h"
#define GRIPPERSERVER_ID 103

class GripperServer: public PacketEventAbstract{

public:
DummyServer ()
 :PacketEventAbstract(GRIPPERSERVER_ID){
 }
 Servo myservo(GripperServo);
 void event(float*buffer)
 };
 
 #endif
