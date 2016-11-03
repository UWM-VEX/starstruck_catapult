/*
 * AutoFire.c
 *
 *  Created on: Nov 3, 2016
 *      Author: Erik
 */

#include "main.h"

AutoFire * initAutoFire(Catapult * catapult)
{
	AutoFire * newStep = malloc(sizeof(AutoFire));

	newStep->catapult = catapult;
	newStep->timeCocked = 0;
	newStep->isFinished = 0;

	return newStep;
}

void autoFire(AutoFire * step)
{
	int cocked = runCatapult(step->catapult, 1);

	if(cocked)
	{
		step->timeCocked = millis();
	}

	if(step->timeCocked != 0)
	{
		// Step is finished if time has elapsed since the catapult was last cocked
		step->isFinished = (millis() - step->timeCocked) > 250;
	}
}
