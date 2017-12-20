#ifndef MAIN_H
#define MAIN_H

#include "AS5050.h"
#include "mbed.h"
#include "../mbed-os/targets/TARGET_STM/TARGET_STM32F7/TARGET_STM32F746xG/TARGET_NUCLEO_F746ZG/PinNames.h"
#include "../mbed-os/drivers/AnalogIn.h"
#include "../mbed-os/drivers/AnalogOut.h"
#include "../mbed-os/drivers/SPI.h"
#include "drivers/Clock.h"
#include "Servo.h"
#include "drivers/MyPid.h"
#include "drivers/DummyPID.h"
#include "drivers/HIDPacket.h"
#include "main.h"
#include "USBHID.h"
#include "RunEvery.h"
//Coms
#include "coms/PidServer.h"
#include "coms/DummyServer.h"
// DEFINES
#define REV2
//#define REV1
//#define PLANC
#if defined(REV2)
	//GROUND     HDMI 19,1,2,3
	//3.3 volts  HDMI 18
	//Motor 8.4v HDMI 6,5,4
	// HDMI 9
	#define SERVO_1 PE_9
	#define SERVO_2 PE_11
	#define SERVO_3 PE_13

	//Full turn PCB values
	//HDMI 17
	#define ENC_1 PD_2
	#define ENC_2 PE_4
	#define ENC_3 PE_3
	//HDMI 12
	#define LOAD_1 PA_3
	#define LOAD_2 PC_0
	#define LOAD_3 PC_3
	#define GRIPPER_SERVO PB_10
#endif
#if defined(REV1)
	//GROUND     HDMI 19,1,2,3
	//3.3 volts  HDMI 18
	//Motor 8.4v HDMI 6,5,4
	// HDMI 9
	#define SERVO_1 PE_9
	#define SERVO_2 PE_11
	#define SERVO_3 PE_13

	#define MOSI PB_5 // HDMI 16
	#define CLK PB_3 // HDMI 13
	#define MISO PB_4 // HDMI 15
	//Full turn PCB values
	//HDMI 17
	#define ENC_1 PC_8
	#define ENC_2 PC_9
	#define ENC_3 PC_10
	//HDMI 12
	#define LOAD_1 PA_3
	#define LOAD_2 PC_0
	#define LOAD_3 PC_3
	#define GRIPPER_SERVO PB_10

#endif
#if defined(PLANC)
	//GROUND     HDMI 19,1,2,3
	//3.3 volts  HDMI 18
	//Motor 8.4v HDMI 6,5,4
	// HDMI 9
	#define SERVO_1 PE_9
	#define SERVO_2 PE_11
	#define SERVO_3 PE_13

	#define MOSI PB_5 // HDMI 16
	#define CLK PB_3 // HDMI 13
	#define MISO PB_4 // HDMI 15
	//Full turn PCB values
	//HDMI 17
	#define ENC_1 PC_8
	#define ENC_2 PC_9
	#define ENC_3 PC_10
	//HDMI 12
	#define LOAD_1 PA_3
	#define LOAD_2 PC_0
	#define LOAD_3 PC_3
	#define GRIPPER_SERVO PB_10

#endif

#endif
