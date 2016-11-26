void driveForward(int distanceCM, int targetSpeed, bool brake){

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

		delay( 10 );
	}

	//brake, then coast

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

		delay(10);
		}
	}
	else {
		while((mArmPosition < SensorValue[ThrowerEncoder]) && (timeOut > time1[T1])) {
			throwerSpeed = mThrowerSpeed * -1;

			delay(10);
		}
	}

	throwerSpeed = 0;

}

void spinClockwise(int degrees, int spinPower, bool brake) {

	strafeMode = false;

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	int spinTargetClicks = degrees * 8;

	while(abs(spinTargetClicks) > abs(SensorValue[LeftDriver])) {
		motor[leftDrive] = spinPower * sgn(degrees);
		motor[rightDrive] = -1 * spinPower * sgn(degrees);

		delay(10);
	}

	if(brake == true) {
		motor[leftDrive] = -10 * sgn(degrees);
		motor[rightDrive] = 10 * sgn(degrees);
	}

	delay(100);

	motor[leftDrive] = 0;
	motor[rightDrive] = 0;

}
