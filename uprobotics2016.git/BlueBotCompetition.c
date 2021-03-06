#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in2,    lineFollowerInner, sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerCenter, sensorLineFollower)
#pragma config(Sensor, in4,    lineFollowerOuter, sensorLineFollower)
#pragma config(Sensor, dgtl1,  autoMode,       sensorDigitalIn)
#pragma config(Sensor, dgtl2,  bumperLeftFront, sensorTouch)
#pragma config(Sensor, dgtl3,  bumperLeftBack, sensorTouch)
#pragma config(Sensor, dgtl4,  bumperRightFront, sensorTouch)
#pragma config(Sensor, dgtl5,  bumperRightBack, sensorTouch)
#pragma config(Sensor, I2C_1,  StrafeDrive,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ThrowerEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  LeftDriver,     sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  RightDriver,    sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port3,           rightThrowThree, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightThrow,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           strafeDrive,   tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port6,           rightDrive,    tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port7,           leftThrowThree, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftThrow,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port9,           strafeFront,   tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "LCDDisplay2016.c" // LCD Display Control
#include "GlobalVariables.c" // Variables for all
#include "ThrowerControl.c" // Controls the thrower
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "Pid.c" // PID controller program its self explanatory idiot
#include "BlueDriverJoyStickControls.c" // User Controls For User Controlled Period
//#include "LEDLightTimers.c" // Led Light Timer for User Control Part
//#include "LCDDisplay2016.c"

int autoRoutineID = 1;

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	  bStopTasksBetweenModes = true;
	  SensorType[in1] = sensorNone;
	  wait1Msec(1000);
	  //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
	  SensorType[in1] = sensorGyro;
	  wait1Msec(2000);
		SensorValue[in1] = 0;
	  if (SensorValue[autoMode] == 1)
	  	autoRoutineID = getAutoOption();

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}
task autonomous()
{
	startTask(driving);
	startTask(throwerControl);
	if(autoRoutineID == 0){
		startTask(wallSweep);
	}
	else if(autoRoutineID == 1){
		startTask(simpleThrow);
	}
	else if(autoRoutineID == 2){
		startTask(quickBlock);
	}
	else if(autoRoutineID == 3){
		startTask(shortSweep);
	}
	else if(autoRoutineID == 4){
		startTask(longBlock);
	}
	else if(autoRoutineID == 5){
		startTask(doubleThrow);
	}
	else if(autoRoutineID == 6){
		startTask(autoRobotGo);
	}
	while(true){
		delay(500);
	}
}

task usercontrol()
{
		strafeMode = false;
		startTask(throwerControl);
	  startTask(controllerPolling);
	  startTask(driving);
	  while(true){
	  	delay(500);
	  }
}
