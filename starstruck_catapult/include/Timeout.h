/*
 * Timeout.h
 *
 *  Created on: Nov 3, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_TIMEOUT_H_
#define INCLUDE_TIMEOUT_H_

struct Timeout {

	unsigned long time;
	int isFinished;

}typedef Timeout;

Timeout * initTimer(unsigned long time);
void timeout(Timeout * step);

#endif /* INCLUDE_TIMEOUT_H_ */
