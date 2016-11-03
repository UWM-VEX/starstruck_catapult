/*
 * Timeout.c
 *
 *  Created on: Nov 3, 2016
 *      Author: Erik
 */

#include "main.h"

Timeout * initTimer(unsigned long time)
{
	Timeout * newStep = malloc(sizeof(Timeout));

	newStep->time = time;
	newStep->isFinished = 0;

	return newStep;
}

void timeout(Timeout * step)
{
	step->isFinished = autonomousInfo.elapsedTime > step->time;
}
