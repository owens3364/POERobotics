#pragma config(Sensor, dgtl1,  firstFloorButton, sensorTouch)
#pragma config(Sensor, dgtl2,  secondFloorButton, sensorTouch)
#pragma config(Sensor, dgtl3,  thirdFloorButton, sensorTouch)
#pragma config(Sensor, dgtl4,  firstFloorLED,  sensorDigitalOut)
#pragma config(Sensor, dgtl5,  secondFloorLED, sensorDigitalOut)
#pragma config(Sensor, dgtl6,  thirdFloorLED,  sensorDigitalOut)
#pragma config(Sensor, dgtl7,  sonar,          sensorSONAR_mm)
#pragma config(Motor,  port1,           elevatorMotor, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

static const byte MOTOR_DIRECTION = 1; // TODO: Update this

static const byte OPPOSITE = -1;
static const byte TOLERANCE = 2.5; // mm

static const byte INACTIVITY_TIMEOUT = 30;

static const float MM_PER_INCH = 25.4;
static const float FIRST_FLOOR_SONAR_READING = 1.5 * MM_PER_INCH;
static const float SECOND_FLOOR_SONAR_READING = 10 * MM_PER_INCH; // TODO: Update this
static const float THIRD_FLOOR_SONAR_READING = 20 * MM_PER_INCH; // TODO: Update this

static float publicTarget = 0.0;

// Waits for 30 seconds of inactivity before ending the program
task timeout() {
	wait(INACTIVITY_TIMEOUT);
	stopAllTasks();
}

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
		}
	}
	stopMotor(elevatorMotor);
}

void updateLevel(int lvl) {
	switch (lvl) {
		case FIRST_FLOOR_SONAR_READING:
			SensorValue[dgtl4] = 1;
			SensorValue[dgtl5] = 0;
			SensorValue[dgtl6] = 0;
		case SECOND_FLOOR_SONAR_READING:
			SensorValue[dgtl4] = 0;
			SensorValue[dgtl5] = 1;
			SensorValue[dgtl6] = 0;
		case THIRD_FLOOR_SONAR_READING:
			SensorValue[dgtl4] = 0;
			SensorValue[dgtl5] = 0;
			SensorValue[dgtl6] = 1;
	}
}

task main() {
	startTask(timeout);
	while (true) {
		if (SensorValue[dgtl1] == 1) {
			targetLevel(FIRST_FLOOR_SONAR_READING);
			updateLevel(FIRST_FLOOR_SONAR_READING);
			startTask(timeout);
		} else if (SensorValue[dgtl2] == 1) {
			targetLevel(SECOND_FLOOR_SONAR_READING);
			updateLevel(SECOND_FLOOR_SONAR_READING);
			startTask(timeout);
		} else if (SensorValue[dgtl3] == 1) {
			targetLevel(THIRD_FLOOR_SONAR_READING);
			updateLevel(THIRD_FLOOR_SONAR_READING);
			startTask(timeout);
		}
	}
} // all of this is coded by Tin Ngo, The master coder, The one and only, undefeated, undisputed champion of the world, super computer big brained, prodigy genius, full vietnamese, young man.
