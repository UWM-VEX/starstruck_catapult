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

struct DriveToWPProperties {

	Drive drive;
	double magnitudeDB;
	double magnitudeBreakingDistance;
	long magnitudeRampUpTime;
	int magnitudeMaxSpeed;
	int magnitudeMinSpeed;
	double directionDB;
	double directionBreakingDistance;
	long directionRampUpTime;
	int directionMaxSpeed;
	int directionMinSpeed;
	int rotationDB;
	int rotationBreakingDistance;
	int rotationMaxSpeed;
	int rotationMinSpeed;
	double wheelDiameter;
	int gyroInverted;
	unsigned long holdTime;

}typedef DriveToWPProperties;

struct DriveToWP {

	DriveToWPProperties *properties;
	double distance;
	double direction;
	int rotation;
	int isFinished;
	int reachedDistance;
	int reachedDirection;
	int reachedRotation;
	unsigned long timeAchievedGoodLocation;
	int isFirstTime;
	int firstFrontLeftEncoder;
	int firstRearLeftEncoder;
	int firstFrontRightEncoder;
	int firstRearRightEncoder;
	int firstGyro;

} typedef DriveToWP;

DriveToWPProperties * initDriveToWPProperties(Drive drive, double magnitudeDB,
		double magnitudeBreakingDistance, long magnitudeRampUpTime, int magnitudeMaxSpeed,
		int magnitudeMinSpeed, double directionDB, double directionBreakingDistance,
		long directionRampUpTime, int directionMaxSpeed, int directionMinSpeed,
		int rotationDB, int rotationBreakingDistance, int rotationMaxSpeed,
		int rotationMinSpeed, double wheelDiameter, int gyroInverted,
		unsigned long holdTime);
DriveToWP * initDriveToWP(DriveToWPProperties * properties, double distance,
		double direction, int rotation);
void driveToWP(DriveToWP * step);

#endif /* PROPDRIVETOWAYPOINT_H_ */
