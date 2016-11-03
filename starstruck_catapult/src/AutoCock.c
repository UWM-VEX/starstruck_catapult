/*
 * AutoCock.c
 *
 *  Created on: Nov 3, 2016
 *      Author: Erik
 */

#include "main.h"

AutoCock * initAutoCock(Catapult * catapult)
{
	AutoCock * newStep = malloc(sizeof(AutoCock));

	newStep->catapult = catapult;
	newStep->isFinished = 0;

	return newStep;
}

void autoCock(AutoCock * step)
{
	step->isFinished = runCatapult(step->catapult, 0);
}
