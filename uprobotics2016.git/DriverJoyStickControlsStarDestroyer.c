// Read Buttons to see if any are pushed

bool strafeMode = false;
bool turning = false;
bool turnBreaking = false;
bool starThrower = false;
int lastTurnError = 0;

task controllerPolling(){
	while(true){
		if(vexRT[Btn5U] == 1)
		{
			motor[rightClimb] = 127;
			motor[leftClimb] = 127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[rightClimb] = -127;
			motor[leftClimb] = -127;
		}
		else
		{
			motor[rightClimb] = 0;
			motor[leftClimb] = 0;
		}
		if(vexRT[Btn7U] == 1){
			// Turn drive train into strafe mode to enable easier access around the field
			strafeMode = !strafeMode;
		}
		if(vexRT[Btn6U] == 1){
			starThrower = !starThrower;
		}
		if (starThrower == true){
			motor[starDestroyer] = 127;
		}
		else {
			motor[starDestroyer] = 0;
		}
		delay(500);
	}
}
// Add driver joystick Controls here
task driving(){

	while(true)
	{
		if(vexRT[Btn6D] == 1){
			motor[starDestroyer] = 127;
		}
		// Tank Drive Mode
		if(strafeMode == false){

			//Right Drive;
			if((vexRT[Ch2] > 20) || (vexRT[Ch2] < -20))
			{
				turning = true;
				turnBreaking = false;
				motor[rightDrive] = vexRT[Ch2];
			}
			else {
				if (turnBreaking){
					motor[rightDrive] = -1 * sgn(SensorValue[in1]) * 15;
				}
				else{
					motor[rightDrive] = 0;
				}
			}

			// Left Drive
			if((vexRT[Ch3] > 20) || (vexRT[Ch3] < - 20))
			{
				turning = true;
				turnBreaking = false;
				motor[leftDrive] = vexRT[Ch3];
			}
			else {
				if (turnBreaking){
					motor[leftDrive] = sgn(SensorValue[in1]) * 15;
				}
				else{
					motor[leftDrive] = 0;
				}
			}

			// Should be stopped
			if(((vexRT[Ch3] < 20) && (vexRT[Ch3] > - 20)) &&
				((vexRT[Ch2] < 20) && (vexRT[Ch2] > - 20))){
					if (turnBreaking){
						if (abs(SensorValue[in1]) > (abs(lastTurnError) + 3)) // errors getting worse (surpress noise with 3)
							lastTurnError = SensorValue[in1];
						else
							turnBreaking = false;
					}
					if(turning){
						turning = false;
						lastTurnError = 0;
						SensorValue[in1] = 0;
						turnBreaking = true;
					}
				}
		}
//In strafeMode
		else {
			//writeDebugStreamLine("***** Drive Loop ******");
			if ((vexRT[Ch3] > 20) || (vexRT[Ch3] < -20) ||
				  (vexRT[Ch1] > 20) || (vexRT[Ch1] < -20))
			{
				motor[rightDrive] 	= vexRT[Ch3];
				motor[leftDrive] 		= vexRT[Ch3];
				motor[strafeDrive] 	= vexRT[Ch1];
				motor[strafeFront]  = vexRT[Ch1];
			}
			else {
				motor[strafeDrive] = 0;
				motor[strafeFront] = 0;
				motor[rightDrive] = 0;
				motor[leftDrive] = 0;
			}
		}
		delay(5);
	}
}
// End Driver joystick Controls
