#pragma config(StandardModel, "POE + CIM Testbed")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
/*
 Turn on both motors forward until the encoder has counted 480 degrees
 Turn on both motors in reverse until another 3.5 rotations of the encoder have passed
 Turn off both motors.
*/
startMotor(leftMotor, 127);
startMotor(rightMotor, 127);
waitUntil(SensorValue[dgtl3] >= 480);
startMotor(leftMotor, -127);
startMotor(rightMotor, -127);
waitUntil(SensorValue[dgtl3] >= 1740);
stopMotor(leftMotor);
stopMotor(rightMotor);
}
