/*
 * AutoFire.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_AUTOFIRE_H_
#define INCLUDE_AUTOFIRE_H_

struct AutoFire {

	Catapult * catapult;
	unsigned long timeCocked;
	int isFinished;

}typedef AutoFire;

AutoFire * initAutoFire(Catapult * catapult);
void autoFire(AutoFire * step);

#endif /* INCLUDE_AUTOFIRE_H_ */
