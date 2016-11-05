/*
 * Shovel.c
 *
 *  Created on: Aug 16, 2016
 *      Author: Erik
 */

#include "main.h"

Catapult * initCatapult(PantherMotor topLeft, PantherMotor frontLeft, PantherMotor backLeft,
		PantherMotor topRight, PantherMotor frontRight, PantherMotor backRight,
		int pot)
{
	Catapult * newCatapult = malloc(sizeof(Catapult));
	newCatapult->topLeft = topLeft;
	newCatapult->frontLeft = frontLeft;
	newCatapult->backLeft = backLeft;
	newCatapult->topRight = topRight;
	newCatapult->frontRight = frontRight;
	newCatapult->backRight = backRight;
	newCatapult->pot = pot;
	newCatapult->mode = CATAPULT_AUTO;

	return newCatapult;
}

int catapultIsCocked(Catapult * catapult)
{
	return (analogRead(catapult->pot) > 1200);
}

/**
 * Runs the catapult to a cocked position and fires if indicated.
 * Returns whether or not the capatult is currently cocked.
 */
int runCatapult(Catapult * catapult, int fire)
{
	lcdPrint(uart1, 1, "Pot: %d", analogRead(catapult->pot));

	if(fire)
	{
		runCatapultAtSpeed(catapult, 127);
		return 0;
	}
	else
	{
		if(catapultIsCocked(catapult))
		{
			runCatapultAtSpeed(catapult, 30);
			return 1;
		}
		else
		{
			runCatapultAtSpeed(catapult, 127);
			return 0;
		}
	}
}

void runCatapultAtSpeed(Catapult * catapult, int speed)
{
	setPantherMotor(catapult->topLeft, speed);
	setPantherMotor(catapult->frontLeft, speed);
	setPantherMotor(catapult->backLeft, speed);
	setPantherMotor(catapult->topRight, speed);
	setPantherMotor(catapult->frontRight, speed);
	setPantherMotor(catapult->backRight, speed);
}
