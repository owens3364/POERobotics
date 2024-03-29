#pragma config(Sensor, in2,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl1,  switchLimit,    sensorTouch)
#pragma config(Sensor, dgtl2,  pressButton,    sensorTouch)
#pragma config(Motor,  port2,           leftMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightMotor,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           mainServo,     tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
  Project Title: Test
  Team Members: Owen Scott, Peter McKibben
  Date: 11/11/19
  Section: 1


  Task Description:



  Pseudocode:

*/

void operation20() {
	wait(2);
	startMotor(rightMotor, 64);
	wait(5);
	stopMotor(rightMotor);
	startMotor(leftMotor, -95);
	wait(2.5);
	startMotor(leftMotor, 127);
	startMotor(rightMotor, 127);
	wait(7.25);
	stopMotor(leftMotor);
	stopMotor(rightMotor);
}

void operation26() {
	/*
	Write a program that performs the following simple behaviors
	Use the natural language functions where appropriate as shown below
	Add comments at the end of each command line to explain the purpose of each step
		Program the servo to go to position -127 for 2 seconds
		Go to position -63 for 3 seconds
		Go to position 0 for 2 seconds
		Go position 63 for 3 seconds
		Go to position 127 for 2 seconds
	*/
	setServo(mainServo, -127);
	wait(2);
	setServo(mainServo, -63);
	wait(3);
	setServo(0);
	wait(2);
	setServo(mainServo, 63);
	wait(3);
	setServo(mainServo, 127);
	wait(2);
}

void otherOp() {
	stopMotor(leftMotor);
	waitUntil(SensorValue[in2] == 1);
	startMotor(leftMotor, 127);
	waitUntil(SensorValue[in2] == 1);
	stopMotor(leftMotor);
}

task main()
{
	//operation20();
	//operation26();
	otherOp();
}
