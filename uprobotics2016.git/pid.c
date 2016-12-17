void lineFollow(int mStrafeSpeed) {

	if(SensorValue[lineFollowerInner] < SensorValue[lineFollowerCenter] + 500) {
		strafeSpeed = mStrafeSpeed;
	}

	else if(SensorValue[lineFollowerOuter] < SensorValue[lineFollowerCenter] + 500) {
		strafeSpeed = mStrafeSpeed * -1;
	}

	else {
		strafeSpeed = 0;
	}

}

bool foundLine = false;

bool findLine(int oStrafeSpeed, int mLoopCounter){

	int loopCounter = 0;

	if(foundLine == false) {
		while((foundLine == false) && (loopCounter < mLoopCounter * 4)){
			if(loopCounter < mLoopCounter){
				strafeSpeed = oStrafeSpeed;
			}
			else if(loopCounter < mLoopCounter * 2){
				strafeSpeed = oStrafeSpeed * -1;
			}
			else {
				strafeSpeed = oStrafeSpeed;
			}
			if((SensorValue[lineFollowerCenter] + 500 < SensorValue[lineFollowerInner]) && (SensorValue[lineFollowerCenter] + 500 < SensorValue[lineFollowerOuter])){
				foundLine = true;
			}
			loopCounter = loopCounter + 1;
			delay(3);
		}
	}
	return foundLine;
}

// =(

void driveForward(int distanceCM, int targetSpeed, bool brake, bool lineFollower){

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	// Enter Strafe Mode, set target speed

	strafeMode = true;

	leftDriveSpeed = 25 * sgn(distanceCM);
	rightDriveSpeed = 25 * sgn(distanceCM);

	delay(100);

	leftDriveSpeed = targetSpeed * sgn(distanceCM);
	rightDriveSpeed = targetSpeed * sgn(distanceCM);

	int targetClicks = distanceCM * 11;

	// Wait until distance is traveled
	while(abs(SensorValue[LeftDriver]) < abs(targetClicks)){
		if(lineFollower == true){
			lineFollow(30);
		}
		delay(2);
	}

	//brake, then coast

	strafeSpeed = 0;

	if(brake == true) {

		leftDriveSpeed = -10 * sgn(distanceCM);
		rightDriveSpeed = -10 * sgn(distanceCM);

		delay(100);

	}

	leftDriveSpeed = 0;
	rightDriveSpeed = 0;

	strafeMode = false;
	lineFollower = false;

}

void armPosition(int mArmPosition, int mThrowerSpeed, int timeOut) {

	clearTimer(T1);

	if(mArmPosition > SensorValue[ThrowerEncoder]) {
		while((mArmPosition > SensorValue[ThrowerEncoder]) && (timeOut > time1[T1])) {

		throwerSpeed = mThrowerSpeed;

		delay(2);
		}
	}
	else {
		while((mArmPosition < SensorValue[ThrowerEncoder]) && (timeOut > time1[T1])) {
			throwerSpeed = mThrowerSpeed * -1;

			delay(2);
		}
	}

	throwerSpeed = 0;

}

void spin(int degrees, int spinPower, bool brake) {

	strafeMode = false;

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	long spinTargetClicks = degrees * 2.35;

	while(abs(spinTargetClicks) > abs(SensorValue[LeftDriver])){
		leftDriveSpeed = spinPower * sgn(degrees);
		rightDriveSpeed = -1 * spinPower * sgn(degrees);

		delay(2);
	}

	if(brake == true) {
		leftDriveSpeed = -10 * sgn(degrees);
		rightDriveSpeed = 10 * sgn(degrees);
	}

	delay(100);

	leftDriveSpeed = 0;
	rightDriveSpeed = 0;
}

void strafeAuto(int nStrafeSpeed, int strafeDistance){
	SensorValue[LeftDriver]  = 0;
	SensorValue[RightDriver] = 0;
	strafeMode = true;
	SensorValue[StrafeDrive] = 0;
	while(abs(strafeDistance) > abs(SensorValue[StrafeDrive])){
		strafeSpeed = nStrafeSpeed * sgn(strafeDistance);
		delay(2);
	}
	strafeSpeed = 0;
}

task autoRobotGo {

	strafeAuto(100, -400);
	armPosition(-60, 120, 2000);
	armPosition(140, 80, 2000); // Claw Deployed
	driveForward(-121, 127, true, false); // Drive To Wall
	armPosition(450, 127, 3000); // Star Thrown
	delay(250);
	armPosition(380, 100, 3000);
	spin(-130, 50, true);
	driveForward(-60, 30, true, true);
	strafeAuto(80, 100);
	driveForward(-80, 30, true, false);
	strafeAuto(80, -100);
	/*driveForward(-50, 30, true, true);
	strafeAuto(80);
	driveForward(-20, 30, true, false);
	strafeAuto(-80);
	driveForward(-50, 30, true, true); */
}
