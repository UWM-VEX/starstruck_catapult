/*
 * Shovel.c
 *
 *  Created on: Aug 16, 2016
 *      Author: Erik
 */

#include "main.h"

Catapult * initCatapult(PantherMotor topLeft, PantherMotor frontLeft, PantherMotor backLeft,
		PantherMotor topRight, PantherMotor frontRight, PantherMotor backRight,
		int limitSwitch, Encoder encoder)
{
	Catapult * newCatapult = malloc(sizeof(Catapult));
	newCatapult->topLeft = topLeft;
	newCatapult->frontLeft = frontLeft;
	newCatapult->backLeft = backLeft;
	newCatapult->topRight = topRight;
	newCatapult->frontRight = frontRight;
	newCatapult->backRight = backRight;
	newCatapult->limitSwitch = limitSwitch;
	newCatapult->encoder = encoder;
	newCatapult->mode = CATAPULT_AUTO;

	pinMode(newCatapult->limitSwitch, INPUT);

	return newCatapult;
}

int catapultIsCocked(Catapult * catapult)
{
	return digitalRead(catapult->limitSwitch) || encoderGet(catapult->encoder) > 200
					|| encoderGet(catapult->encoder) < -50;
}

/**
 * Runs the catapult to a cocked position and fires if indicated.
 * Returns whether or not the capatult is currently cocked.
 */
int runCatapult(Catapult * catapult, int fire)
{
	if(digitalRead(catapult->limitSwitch))
	{
		encoderReset(catapult->encoder);
	}

	lcdPrint(uart1, 1, "Enc: %d", encoderGet(catapult->encoder));
	lcdPrint(uart1, 2, "LS: %d", digitalRead(catapult->limitSwitch));

	if(fire)
	{
		runCatapultAtSpeed(catapult, 127);
		return 0;
	}
	else
	{
		if(catapultIsCocked(catapult))
		{
			runCatapultAtSpeed(catapult, 0);
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
