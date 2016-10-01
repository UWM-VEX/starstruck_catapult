/*
 * Shovel.h
 *
 *  Created on: Aug 16, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_SHOVEL_H_
#define INCLUDE_SHOVEL_H_

struct Shovel {
	PantherMotor topLeft;
	PantherMotor frontLeft;
	PantherMotor backLeft;
	PantherMotor topRight;
	PantherMotor frontRight;
	PantherMotor backRight;
	int sensor;
}typedef Shovel;

Shovel * initShovel(PantherMotor topLeft, PantherMotor frontLeft, PantherMotor backLeft,
		PantherMotor topRight, PantherMotor frontRight, PantherMotor backRight, int sensor);
void runShovel(Shovel * shovel, int fire);
void runShovelAtSpeed(Shovel * shovel, int speed);

#endif /* INCLUDE_SHOVEL_H_ */
