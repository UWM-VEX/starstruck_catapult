/*
 * Drive.h
 *
 *  Created on: Feb 25, 2015
 *      Author: Erik
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include "main.h"

/**
 * Reference type for a two motor drive.
 */
struct Drive{

	PantherMotor frontLeftMotor;
	PantherMotor frontRightMotor;
	PantherMotor rearLeftMotor;
	PantherMotor rearRightMotor;
	Encoder frontLeftEncoder;
	Encoder frontRightEncoder;
	Encoder rearLeftEncoder;
	Encoder rearRightEncoder;
	Gyro gyro;

}typedef Drive;

Drive initDrive(PantherMotor frontLeftMotor, PantherMotor frontRightMotor,
		PantherMotor rearLeftMotor, PantherMotor rearRightMotor,
		Encoder frontLeftEncoder, Encoder frontRightEncoder,
		Encoder rearLeftEncoder, Encoder rearRightEncoder, Gyro gyro);
void holonomicDrive(Drive drive, int magnitude, int direction, int rotation);

#endif /* DRIVE_H_ */
