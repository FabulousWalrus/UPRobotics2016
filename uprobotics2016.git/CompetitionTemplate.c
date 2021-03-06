#pragma config(Sensor, dgtl1,  ledGreen,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  ledYellow,      sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  ledRed,         sensorLEDtoVCC)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           strafeDrive,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           strafeFront,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           starDestroyer, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightClimb,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftClimb,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "DriverJoyStickControlsStarDestroyer.c" // User Controls For User Controlled Period
#include "LEDLightTimers.c" // Led Light Timer for User Control Part
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

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}
task autonomous()
{

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

task usercontrol()
{
	  startTask(controllerPolling);
	  startTask(driving);
	  startTask(lightShow);
	  while(true){
	  	delay(500);
	  }
}
