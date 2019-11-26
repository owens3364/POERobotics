#pragma config(Sensor, dgtl1,  firstFloorButton, sensorTouch)
#pragma config(Sensor, dgtl2,  secondFloorButton, sensorTouch)
#pragma config(Sensor, dgtl3,  thirdFloorButton, sensorTouch)
#pragma config(Sensor, dgtl4,  firstFloorLED,  sensorDigitalOut)
#pragma config(Sensor, dgtl5,  secondFloorLED, sensorDigitalOut)
#pragma config(Sensor, dgtl6,  thirdFloorLED,  sensorDigitalOut)
#pragma config(Sensor, dgtl7,  sonar,          sensorSONAR_mm)
#pragma config(Motor,  port1,           elevatorMotor, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

static const byte MOTOR_DIRECTION = 1; // Multiplied by motor power makes it easy to fix inverted motor powers // TODO: Update this

static const byte OPPOSITE = -1; // Multiplied by values that need to be inverted

static const byte TOLERANCE = 2; // Minimum distance allowed between target position and actual positon, in mm

static const byte INACTIVITY_TIMEOUT = 30; // Time allowed for no activity before the elevator is disabled permanently

static const byte ON = 1; // To make the digital output operations on the lights easier to understand
static const byte OFF = 0; // To make the digital output operations on the lights easier to understand

static const float MM_PER_INCH = 25.4; // For converting inches to mm for accurate use with the sonar sensor
static const float FIRST_FLOOR_SONAR_READING = 1.5 * MM_PER_INCH;
static const float SECOND_FLOOR_SONAR_READING = 4.4375 * MM_PER_INCH;
static const float THIRD_FLOOR_SONAR_READING = 7.375 * MM_PER_INCH;

static float publicTarget = 0.0; // For debugging purposes only

// Waits for 30 seconds of inactivity before ending the program
task timeout() {
	wait(INACTIVITY_TIMEOUT);
	stopAllTasks();
}

// Checks to ensure the elevator is at the target level. If it isn't, it targets the floor with a tolerance of 4mm
void targetLevel(float targetLevel) {
	publicTarget = targetLevel;
	bool targetReached = false;
	while (!targetReached) {
		if (SensorValue[sonar] - targetLevel < TOLERANCE && SensorValue[sonar] - targetLevel > OPPOSITE * TOLERANCE) {
			if (SensorValue[sonar] < targetLevel) {
				startMotor(elevatorMotor, 63.5 * MOTOR_DIRECTION);
			} else if (SensorValue[sonar] > targetLevel) {
				startMotor(elevatorMotor, -63.5 * MOTOR_DIRECTION);
			}
		} else {
			targetReached = true;
		}
	}
	stopMotor(elevatorMotor);
}

// Updates the lights to show where the elevator is at
void updateLevel(float lvl) {
	switch (lvl) {
		case FIRST_FLOOR_SONAR_READING:
			SensorValue[dgtl4] = ON;
			SensorValue[dgtl5] = OFF;
			SensorValue[dgtl6] = OFF;
		case SECOND_FLOOR_SONAR_READING:
			SensorValue[dgtl4] = OFF;
			SensorValue[dgtl5] = ON;
			SensorValue[dgtl6] = OFF;
		case THIRD_FLOOR_SONAR_READING:
			SensorValue[dgtl4] = OFF;
			SensorValue[dgtl5] = OFF;
			SensorValue[dgtl6] = ON;
	}
}

// Has the elevator move to the target position, updates the lights, and restarts the timeout
void targetAndUpdate(float lvl) {
	targetLevel(lvl);
	updateLevel(lvl);
	startTask(timeout);
}

// Starts the timeout, and then listens for button calls or floor selections and calls targetAndUpdate(lvl) in resposne until the timeout is reached
task main() {
	startTask(timeout);
	while (true) {
		if (SensorValue[dgtl1] == 1) {
			targetAndUpdate(FIRST_FLOOR_SONAR_READING);
		} else if (SensorValue[dgtl2] == 1) {
			targetAndUpdate(SECOND_FLOOR_SONAR_READING);
		} else if (SensorValue[dgtl3] == 1) {
			targetAndUpdate(THIRD_FLOOR_SONAR_READING);
		}
	}
}
