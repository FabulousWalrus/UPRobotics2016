void foward(int distanceCM, float targetSpeed){

// Constants
	float pid_Kp = 0;
	float pid_Ki = 0;
	float pid_Kd = 0;

	float CLICKS_PER_CM = 2 // Need to get this data

	int prevClicksLeft = 0;
	int currentClicksLeft = 0;

	float realSpeedLeft = 0;
	float currentErrorLeft = 0;
	float prevErrorLeft = 0;
	float sumErrorLeft = 0;

	int prevClicksRight = 0;
	int currentClicksRight = 0;

	float realSpeedRight = 0;
	float currentErrorRight = 0;
	float prevErrorRight = 0;
	float sumErrorRight = 0;


	SensorValue[leftDriver] = 0;

  clearTimer(T1);

  // Need to find stopping time.
	while(true){

		// Left side stuff
		// get real speed
		currentClicksLeft =  SensorValue[LeftDrive];
		realSpeedLeft = ((currentClicksLeft - prevClicksLeft) / time1[T1])

	  // get error ( targetSpeed - realSpeed )
		currentErrorLeft = targetSpeedLeft - realSpeedLeft;
		sumError = sumError + currentError;

		// apply new pid Power (set drive variable) (left drive speed)
		leftDriveSpeed = ( currentErrorLeft * pid_Kp ) + (sumErrorLeft * pid_Ki );


		// Right Side Stuff
		// get real speed
		currentClicksRight =  SensorValue[RightDrive];
		realSpeedRight = ((currentClicksRIght - prevClicksRight) / time1[T1])

	  // get error ( targetSpeed - realSpeed )
		currentErrorRight = targetSpeedRight - realSpeedRight;
		sumError = sumError + currentError;

		// apply new pid Power (set drive variable) (left drive speed)
		rightDriveSpeed = ( currentErrorRight * pid_Kp ) + (sumErrorRight * pid_Ki );

		// Save Previouses and reset timer
		clearTimer(T1);
		prevClicksRight = currentClicksRight;
		prevClicksLeft = currentClicksLeft;
	}
}
