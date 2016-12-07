void lineFollow(int mStrafeSpeed) {

	if(SensorValue[lineFollowerInner] > SensorValue[lineFollowerCenter]) {
		strafeSpeed = mStrafeSpeed;
	}

	else if(SensorValue[lineFollowerOuter] > SensorValue[lineFollowerCenter]) {
		strafeSpeed = mStrafeSpeed * -1;
	}

	else {
		strafeSpeed = 0;
	}

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
		if(lineFollower == true) {
			lineFollow(50);
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

task autoRobotGo {

	armPosition(-50, 120, 2000);
	armPosition(80, 80, 2000);
	driveForward(-80, 127, true, false);
	armPosition(450, 127, 3000);
	delay(250);
	armPosition(400, 100, 3000);
	spin(-90, 40, true);
	driveForward(200, 100, true, false);
}
