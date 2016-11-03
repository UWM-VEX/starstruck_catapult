/*
 * OI.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#include "main.h"

int OIGetDriveMagnitude()
{
	return joystickGetAnalog(1, 3);
}

int OIGetDriveDirection()
{
	return joystickGetAnalog(1, 4);
}

int OIGetDriveRotation()
{
	return joystickGetAnalog(1, 1);
}

int OIGetFire()
{
	return joystickGetDigital(1, 5, JOY_DOWN) &&
			joystickGetDigital(1, 6, JOY_DOWN);
}

int OIGetCatapultManual()
{
	return joystickGetAnalog(2, 3);
}

int OIGetCatapultAuto()
{
	return joystickGetDigital(2, 7, JOY_LEFT);
}
