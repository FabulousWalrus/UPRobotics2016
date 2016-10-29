// Read Buttons to see if any are pushed

bool strafeMode = false;

int strafeSpeed = 0;
int rightDriveSpeed = 0;
int leftDriveSpeed = 0;

// fork has been removed
// int forkSpeed = 0;

task controllerPolling(){
	while(true){
 		if(vexRT[Btn7U] == 1){
			// Turn drive train into strafe mode to enable easier access around the field
			strafeMode = !strafeMode;
			delay(300);
		}

		if((vexRT[Ch2] > 20) || (vexRT[Ch2] < -20)) {
			rightDriveSpeed = vexRT[Ch2];
		}
		else {
			rightDriveSpeed = 0;
		}
		if((vexRT[Ch3] > 20) || (vexRT[Ch3] < - 20)) {
			leftDriveSpeed = vexRT[Ch3];
		}
		else {
			leftDriveSpeed = 0;
		}

		if(strafeMode	== true){
			rightDriveSpeed = leftDriveSpeed;
			if ((vexRT[Ch1] > 20) || (vexRT[Ch1] < - 20)) {
				strafeSpeed = vexRT[Ch1];
			}
			else {
				strafeSpeed = 0;
			}
		}
		if((vexRT[Ch3Xmtr2] > 20) || (vexRT[Ch3Xmtr2] < - 20)) {
			throwerSpeed = vexRT[Ch3Xmtr2];
		}
		else if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch2Xmtr2] < - 20)) {
			throwerSpeed = vexRT[Ch2Xmtr2] / 3;
		}
		else {
			throwerSpeed = 0;
		}
	//	if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch4Xmtr2] < - 20)) {
	//	forkSpeed = vexRT[Ch4Xmtr2];
	//}
	//	else {
	//		forkSpeed = 0;
	//	}

		if(vexRT[Btn5U] == 1)
		{
			throwerSpeed = 127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			throwerSpeed = -127;
		}
	//	if(vexRT[Btn6U] == 1)
	//	{
	//		forkSpeed = 127;
	//	}
	//	else if(vexRT[Btn6D] == 1)
	//	{
	//		forkSpeed = -127;
	//	}
	//	else
	//	{
	//		forkSpeed = 0;
	//	}
		delay(5);
	}
}
// Add driver joystick Controls here
task driving(){

	while(true)
	{
		// Tank Drive Mode
		if(strafeMode == false){
			//Right Drive;
				motor[rightDrive] = rightDriveSpeed;
				motor[leftDrive] = leftDriveSpeed;
		}
//In strafeMode
		else {
			//writeDebugStreamLine("***** Drive Loop ******");
			motor[rightDrive] 	= rightDriveSpeed;
			motor[leftDrive] 		= leftDriveSpeed;
			motor[strafeDrive] 	= strafeSpeed;
		}
	}
		delay(5);
}
// End Driver joystick Controls
