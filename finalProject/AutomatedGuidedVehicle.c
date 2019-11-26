#pragma config(Sensor, dgtl1,  ,               sensorTouch)
#pragma config(Sensor, dgtl2,  ,               sensorTouch)
#pragma config(Sensor, dgtl3,  ,               sensorTouch)
#pragma config(Motor,  port2,            ,             tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool flag;
task check() // This program acts a stop function to the loop. Every time this function is used, it is checking to stop.
{
	while(true){
		if(SensorValue[dgtl1] == 1)
		{
			hogCPU();
			flag = true;
			releaseCPU();
			break;
		}
	}
}

void travel()
{
	startMotor(port2, 127); //starts motor for the vehicle to move foward
	waitUntil(SensorValue[dgtl2] == 1); // It goes until it reaches a certain distance from a wall
	stopMotor(port2); // stops the vehicle so that people the package can be unloaded
	wait(2);
	startMotor(port2, -127); //starts to move back and go to the place it came from
	waitUntil(SensorValue[dgtl3] == 1); //Goes back until 100 cm away
	stopMotor(port2);
	wait(2); // waits 2 seconds for another package to be loaded onto again
}


task main()
{
	while(true)
	{
		if (SensorValue[dgtl1] == 1) // Push the button to start the vehicle
		{
		waitUntil(SensorValue[dgtl1] == 0);
		hogCPU();
		flag = false;
		releaseCPU();
		wait(1);
		startTask(check);

			while(true) //puts it in a loop to repeat the code below
			{
				travel();
				hogCPU();
				if(flag)
				{
					travel();
					break;
				}
				releaseCPU();
			}
		}
	}
}