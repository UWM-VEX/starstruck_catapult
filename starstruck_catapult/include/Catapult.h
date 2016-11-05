/*
 * Shovel.h
 *
 *  Created on: Aug 16, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_CATAPULT_H_
#define INCLUDE_CATAPULT_H_

#define CATAPULT_AUTO 0
#define CATAPULT_MANUAL 1

struct Catapult {
	PantherMotor topLeft;
	PantherMotor frontLeft;
	PantherMotor backLeft;
	PantherMotor topRight;
	PantherMotor frontRight;
	PantherMotor backRight;
	int pot;
	int mode;
}typedef Catapult;

Catapult * initCatapult(PantherMotor topLeft, PantherMotor frontLeft, PantherMotor backLeft,
		PantherMotor topRight, PantherMotor frontRight, PantherMotor backRight,
		int limitSwitch);
int runCatapult(Catapult * catapult, int fire);
void runCatapultAtSpeed(Catapult * catapult, int speed);

#endif /* INCLUDE_CATAPULT_H_ */
