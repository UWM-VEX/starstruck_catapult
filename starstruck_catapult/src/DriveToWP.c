/*
 * PropDriveToWayPoint.c
 *
 *  Created on: Jul 27, 2015
 *      Author: Erik
 */

#include "main.h"

// TODO Update for meccanum drive

DriveToWP initDriveToWP(Drive drive, double distance, int rotation)
{
	DriveToWPIterationInfo *iterationInfo = malloc(sizeof(DriveToWPIterationInfo));

	DriveToWP newStep = {.drive = robotDrive, .magnitudeKP = 2, .turningKP = 2, .straightRotationKP = .5,
		.distance = distance, .rotation = rotation, .straightMaxSpeed = 100, .turningMaxSpeed = 80,
		.straightMinSpeed = 20, .turningMinSpeed = 25, .slowDownDistance = 18, .timeToAccelerate = 500,
		.timeToAccelerateTurning = 250, .iteration = iterationInfo, .slowDownAngle = 40};
	lcdPrint(uart1, 1, "%d", sizeof(newStep));
	return newStep;
}

void driveToWPSetMagnitudeKP(DriveToWP *step, double kP)
{
	(*step).magnitudeKP = kP;
}

void driveToWPSetRotationKP(DriveToWP *step, double kP)
{
	(*step).turningKP = kP;
}

void driveToWPSetMaxSpeed(DriveToWP *step, int speed)
{
	(*step).straightMaxSpeed = speed;
}

void driveToWPSetMinSpeed(DriveToWP *step, int speed)
{
	(*step).straightMinSpeed = speed;
}

int driveToWPPropCorrection(DriveToWP *step, double error, double kP, int min, int max, double deadBand)
{
	int output = (int) (error * kP);

	if(inDeadBandDouble((double) error, 0, deadBand))
		output = 0;
	else if(error > 0)
	{
		output += min;
		output = limit(output, max, 0);
	}
	else
	{
		output -= min;
		output = limit(output, 0, -max);
	}

	return output;
}

int driveToWPGetRotationCorrection(DriveToWP *step)
{
	if(step->rotation == 0)
		return driveToWPPropCorrection(step, (double) step->iteration->angleError,
				step->straightRotationKP, step->turningMinSpeed, step->turningMaxSpeed, 1);
	else
		return driveToWPPropCorrection(step, (double) step->iteration->angleError,
				step->turningKP, step->turningMinSpeed, step->turningMaxSpeed, 1);
}

int driveToWPGetMagnitudeCorrection(DriveToWP *step)
{
	return driveToWPPropCorrection(step, step->iteration->distanceError, step->magnitudeKP,
			step->straightMinSpeed, step->straightMaxSpeed, 0.5);
}

void driveToWPInitIterationInfo(DriveToWP *step)
{
	/*step->iteration->magnitude = 0;
	step->iteration->rotation = 0;

	double currentDistance = (encoderGet((*step).drive.leftEncoder) +
			encoderGet((*step).drive.rightEncoder)) / 2.0;
	currentDistance = encoderToInches(currentDistance, WHEEL_DIAMETER);
	int currentAngle = GYRO_INVERTED * gyroGet((*step).drive.gyro);

	double deltaDistance = currentDistance - (*step).initialDistance;
	int deltaAngle = currentAngle - (*step).initialAngle;

	step->iteration->distanceError = (*step).distance - deltaDistance;
	step->iteration->angleError = (*step).rotation - deltaAngle;

	step->iteration->leftEncoder = encoderGet((*step).drive.leftEncoder);
	step->iteration->rightEncoder = encoderGet((*step).drive.rightEncoder);

	lcdPrint(uart1, 1, "Gyro: %d", deltaAngle);
	lcdPrint(uart1, 2, "Mag Err: %f", step->iteration->distanceError);*/
}

void driveToWPFirstInteration(DriveToWP *step)
{
	/*encoderReset((*step).drive.leftEncoder);
	encoderReset((*step).drive.rightEncoder);
	gyroReset((*step).drive.gyro);
	(*step).initialDistance = (encoderGet((*step).drive.leftEncoder) +
			encoderGet((*step).drive.rightEncoder)) / 2.0;
	(*step).initialDistance = encoderToInches((*step).initialDistance, WHEEL_DIAMETER);
	(*step).initialAngle = GYRO_INVERTED * gyroGet((*step).drive.gyro);*/
}

void driveToWP(DriveToWP *step)
{
	driveToWPInitIterationInfo(step);

	int forward = (*step).distance >= 0;
	int driveStraight = ((*step).rotation == 0);

	if(autonomousInfo.step != autonomousInfo.lastStep)
		driveToWPFirstInteration(step);

	//lcdPrint(uart1, 1, "Left: %d", encoderGet((*step).drive.leftEncoder));
	//lcdPrint(uart1, 2, "Right: %d", encoderGet((*step).drive.rightEncoder));
	lcdPrint(uart1, 2, "Gyro: %d", GYRO_INVERTED * gyroGet((*step).drive.gyro));

	int turnRight = step->iteration->angleError >= 0;

	if(driveStraight)
	{
		if(absDouble(step->iteration->distanceError) < .5)
		{
			//TODO need to make a decision on this
			step->iteration->magnitude = (forward) ? -10 : 10;
			(*step).goodDistance = 1;

			int turnEncoderError = step->iteration->leftEncoder - step->iteration->rightEncoder;

			//if(inDeadBand(turnEncoderError, 0, 5))
			//{
				(*step).goodRotation = 1;
				step->iteration->rotation = 0;
			//}
			/*else if(turnEncoderError > 0)
			{
				(*step).goodRotation = 0;
				step->iteration->rotation = -25;
			}
			else
			{
				(*step).goodRotation = 0;
				step->iteration->rotation = 25;
			}*/

			//lcdSetText(uart1, 1, "Good Distance");
		}
		else
		{
			step->iteration->rotation = driveToWPGetRotationCorrection(step);

			if(absDouble(step->iteration->distanceError) < (*step).slowDownDistance)
			{
				step->iteration->magnitude = (int) (step->iteration->distanceError * (*step).magnitudeKP);

				step->iteration->magnitude = driveToWPGetMagnitudeCorrection(step);

				//lcdPrint(uart1, 1, "%f", step->iteration->distanceError);

				//lcdSetText(uart1, 1, "Slowing Down");
			}
			else if(autonomousInfo.elapsedTime < (*step).timeToAccelerate)
			{
				step->iteration->magnitude = (int) ((autonomousInfo.elapsedTime * 1.0 / (*step).timeToAccelerate)
						* (*step).straightMaxSpeed);

				if(!forward) step->iteration->magnitude *= -1;

				//lcdSetText(uart1, 1, "Accelerating");
			}
			else
			{
				if(forward) step->iteration->magnitude = (*step).straightMaxSpeed;
				else step->iteration->magnitude = -(*step).straightMaxSpeed;

				//lcdSetText(uart1, 1, "Coasting");
			}
		}

		if((*step).goodDistance)
		{
			step->iteration->magnitude = 0;
			(*step).goodRotation = 1;

			//lcdSetText(uart1, 2, "Good Rotation");
		}
	}
	else
	{
		(*step).goodDistance = 1;

		if(abs(step->iteration->angleError) <= 1)
		{
			step->iteration->rotation = (turnRight) ? -10 : 10;
			(*step).goodRotation = 1;

			lcdSetText(uart1, 1, "Good Rotation");
		}
		else if(abs(step->iteration->angleError) < (*step).slowDownAngle)
		{
			step->goodRotation = 0;
			step->iteration->rotation = driveToWPGetRotationCorrection(step);
			lcdSetText(uart1, 1, "Slowing Down");
		}
		else if(autonomousInfo.elapsedTime < (*step).timeToAccelerateTurning)
		{
			step->goodRotation = 0;
			step->iteration->rotation = (int) ((autonomousInfo.elapsedTime * 1.0 /
					(*step).timeToAccelerateTurning) * (*step).turningMaxSpeed);

			if(!turnRight)
				step->iteration->rotation *= -1;

			if(!step->iteration->rotation) step->iteration->rotation *= -1;

			lcdSetText(uart1, 1, "Accelerating");
		}
		else
		{
			step->goodRotation = 0;
			if(turnRight)
				step->iteration->rotation = (*step).turningMaxSpeed;
			else
				step->iteration->rotation = -(*step).turningMaxSpeed;

			lcdSetText(uart1, 1, "Coasting");
		}
	}

	//lcdPrint(uart1, 1, "%d", step->iteration->rotation);
	arcadeDrive((*step).drive, step->iteration->magnitude, step->iteration->rotation);

	if(!step->goodDistance)
			step->timeAtGoodDistance = 0;
	else
	{
		if(step->timeAtGoodDistance == 0)
			step->timeAtGoodDistance = millis();
	}

	if(!step->goodRotation)
		step->timeAtGoodRotation = 0;
	else
	{
		if(step->timeAtGoodRotation == 0)
			step->timeAtGoodRotation = millis();
	}

	(*step).isFinished = (*step).goodDistance && (*step).goodRotation &&
			(millis() - step->timeAtGoodRotation > 500) && (millis() - step->timeAtGoodDistance > 500);

	if((*step).isFinished) arcadeDrive((*step).drive, 0, 0);
}
