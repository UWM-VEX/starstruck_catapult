/*
 * PropDriveToWayPoint.h
 *
 *  Created on: Jul 27, 2015
 *      Author: Erik
 */

#ifndef PROPDRIVETOWAYPOINT_H_
#define PROPDRIVETOWAYPOINT_H_

#include "main.h"

#define GYRO_INVERTED 1

struct DriveToWPIterationInfo{

	int magnitude;
	int rotation;
	double distanceError;
	int angleError;
	int leftEncoder;
	int rightEncoder;

}typedef DriveToWPIterationInfo;

struct DriveToWP{

	Drive drive;
	double magnitudeKP;
	double turningKP;
	double straightRotationKP;
	double distance;
	int rotation;
	int straightMaxSpeed;
	int turningMaxSpeed;
	int straightMinSpeed;
	int turningMinSpeed;
	double initialDistance;
	int initialAngle;
	int isFinished;
	double slowDownDistance;
	long timeToAccelerate;
	int slowDownAngle;
	long timeToAccelerateTurning;
	int goodRotation;
	int goodDistance;
	long timeAtGoodRotation;
	long timeAtGoodDistance;
	DriveToWPIterationInfo *iteration;

}typedef DriveToWP;

DriveToWP initDriveToWP(Drive drive, double distance, int rotation);
void driveToWPSetMagnitudeKP(DriveToWP *step, double kP);
void driveToWPSetRotationKP(DriveToWP *step, double kP);
void driveToWPSetMaxSpeed(DriveToWP *step, int speed);
void driveToWPSetMinSpeed(DriveToWP *step, int speed);
void driveToWP(DriveToWP *step);


#endif /* PROPDRIVETOWAYPOINT_H_ */
