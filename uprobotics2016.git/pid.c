void driveForward(int distanceCM, float targetSpeed){

	SensorValue[LeftDriver] = 0;
	SensorValue[RightDriver] = 0;

	// Enter Strafe Mode, set target speed

	strafeMode = true;

	leftDriveSpeed = 25;
	rightDriveSpeed = 25;

	delay(100);

	leftDriveSpeed = targetSpeed;
	rightDriveSpeed = targetSpeed;

	int targetClicks = distanceCM * 11;

	// Wait until distance is traveled
	while(SensorValue[LeftDriver] < targetClicks){

		delay( 10 );
	}

	//brake, then coast

	leftDriveSpeed = -10;
	rightDriveSpeed = -10;

	delay(100);

	leftDriveSpeed = 0;
	rightDriveSpeed = 0;

	strafeMode = false;

}
