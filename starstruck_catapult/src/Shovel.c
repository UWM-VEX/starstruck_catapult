/*
 * Shovel.c
 *
 *  Created on: Aug 16, 2016
 *      Author: Erik
 */

#include "main.h"

Shovel * initShovel(PantherMotor topLeft, PantherMotor frontLeft, PantherMotor backLeft,
		PantherMotor topRight, PantherMotor frontRight, PantherMotor backRight, int sensor)
{
	Shovel * newShovel = malloc(sizeof(Shovel));
	newShovel->topLeft = topLeft;
	newShovel->frontLeft = frontLeft;
	newShovel->backLeft = backLeft;
	newShovel->topRight = topRight;
	newShovel->frontRight = frontRight;
	newShovel->backRight = backRight;
	newShovel->sensor = sensor;

	pinMode(newShovel->sensor, INPUT);

	return newShovel;
}

void runShovel(Shovel * shovel, int fire)
{
	if(fire)
	{
		runShovelAtSpeed(shovel, 127);
	}
	else
	{
		if(digitalRead(shovel->sensor))
		{
			runShovelAtSpeed(shovel, 0);
		}
		else
		{
			runShovelAtSpeed(shovel, 127);
		}
	}
}

void runShovelAtSpeed(Shovel * shovel, int speed)
{
	setPantherMotor(shovel->topLeft, speed);
	setPantherMotor(shovel->frontLeft, speed);
	setPantherMotor(shovel->backLeft, speed);
	setPantherMotor(shovel->topRight, speed);
	setPantherMotor(shovel->frontRight, speed);
	setPantherMotor(shovel->backRight, speed);
}
