#ifndef MAIN_H
#define MAIN_H

#include "AS5050.h"
#include "mbed.h"
#include "drivers/Clock.h"
#include "Servo.h"
#include "mbed.h"
#include "drivers/MyPid.h"
#include "drivers/DummyPID.h"
#include "drivers/HIDPacket.h"
#include "main.h"
#include "USBHID.h"
#include "RunEvery.h"

//Coms
#include "coms/PidServer.h"
/*
#define SERVO_1 PC_6
#define SERVO_2 PB_15
#define SERVO_3 PB_13
*/

#define SERVO_1 PB_13
#define SERVO_2 PB_15
#define SERVO_3 PC_6

#define MOSI PB_5
#define CLK PB_3
#define MISO PB_4

#define ENC_1 PD_14
#define ENC_2 PD_15
#define ENC_3 PF_12

#endif
