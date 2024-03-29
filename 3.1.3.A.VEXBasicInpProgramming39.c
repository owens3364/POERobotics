#pragma config(StandardModel, "POE + CIM Testbed")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
/*
Wait until an object is detected within 20 cm to turn both motors on
Wait for the object to move more than 25 cm away before turning the motors off.
*/
waitUntil(SensorValue[dgtl5] <= 20);
startMotor(leftMotor, 127);
startMotor(rightMotor, 127);
waitUntil(SensorValue[dgtl5] >= 25);
stopMotor(leftMotor);
stopMotor(rightMotor);

}
