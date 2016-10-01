/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions

related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source

code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task

with the default
 * priority and stack size whenever the robot is enabled via the Field Management

System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or

communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot

will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX

Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition

Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit.

If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

/**
 * This is where you declare all of the actions the robot will take.
 * The options are DriveForTime which is useful for driving into something
 * but shouldn't be used elsewhere, DriveToWayPoint, which will handle
 * driving forward and back, strafing, and turning (turning must be in
 * its own step) and AutoLiftToHeight which will bring the lift to a
 * specified height (Note: Once the step where this function is used has
 * completed, the lift will move down due to gravity. To avoid this,
 * create a new AutoLiftToHeight function to keep the lift at the desired
 * height. Also, the lift to height code isn't perfectly tuned yet,
 * if the autonomous stalls with the autoLiftToHeight function, help the
 * lift up.)
 *
 * Running the pickup or spinner does not require an object to be declared
 * or instantiated, an example is shown below.
 */

int isAuto = 1;

long int stepStartTime;

DriveToWP worlds1TurnToBump;
DriveToWP worlds1DriveToBump;
DriveToWP worlds1TurnToFirstPile;
DriveToWP worlds1DriveToFirstPile;
DriveToWP worlds1TurnToShoot1;
DriveToWP worlds1DriveToShoot1;
DriveToWP worlds1TurnToSecondPile;
DriveToWP worlds1DriveToSecondPile;
DriveToWP worlds1SlowToSecondPile;
DriveToWP worlds1TurnToShoot2;
DriveToWP worlds1DriveToShoot2;
DriveToWP worlds1BackToThirdPile;
DriveToWP worlds1TurnToThirdPile;
DriveToWP worlds1DriveToThirdPile;
DriveToWP worlds1BackToShoot;
DriveToWP worlds1TurnToShoot3;
DriveToWP worlds1DriveToShoot3;

DriveToWP worlds2TurnToBump;
DriveToWP worlds2DriveToBump;
DriveToWP worlds2TurnToFirstPile;
DriveToWP worlds2DriveToFirstPile;
DriveToWP worlds2TurnToShoot1;
DriveToWP worlds2DriveToShoot1;
DriveToWP worlds2BackToPile2;
DriveToWP worlds2TurnToPile2;
DriveToWP worlds2DriveToPile2;
DriveToWP worlds2BackToShoot2;
DriveToWP worlds2TurnToShoot2;
DriveToWP worlds2DriveToShoot2;
DriveToWP worlds2TurnToPile3;
DriveToWP worlds2DriveToPile3;
DriveToWP worlds2SlowToPile3;
DriveToWP worlds2TurnToShoot3;
DriveToWP worlds2DriveToShoot3;

DriveToWP worlds3TurnToPile1;
DriveToWP worlds3DriveToPile1;
DriveToWP worlds3TurnPile2;
DriveToWP worlds3ThroughPile2;
DriveToWP worlds3BackToPile3;
DriveToWP worlds3TurnToPile3;
DriveToWP worlds3DriveToPile3;
DriveToWP worlds3BackToShoot2;
DriveToWP worlds3TurnToShoot2;
DriveToWP worlds3DriveToShoot2;
DriveToWP worlds3TurnToPile4;
DriveToWP worlds3DriveToPile4;
DriveToWP worlds3SlowToPile4;
DriveToWP worlds3TurnToShoot4;
DriveToWP worlds3DriveToShoot3;

DriveToWP worlds4TurnToDrive;
DriveToWP worlds4Drive;
DriveToWP worlds4TurnToPile1;
DriveToWP worlds4DriveToPile1;
DriveToWP worlds4BackToShoot1;
DriveToWP worlds4TurnToShoot1;
DriveToWP worlds4DriveToShoot1;
DriveToWP worlds4SlowToPile2;
DriveToWP worlds4DriveToShoot2;


DriveToWP worlds5TurnToShoot1;
DriveToWP worlds5DriveToShoot1;
DriveToWP worlds5TurnToGoal1;
DriveToWP worlds5TurnToPile2;
DriveToWP worlds5DriveToPile2;
DriveToWP worlds5SlowToPile2;
DriveToWP worlds5FastToPile2;
DriveToWP worlds5TurnToShoot2;
DriveToWP worlds5TurnToPile3;
DriveToWP worlds5DriveToPile3;
DriveToWP worlds5BackToShoot3;
DriveToWP worlds5TurnToShoot3;

DriveToWP turn90;

DriveToWP worldsfeedTurnToClear;
DriveToWP worldsfeedDriveToSet;
DriveToWP worldsfeedTurnToFeed;
DriveToWP worldsfeedDriveToFeed;
DriveToWP worldsfeedBackToPile1;
DriveToWP worldsfeedTurnToPile1;
DriveToWP worldsfeedDriveToPile1;
DriveToWP worldsfeedDriveToPile1Slow;
DriveToWP worldsfeedDriveThroughPile1;
DriveToWP worldsfeedDriveToFeed4;
DriveToWP worldsfeedBackToFeed2;
DriveToWP worldsfeedTurnToFeed2;
DriveToWP worldsfeedBackToPile3;
DriveToWP worldsfeedTurnToPile3;
DriveToWP worldsfeedDriveToPile3;
DriveToWP worldsfeedSlowToPile3;
DriveToWP worldsfeedDriveThroughPile3;
DriveToWP worldsfeedTurnToFeed3;
DriveToWP worldsfeedDriveToFeed3;

DriveToWP worlds6TurnToPile1;
DriveToWP worlds6DriveToPile1;
DriveToWP worlds6TurnPile2;
DriveToWP worlds6ThroughPile2;
DriveToWP worlds6BackToPile3;
DriveToWP worlds6TurnToPile3;
DriveToWP worlds6DriveToPile3;
DriveToWP worlds6BackToShoot2;
DriveToWP worlds6TurnToShoot2;
DriveToWP worlds6DriveToShoot2;
DriveToWP worlds6BackToClean;
DriveToWP worlds6TurnToClean;
DriveToWP worlds6DriveToClean;
DriveToWP worlds6BackToShoot3;
DriveToWP worlds6TurnToShoot3;
DriveToWP worlds6DriveToShoot3;

int globalTimeout;

/**
 * Runs at the start of autonomous. Steps should be initialized here.
 */
void autonomousInit()
{
	/**
	 * Here, the different steps are instantiated and details are
	 * given about them. By hovering over the function name, you can see a
	 * list of the arguments to pass in.
	 */

	globalTimeout = 6000;

	if(autonomousSelection == WORLDS_1)
	{
		if(alliance == BLUE)
		{
			worlds1TurnToBump = initDriveToWP(robotDrive, 0, -50);
			worlds1DriveToBump = initDriveToWP(robotDrive, 6*12, 0);
			worlds1TurnToFirstPile = initDriveToWP(robotDrive, 0, -

18);
			worlds1DriveToFirstPile = initDriveToWP(robotDrive, 24,

0);
				driveToWPSetMaxSpeed(&worlds1DriveToFirstPile,

40);
			worlds1TurnToShoot1 = initDriveToWP(robotDrive, 0, 51);
			worlds1DriveToShoot1 = initDriveToWP(robotDrive, 22, 0);
			worlds1TurnToSecondPile = initDriveToWP(robotDrive, 0,

97);
			worlds1DriveToSecondPile = initDriveToWP(robotDrive, 10,

0);
			worlds1SlowToSecondPile = initDriveToWP(robotDrive, 26,

0);
				driveToWPSetMaxSpeed(&worlds1SlowToSecondPile,

35);
			worlds1TurnToShoot2 = initDriveToWP(robotDrive, 0, -137);
			worlds1DriveToShoot2 = initDriveToWP(robotDrive, 10, 0);
			worlds1BackToThirdPile = initDriveToWP(robotDrive, -32,

0);
			worlds1TurnToThirdPile = initDriveToWP(robotDrive, 0, 52);
			worlds1DriveToThirdPile = initDriveToWP(robotDrive, 45,

0);
			worlds1BackToShoot = initDriveToWP(robotDrive, -36, 0);
			worlds1TurnToShoot3 = initDriveToWP(robotDrive, 0, -58);
			worlds1DriveToShoot3 = initDriveToWP(robotDrive, 28, 0);
		}
		else
		{
			worlds1TurnToBump = initDriveToWP(robotDrive, 0, 47);
			worlds1DriveToBump = initDriveToWP(robotDrive, 6*12, 0);
			worlds1TurnToFirstPile = initDriveToWP(robotDrive, 0, 17);
			worlds1DriveToFirstPile = initDriveToWP(robotDrive, 24,

0);
				driveToWPSetMaxSpeed(&worlds1DriveToFirstPile,

40);
			worlds1TurnToShoot1 = initDriveToWP(robotDrive, 0, -54);
			worlds1DriveToShoot1 = initDriveToWP(robotDrive, 22, 0);
			worlds1TurnToSecondPile = initDriveToWP(robotDrive, 0, -

102);
			worlds1DriveToSecondPile = initDriveToWP(robotDrive, 10,

0);
			worlds1SlowToSecondPile = initDriveToWP(robotDrive, 26,

0);
				driveToWPSetMaxSpeed(&worlds1SlowToSecondPile,

35);
			worlds1TurnToShoot2 = initDriveToWP(robotDrive, 0, 145);
			worlds1DriveToShoot2 = initDriveToWP(robotDrive, 16, 0);
			worlds1BackToThirdPile = initDriveToWP(robotDrive, -34,

0);
			worlds1TurnToThirdPile = initDriveToWP(robotDrive, 0, -

55);
			worlds1DriveToThirdPile = initDriveToWP(robotDrive, 49,

0);
			worlds1BackToShoot = initDriveToWP(robotDrive, -40, 0);
			worlds1TurnToShoot3 = initDriveToWP(robotDrive, 0, 55);
			worlds1DriveToShoot3 = initDriveToWP(robotDrive, 34, 0);
		}
	}
	else if(autonomousSelection == WORLDS_2)
	{
		if(alliance == BLUE)
		{
			worlds2TurnToBump = initDriveToWP(robotDrive, 0, -50);
			worlds2DriveToBump = initDriveToWP(robotDrive, 6*12, 0);
			worlds2TurnToFirstPile = initDriveToWP(robotDrive, 0, -

18);
			worlds2DriveToFirstPile = initDriveToWP(robotDrive, 24,

0);
				driveToWPSetMaxSpeed(&worlds2DriveToFirstPile,

40);
			worlds2TurnToShoot1 = initDriveToWP(robotDrive, 0, 51);
			worlds2DriveToShoot1 = initDriveToWP(robotDrive, 22, 0);
			worlds2BackToPile2 = initDriveToWP(robotDrive, -27, 0);
			worlds2TurnToPile2 = initDriveToWP(robotDrive, 0, -65);
			worlds2DriveToPile2 = initDriveToWP(robotDrive, 17.5, 0);
				driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
			worlds2BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
			worlds2TurnToShoot2 = initDriveToWP(robotDrive, 0, 60);
			worlds2DriveToShoot2 = initDriveToWP(robotDrive, 27, 0);
			worlds2TurnToPile3 = initDriveToWP(robotDrive, 0, 97);
			worlds2DriveToPile3 = initDriveToWP(robotDrive, 10, 0);
			worlds2SlowToPile3 = initDriveToWP(robotDrive, 26, 0);
				driveToWPSetMaxSpeed(&worlds2SlowToPile3, 35);
			worlds2TurnToShoot3 = initDriveToWP(robotDrive, 0, -137);
			worlds2DriveToShoot3 = initDriveToWP(robotDrive, 14, 0);
		}
		else
		{
			worlds2TurnToBump = initDriveToWP(robotDrive, 0, 47);
			worlds2DriveToBump = initDriveToWP(robotDrive, 6*12, 0);
			worlds2TurnToFirstPile = initDriveToWP(robotDrive, 0, 17);
			worlds2DriveToFirstPile = initDriveToWP(robotDrive, 24,

0);
				driveToWPSetMaxSpeed(&worlds2DriveToFirstPile,

40);
			worlds2TurnToShoot1 = initDriveToWP(robotDrive, 0, -54);
			worlds2DriveToShoot1 = initDriveToWP(robotDrive, 22, 0);
			worlds2BackToPile2 = initDriveToWP(robotDrive, -27, 0);
			worlds2TurnToPile2 = initDriveToWP(robotDrive, 0, 62);
			worlds2DriveToPile2 = initDriveToWP(robotDrive, 17.5, 0);
				driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
			worlds2BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
			worlds2TurnToShoot2 = initDriveToWP(robotDrive, 0, -58);
			worlds2DriveToShoot2 = initDriveToWP(robotDrive, 27, 0);
			worlds2TurnToPile3 = initDriveToWP(robotDrive, 0, -102);
			worlds2DriveToPile3 = initDriveToWP(robotDrive, 10, 0);
			worlds2SlowToPile3 = initDriveToWP(robotDrive, 26, 0);
				driveToWPSetMaxSpeed(&worlds2SlowToPile3, 35);
			worlds2TurnToShoot3 = initDriveToWP(robotDrive, 0, 130);
			worlds2DriveToShoot3 = initDriveToWP(robotDrive, 14, 0);
		}
	}
	else if(autonomousSelection == WORLDS_3)
	{
		if(alliance == BLUE)
		{
			worlds3TurnToPile1 = initDriveToWP(robotDrive, 0, -62);
			worlds3DriveToPile1 = initDriveToWP(robotDrive, 88, 0);
			worlds3TurnPile2 = initDriveToWP(robotDrive, 0, 45);
			worlds3ThroughPile2 = initDriveToWP(robotDrive, 30, 0);
			worlds3BackToPile3 = initDriveToWP(robotDrive, -20, 0);
			worlds3TurnToPile3 = initDriveToWP(robotDrive, 0, -65);
			worlds3DriveToPile3 = initDriveToWP(robotDrive, 18, 0);
				driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
			worlds3BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
			worlds3TurnToShoot2 = initDriveToWP(robotDrive, 0, 60);
			worlds3DriveToShoot2 = initDriveToWP(robotDrive, 24, 0);
			worlds3TurnToPile4 = initDriveToWP(robotDrive, 0, 97);
			worlds3DriveToPile4 = initDriveToWP(robotDrive, 10, 0);
			worlds3SlowToPile4 = initDriveToWP(robotDrive, 26, 0);
				driveToWPSetMaxSpeed(&worlds3SlowToPile4, 35);
			worlds3TurnToShoot4 = initDriveToWP(robotDrive, 0, -137);
			worlds3DriveToShoot3 = initDriveToWP(robotDrive, 15, 0);
		}
		else
		{
			worlds3TurnToPile1 = initDriveToWP(robotDrive, 0, 59);
			worlds3DriveToPile1 = initDriveToWP(robotDrive, 88, 0);
			worlds3TurnPile2 = initDriveToWP(robotDrive, 0, -48);
			worlds3ThroughPile2 = initDriveToWP(robotDrive, 30, 0);
			worlds3BackToPile3 = initDriveToWP(robotDrive, -20, 0);
			worlds3TurnToPile3 = initDriveToWP(robotDrive, 0, 62);
			worlds3DriveToPile3 = initDriveToWP(robotDrive, 18, 0);
				driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
			worlds3BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
			worlds3TurnToShoot2 = initDriveToWP(robotDrive, 0, -63);
			worlds3DriveToShoot2 = initDriveToWP(robotDrive, 24, 0);
			worlds3TurnToPile4 = initDriveToWP(robotDrive, 0, -102);
			worlds3DriveToPile4 = initDriveToWP(robotDrive, 10, 0);
			worlds3SlowToPile4 = initDriveToWP(robotDrive, 26, 0);
				driveToWPSetMaxSpeed(&worlds3SlowToPile4, 35);
			worlds3TurnToShoot4 = initDriveToWP(robotDrive, 0, 130);
			worlds3DriveToShoot3 = initDriveToWP(robotDrive, 15, 0);
		}
	}
	else if(autonomousSelection == WORLDS_4)
	{
		if(alliance == BLUE)
		{
			 worlds4TurnToDrive = initDriveToWP(robotDrive, 0, -40);
			 worlds4Drive = initDriveToWP(robotDrive, 58, 0);
			 worlds4TurnToPile1 = initDriveToWP(robotDrive, 0, 80);
			 worlds4DriveToPile1 = initDriveToWP(robotDrive, 43, 0);
			 worlds4BackToShoot1 = initDriveToWP(robotDrive, -35, 0);
			 worlds4TurnToShoot1 = initDriveToWP(robotDrive, 0, -85);
			 worlds4DriveToShoot1 = initDriveToWP(robotDrive, 24, 0);
			 worlds4SlowToPile2 = initDriveToWP(robotDrive, 12, 0);
				 driveToWPSetMaxSpeed(&worlds4SlowToPile2, 35);
			 worlds4DriveToShoot2 = initDriveToWP(robotDrive, 24, 0);
		}
		else
		{
			worlds4TurnToDrive = initDriveToWP(robotDrive, 0, 38);
			worlds4Drive = initDriveToWP(robotDrive, 58, 0);
			worlds4TurnToPile1 = initDriveToWP(robotDrive, 0, -85);
			worlds4DriveToPile1 = initDriveToWP(robotDrive, 43, 0);
			worlds4BackToShoot1 = initDriveToWP(robotDrive, -35, 0);
			worlds4TurnToShoot1 = initDriveToWP(robotDrive, 0, 81);
			worlds4DriveToShoot1 = initDriveToWP(robotDrive, 24, 0);
			worlds4SlowToPile2 = initDriveToWP(robotDrive, 12, 0);
				driveToWPSetMaxSpeed(&worlds4SlowToPile2, 35);
			worlds4DriveToShoot2 = initDriveToWP(robotDrive, 24, 0);
		}
	}
	else if(autonomousSelection == WORLDS_5)
	{
		if(alliance == BLUE)
		{
			worlds5TurnToShoot1 = initDriveToWP(robotDrive, 0, -50);
			worlds5DriveToShoot1 = initDriveToWP(robotDrive, 100, 0);
			worlds5TurnToGoal1 = initDriveToWP(robotDrive, 0, 36);
			worlds5TurnToPile2 = initDriveToWP(robotDrive, 0, 84);
			worlds5DriveToPile2 = initDriveToWP(robotDrive, 14, 0);
			worlds5SlowToPile2 = initDriveToWP(robotDrive, 5, 0);
				driveToWPSetMaxSpeed(&worlds5SlowToPile2, 65);
			worlds5FastToPile2 = initDriveToWP(robotDrive, 27, 0);
			worlds5TurnToShoot2 = initDriveToWP(robotDrive, 0, -130);
			worlds5TurnToPile3 = initDriveToWP(robotDrive, 0, 70);
			worlds5DriveToPile3 = initDriveToWP(robotDrive, 30, 0);
			worlds5BackToShoot3 = initDriveToWP(robotDrive, -30, 0);
			worlds5TurnToShoot3 = initDriveToWP(robotDrive, 0, -73);
		}
		else
		{
			worlds5TurnToShoot1 = initDriveToWP(robotDrive, 0, 47);
			worlds5DriveToShoot1 = initDriveToWP(robotDrive, 114, 0);
			worlds5TurnToGoal1 = initDriveToWP(robotDrive, 0, -38);
			worlds5TurnToPile2 = initDriveToWP(robotDrive, 0, -89);
			worlds5DriveToPile2 = initDriveToWP(robotDrive, 14, 0);
			worlds5SlowToPile2 = initDriveToWP(robotDrive, 5, 0);
				driveToWPSetMaxSpeed(&worlds5SlowToPile2, 65);
			worlds5FastToPile2 = initDriveToWP(robotDrive, 27, 0);
			worlds5TurnToShoot2 = initDriveToWP(robotDrive, 0, 123);
			worlds5TurnToPile3 = initDriveToWP(robotDrive, 0, -70);
			worlds5DriveToPile3 = initDriveToWP(robotDrive, 30, 0);
			worlds5BackToShoot3 = initDriveToWP(robotDrive, -30, 0);
			worlds5TurnToShoot3 = initDriveToWP(robotDrive, 0, 69);
		}

	}
	else if(autonomousSelection == TURN_TEST)
	{
		if(alliance == BLUE)
		{
			turn90 = initDriveToWP(robotDrive, 96, 0);
		}
		else
		{
			turn90 = initDriveToWP(robotDrive, 96, 0);
		}
	}
	else if(autonomousSelection == WORLDS_FEED)
	{
		if(alliance == BLUE)
		{
			worldsfeedTurnToClear = initDriveToWP(robotDrive, 0, -30);
			worldsfeedDriveToSet = initDriveToWP(robotDrive, 14, 0);
			worldsfeedTurnToFeed = initDriveToWP(robotDrive, 0, 135);
			worldsfeedDriveToFeed = initDriveToWP(robotDrive, 9, 0);
			worldsfeedBackToPile1 = initDriveToWP(robotDrive, -3, 0);
			worldsfeedTurnToPile1 = initDriveToWP(robotDrive, 0, -85);
			worldsfeedDriveToPile1 = initDriveToWP(robotDrive, 32, 0);
			worldsfeedDriveToPile1Slow = initDriveToWP(robotDrive, 4, 0);
				driveToWPSetMaxSpeed(&worldsfeedDriveToPile1Slow, 80);
			worldsfeedDriveThroughPile1 = initDriveToWP(robotDrive, 8, 0);
			worldsfeedBackToFeed2 = initDriveToWP(robotDrive, -44, 0);
			worldsfeedTurnToFeed2 = initDriveToWP(robotDrive, 0, 85);
			worldsfeedBackToPile3 = initDriveToWP(robotDrive, -12, 0);
			worldsfeedTurnToPile3 = initDriveToWP(robotDrive, 0, -90);
			worldsfeedDriveToPile3 = initDriveToWP(robotDrive, 6, 0);
			worldsfeedSlowToPile3 = initDriveToWP(robotDrive, 4, 0);
				driveToWPSetMaxSpeed(&worldsfeedSlowToPile3, 80);
			worldsfeedDriveThroughPile3 = initDriveToWP(robotDrive, 12, 0);
			worldsfeedTurnToFeed3 = initDriveToWP(robotDrive, 0, 120);
			worldsfeedDriveToFeed3 = initDriveToWP(robotDrive, 20, 0);
		}
		else
		{

		}

	}
	else if(autonomousSelection == WORLDS_6)
	{
		if(alliance == BLUE)
		{
			worlds6TurnToPile1 = initDriveToWP(robotDrive, 0, -62);
			worlds6DriveToPile1 = initDriveToWP(robotDrive, 88, 0);
			worlds6TurnPile2 = initDriveToWP(robotDrive, 0, 43);
			worlds6ThroughPile2 = initDriveToWP(robotDrive, 34, 0);
			worlds6BackToPile3 = initDriveToWP(robotDrive, -24, 0);
			worlds6TurnToPile3 = initDriveToWP(robotDrive, 0, -65);
			worlds6DriveToPile3 = initDriveToWP(robotDrive, 18, 0);
				driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
			worlds6BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
			worlds6TurnToShoot2 = initDriveToWP(robotDrive, 0, 57);
			worlds6DriveToShoot2 = initDriveToWP(robotDrive, 24, 0);
			worlds6BackToClean = initDriveToWP(robotDrive, -18, 0);
			worlds6TurnToClean = initDriveToWP(robotDrive, 0, -70);
			worlds6DriveToClean = initDriveToWP(robotDrive, 17, 0);
			worlds6BackToShoot3 = initDriveToWP(robotDrive, -17, 0);
			worlds6TurnToShoot3 = initDriveToWP(robotDrive, 0, 70);
			worlds6DriveToShoot3 = initDriveToWP(robotDrive, 18, 0);
		}
		else
		{
			worlds6TurnToPile1 = initDriveToWP(robotDrive, 0, 54);
			worlds6DriveToPile1 = initDriveToWP(robotDrive, 88, 0);
			worlds6TurnPile2 = initDriveToWP(robotDrive, 0, -48);
			worlds6ThroughPile2 = initDriveToWP(robotDrive, 30, 0);
			worlds6BackToPile3 = initDriveToWP(robotDrive, -20, 0);
			worlds6TurnToPile3 = initDriveToWP(robotDrive, 0, 62);
			worlds6DriveToPile3 = initDriveToWP(robotDrive, 18, 0);
				driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
			worlds6BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
			worlds6TurnToShoot2 = initDriveToWP(robotDrive, 0, -63);
			worlds6DriveToShoot2 = initDriveToWP(robotDrive, 24, 0);
			worlds6BackToClean = initDriveToWP(robotDrive, -18, 0);
			worlds6TurnToClean = initDriveToWP(robotDrive, 0, 70);
			worlds6DriveToClean = initDriveToWP(robotDrive, 17, 0);
			worlds6BackToShoot3 = initDriveToWP(robotDrive, -17, 0);
			worlds6TurnToShoot3 = initDriveToWP(robotDrive, 0, -70);
			worlds6DriveToShoot3 = initDriveToWP(robotDrive, 18, 0);
		}
	}

	autonomousInfo.lastStep = 0;
	autonomousInfo.step = 1;
	autonomousInfo.isFinished = 0;

	stepStartTime = millis();
}

/**
 * Runs continuously during autonomous, should exit relatively promptly.
 */
void autonomousPeriodic()
{
	if(autonomousInfo.step != autonomousInfo.lastStep)
	{
		stepStartTime = millis();
	}

	autonomousInfo.elapsedTime = millis() - stepStartTime;

	lcdPrint(uart1, 1, "Step: %d", autonomousInfo.step);

	switch(autonomousSelection)
	{
		case(WORLDS_1):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&worlds1TurnToBump);
				turnShooterOn(&robotShooter);
				shootFender(&robotShooter);
				ballStopperDown(&robotStopper);

				autonomousInfo.isFinished =

worlds1TurnToBump.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(2):
				driveToWP(&worlds1DriveToBump);
				autonomousInfo.isFinished =

worlds1DriveToBump.isFinished;
				break;
			case(3):
				driveToWP(&worlds1TurnToFirstPile);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished =

worlds1TurnToFirstPile.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(4):
				driveToWP(&worlds1DriveToFirstPile);
				autonomousInfo.isFinished =

worlds1DriveToFirstPile.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(5):
				driveToWP(&worlds1TurnToShoot1);
				autonomousInfo.isFinished =

worlds1TurnToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(6):
				driveToWP(&worlds1DriveToShoot1);
				intake1Stop(&robotIntake);
				intake2Stop(&robotIntake);
				autonomousInfo.isFinished =

worlds1DriveToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(7):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 4000;
				break;



			case(8):
				driveToWP(&worlds1TurnToSecondPile);
				ballStopperDown(&robotStopper);
				intake1Out(&robotIntake);
				autonomousInfo.isFinished =

worlds1TurnToSecondPile.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(9):
			driveToWP(&worlds1DriveToSecondPile);
			intake1In(&robotIntake);
			autonomousInfo.isFinished =

worlds1DriveToSecondPile.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(10):
			driveToWP(&worlds1SlowToSecondPile);
			autonomousInfo.isFinished =

worlds1SlowToSecondPile.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(11):
			driveToWP(&worlds1TurnToShoot2);
			autonomousInfo.isFinished = worlds1TurnToShoot2.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(12):
			driveToWP(&worlds1DriveToShoot2);
			autonomousInfo.isFinished =

worlds1DriveToShoot2.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(13):
			ballStopperUp(&robotStopper);
			autonomousInfo.isFinished = autonomousInfo.elapsedTime >

3500;
			break;

			case(14):
			driveToWP(&worlds1BackToThirdPile);
			ballStopperDown(&robotStopper);
			intake1Out(&robotIntake);
			autonomousInfo.isFinished =

worlds1BackToThirdPile.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(15):
			driveToWP(&worlds1TurnToThirdPile);
			intake1In(&robotIntake);
			autonomousInfo.isFinished =

worlds1TurnToThirdPile.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(16):
			driveToWP(&worlds1DriveToThirdPile);
			autonomousInfo.isFinished =

(worlds1DriveToThirdPile.isFinished
					&& autonomousInfo.elapsedTime > 4000)
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(17):
			driveToWP(&worlds1BackToShoot);
			autonomousInfo.isFinished = worlds1BackToShoot.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(18):
			driveToWP(&worlds1TurnToShoot3);
			autonomousInfo.isFinished = worlds1TurnToShoot3.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(19):
			driveToWP(&worlds1DriveToShoot3);
			autonomousInfo.isFinished =

worlds1DriveToShoot3.isFinished
					|| autonomousInfo.elapsedTime >

globalTimeout;
			break;

			case(20):
			ballStopperUp(&robotStopper);
			intake1In(&robotIntake);
			intake2In(&robotIntake);
			autonomousInfo.isFinished = autonomousInfo.elapsedTime >

4000;
			break;

			default:
				isAuto = 0;
				break;
			}

		break;

		case(WORLDS_2):
			switch(autonomousInfo.step)
			{
			case(1):
					driveToWP(&worlds2TurnToBump);
					turnShooterOn(&robotShooter);
					shootFender(&robotShooter);
					ballStopperDown(&robotStopper);

					autonomousInfo.isFinished =

worlds2TurnToBump.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(2):
					driveToWP(&worlds2DriveToBump);
					autonomousInfo.isFinished =

worlds2DriveToBump.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(3):
					driveToWP(&worlds2TurnToFirstPile);
					intake1In(&robotIntake);
					intake2In(&robotIntake);
					autonomousInfo.isFinished =

worlds2TurnToFirstPile.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(4):
					driveToWP(&worlds2DriveToFirstPile);
					autonomousInfo.isFinished =

worlds2DriveToFirstPile.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(5):
					driveToWP(&worlds2TurnToShoot1);
					autonomousInfo.isFinished =

worlds2TurnToShoot1.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(6):
					driveToWP(&worlds2DriveToShoot1);
					intake1Stop(&robotIntake);
					intake2Stop(&robotIntake);
					autonomousInfo.isFinished =

worlds2DriveToShoot1.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(7):
					ballStopperUp(&robotStopper);
					intake1In(&robotIntake);
					intake2In(&robotIntake);
					autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 3500;
					break;
				case(8):
					driveToWP(&worlds2BackToPile2);
					ballStopperDown(&robotStopper);
					intake1Out(&robotIntake);
					autonomousInfo.isFinished =

worlds2BackToPile2.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(9):
					driveToWP(&worlds2TurnToPile2);
					intake1In(&robotIntake);
					autonomousInfo.isFinished =

worlds2TurnToPile2.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(10):
					driveToWP(&worlds2DriveToPile2);
					autonomousInfo.isFinished =

worlds2DriveToPile2.isFinished
							||

autonomousInfo.elapsedTime > 3500;
					break;
				case(11):
					driveToWP(&worlds2BackToShoot2);
					autonomousInfo.isFinished =

worlds2BackToShoot2.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(12):
					driveToWP(&worlds2TurnToShoot2);
					autonomousInfo.isFinished =

worlds2TurnToShoot2.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(13):
					driveToWP(&worlds2DriveToShoot2);
					autonomousInfo.isFinished =

worlds2DriveToShoot2.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(14):
					ballStopperUp(&robotStopper);
					intake1In(&robotIntake);
					intake2In(&robotIntake);
					autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 3500;
					break;
				case(15):
					driveToWP(&worlds2TurnToPile3);
					ballStopperDown(&robotStopper);
					intake1Out(&robotIntake);
					autonomousInfo.isFinished =

worlds2TurnToPile3.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;
				case(16):
					driveToWP(&worlds2DriveToPile3);
					intake1In(&robotIntake);
					autonomousInfo.isFinished =

worlds2DriveToPile3.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
					break;

				case(17):
					driveToWP(&worlds2SlowToPile3);
					autonomousInfo.isFinished =

worlds2SlowToPile3.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
				break;

				case(18):
					driveToWP(&worlds2TurnToShoot3);
					autonomousInfo.isFinished =

worlds2TurnToShoot3.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
				break;

				case(19):
					driveToWP(&worlds2DriveToShoot3);
					autonomousInfo.isFinished =

worlds2DriveToShoot3.isFinished
							||

autonomousInfo.elapsedTime > globalTimeout;
				break;

				case(20):
					ballStopperUp(&robotStopper);
					autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 3500;
				break;


			default:
				isAuto = 0;
			}
		break;


		case(WORLDS_3):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&worlds3TurnToPile1);
				turnShooterOn(&robotShooter);
				shootFender(&robotShooter);
				ballStopperDown(&robotStopper);
				autonomousInfo.isFinished = worlds3TurnToPile1.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(2):
				driveToWP(&worlds3DriveToPile1);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = worlds3DriveToPile1.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(3):
				driveToWP(&worlds3TurnPile2);
				autonomousInfo.isFinished = worlds3TurnPile2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(4):
				driveToWP(&worlds3ThroughPile2);
				autonomousInfo.isFinished = worlds3ThroughPile2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(5):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
				break;
			case(6):
				driveToWP(&worlds3BackToPile3);
				ballStopperDown(&robotStopper);
				intake1Out(&robotIntake);
				autonomousInfo.isFinished = worlds3BackToPile3.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(7):
				driveToWP(&worlds3TurnToPile3);
				intake1In(&robotIntake);
				autonomousInfo.isFinished = worlds3TurnToPile3.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(8):
				driveToWP(&worlds3DriveToPile3);
				autonomousInfo.isFinished = worlds3BackToShoot2.isFinished
						|| autonomousInfo.elapsedTime > 3000;
				break;
			case(9):
				driveToWP(&worlds3BackToShoot2);
				autonomousInfo.isFinished = worlds3BackToShoot2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(10):
				driveToWP(&worlds3TurnToShoot2);
				autonomousInfo.isFinished = worlds3TurnToShoot2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(11):
				driveToWP(&worlds3DriveToShoot2);
				autonomousInfo.isFinished = worlds3DriveToShoot2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(12):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
				break;
			case(13):
				driveToWP(&worlds3TurnToPile4);
				intake1Out(&robotIntake);
				autonomousInfo.isFinished = worlds3TurnToPile4.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(14):
				driveToWP(&worlds3DriveToPile4);
				ballStopperDown(&robotStopper);
				intake1In(&robotIntake);
				autonomousInfo.isFinished = worlds3DriveToPile4.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(15):
				driveToWP(&worlds3SlowToPile4);
				autonomousInfo.isFinished = worlds3SlowToPile4.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(16):
				driveToWP(&worlds3TurnToShoot4);
				autonomousInfo.isFinished = worlds3TurnToShoot4.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(17):
				driveToWP(&worlds3DriveToShoot3);
				autonomousInfo.isFinished = worlds3DriveToShoot3.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(18):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
				break;
			default:
				isAuto = 0;
				break;
			}
		break;

		case(WORLDS_4):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&worlds4TurnToDrive);
				ballStopperDown(&robotStopper);
				turnShooterOn(&robotShooter);
				shootHalfCourt(&robotShooter);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished =

worlds4TurnToDrive.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(2):
				driveToWP(&worlds4Drive);
				autonomousInfo.isFinished =

worlds4Drive.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(3):
				driveToWP(&worlds4TurnToPile1);
				autonomousInfo.isFinished =

worlds4TurnToPile1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(4):
				driveToWP(&worlds4DriveToPile1);
				autonomousInfo.isFinished =

worlds4DriveToPile1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(5):
				driveToWP(&worlds4BackToShoot1);
				autonomousInfo.isFinished =

worlds4BackToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(6):
				driveToWP(&worlds4TurnToShoot1);
				autonomousInfo.isFinished =

worlds4TurnToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(7):
				driveToWP(&worlds4DriveToShoot1);
				autonomousInfo.isFinished =

worlds4DriveToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(8):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 4000;
				break;

			default:
				isAuto = 0;
				break;
			}
			break;

			case(WORLDS_5):
			switch(autonomousInfo.step)
			{
			case(1):
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 5000;
				break;
			case(2):
				turnShooterOn(&robotShooter);
				shootFender(&robotShooter);
				ballStopperDown(&robotStopper);
				driveToWP(&worlds5TurnToShoot1);
				autonomousInfo.isFinished =

worlds5TurnToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(3):
				driveToWP(&worlds5DriveToShoot1);
				autonomousInfo.isFinished =

worlds5DriveToShoot1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(4):
				driveToWP(&worlds5TurnToGoal1);
				autonomousInfo.isFinished =

worlds5TurnToGoal1.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(5):
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				ballStopperUp(&robotStopper);
				autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 5000;
				break;
			case(6):
				driveToWP(&worlds5TurnToPile2);
				intake1Out(&robotIntake);
				autonomousInfo.isFinished =

worlds5TurnToPile2.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(7):
				driveToWP(&worlds5DriveToPile2);
				ballStopperDown(&robotStopper);
				shootHalfCourt(&robotShooter);
				intake1In(&robotIntake);
				autonomousInfo.isFinished =

worlds5DriveToPile2.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(8):
				driveToWP(&worlds5SlowToPile2);
				autonomousInfo.isFinished =

worlds5SlowToPile2.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(9):
				driveToWP(&worlds5FastToPile2);
				autonomousInfo.isFinished =

worlds5FastToPile2.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(10):
				driveToWP(&worlds5TurnToShoot2);
				autonomousInfo.isFinished =

worlds5TurnToShoot2.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(11):
				ballStopperUp(&robotStopper);
				autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 5000;
				break;
			case(12):
				driveToWP(&worlds5TurnToPile3);
				ballStopperDown(&robotStopper);
				intake1Out(&robotIntake);
				autonomousInfo.isFinished =

worlds5TurnToPile3.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(13):
				driveToWP(&worlds5DriveToPile3);
				intake1In(&robotIntake);
				autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 5000;
				break;
			case(14):
				driveToWP(&worlds5BackToShoot3);
				autonomousInfo.isFinished =

worlds5BackToShoot3.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(15):
				driveToWP(&worlds5TurnToShoot3);
				autonomousInfo.isFinished =

worlds5TurnToShoot3.isFinished
						|| autonomousInfo.elapsedTime >

globalTimeout;
				break;
			case(16):
				ballStopperUp(&robotStopper);
				autonomousInfo.isFinished =

autonomousInfo.elapsedTime > 5000;
				break;



			default:
				isAuto = 0;
				break;
			}
			break;

			case(TURN_TEST):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&turn90);
				autonomousInfo.isFinished = turn90.isFinished;
				break;
			default:
				isAuto = 0;
			}
			break;

			case(WORLDS_FEED):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&worldsfeedTurnToClear);
				ballStopperDown(&robotStopper);
				autonomousInfo.isFinished = worldsfeedTurnToClear.isFinished;
				break;
			case(2):
				driveToWP(&worldsfeedDriveToSet);
				autonomousInfo.isFinished = worldsfeedDriveToSet.isFinished;
				break;
			case(3):
				tankDrive(robotDrive, 0, 0);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 5000;
				break;
			case(4):
				driveToWP(&worldsfeedTurnToFeed);
				autonomousInfo.isFinished = worldsfeedTurnToFeed.isFinished;
				break;
			case(5):
				driveToWP(&worldsfeedDriveToFeed);
				autonomousInfo.isFinished = worldsfeedDriveToFeed.isFinished;
				break;
			case(6):
				intake1Auto(&robotIntake);
				intake2Out(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3500;
				break;
			case(7):
				driveToWP(&worldsfeedBackToPile1);
				autonomousInfo.isFinished = worldsfeedBackToPile1.isFinished;
				break;
			case(8):
				driveToWP(&worldsfeedTurnToPile1);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = worldsfeedTurnToPile1.isFinished;
				break;
			case(9):
				driveToWP(&worldsfeedDriveToPile1);
				autonomousInfo.isFinished = worldsfeedDriveToPile1.isFinished;
				break;
			case(10):
				driveToWP(&worldsfeedDriveToPile1Slow);
				autonomousInfo.isFinished = worldsfeedDriveToPile1Slow.isFinished;
				break;
			case(11):
				driveToWP(&worldsfeedDriveThroughPile1);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3000;
				break;
			case(12):
				driveToWP(&worldsfeedBackToFeed2);
				autonomousInfo.isFinished = worldsfeedBackToFeed2.isFinished;
				break;
			case(13):
				driveToWP(&worldsfeedTurnToFeed2);
				autonomousInfo.isFinished = worldsfeedTurnToFeed2.isFinished;
				break;
			case(14):
				intake1Auto(&robotIntake);
				intake2Out(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4500;
				break;
			case(15):
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				driveToWP(&worldsfeedBackToPile3);
				autonomousInfo.isFinished = worldsfeedBackToPile3.isFinished;
				break;
			case(16):
				driveToWP(&worldsfeedTurnToPile3);
				autonomousInfo.isFinished = worldsfeedTurnToPile3.isFinished;
				break;
			case(17):
				driveToWP(&worldsfeedDriveToPile3);
				autonomousInfo.isFinished = worldsfeedDriveToPile3.isFinished;
				break;
			case(18):
				driveToWP(&worldsfeedSlowToPile3);
				autonomousInfo.isFinished = worldsfeedSlowToPile3.isFinished;
				break;
			case(19):
				driveToWP(&worldsfeedDriveThroughPile3);
				autonomousInfo.isFinished = worldsfeedDriveThroughPile3.isFinished;
				break;
			case(20):
				driveToWP(&worldsfeedTurnToFeed3);
				autonomousInfo.isFinished = worldsfeedTurnToFeed3.isFinished;
				break;
			case(21):
				driveToWP(&worldsfeedDriveToFeed3);
				autonomousInfo.isFinished = worldsfeedDriveToFeed3.isFinished;
				break;
			case(22):
				intake1Auto(&robotIntake);
				intake2Out(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4500;
				break;
			default:
				isAuto = 0;
			}
			break;
			case(WORLDS_6):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&worlds6TurnToPile1);
				turnShooterOn(&robotShooter);
				shootFender(&robotShooter);
				ballStopperDown(&robotStopper);
				autonomousInfo.isFinished = worlds6TurnToPile1.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(2):
				driveToWP(&worlds6DriveToPile1);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = worlds6DriveToPile1.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(3):
				driveToWP(&worlds6TurnPile2);
				autonomousInfo.isFinished = worlds6TurnPile2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(4):
				driveToWP(&worlds6ThroughPile2);
				autonomousInfo.isFinished = worlds6ThroughPile2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(5):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
				break;
			case(6):
				driveToWP(&worlds6BackToPile3);
				ballStopperDown(&robotStopper);
				intake1Out(&robotIntake);
				autonomousInfo.isFinished = worlds6BackToPile3.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(7):
				driveToWP(&worlds6TurnToPile3);
				intake1In(&robotIntake);
				autonomousInfo.isFinished = worlds6TurnToPile3.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(8):
				driveToWP(&worlds6DriveToPile3);
				autonomousInfo.isFinished = worlds6BackToShoot2.isFinished
						|| autonomousInfo.elapsedTime > 3000;
				break;
			case(9):
				driveToWP(&worlds6BackToShoot2);
				autonomousInfo.isFinished = worlds6BackToShoot2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(10):
				driveToWP(&worlds6TurnToShoot2);
				autonomousInfo.isFinished = worlds6TurnToShoot2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(11):
				driveToWP(&worlds6DriveToShoot2);
				autonomousInfo.isFinished = worlds6DriveToShoot2.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(12):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
				break;
			case(13):
				ballStopperDown(&robotStopper);
				driveToWP(&worlds6BackToClean);
				autonomousInfo.isFinished = worlds6BackToClean.isFinished
						|| autonomousInfo.elapsedTime > globalTimeout;
				break;
			case(14):
							driveToWP(&worlds6TurnToClean);
							autonomousInfo.isFinished = worlds6TurnToClean.isFinished
									|| autonomousInfo.elapsedTime > globalTimeout;
							break;
			case(15):
							driveToWP(&worlds6DriveToClean);
							autonomousInfo.isFinished = worlds6DriveToClean.isFinished
									|| autonomousInfo.elapsedTime > globalTimeout;
							break;
			case(16):
							driveToWP(&worlds6BackToShoot3);
							autonomousInfo.isFinished = worlds6BackToShoot3.isFinished
									|| autonomousInfo.elapsedTime > globalTimeout;
							break;
			case(17):
							driveToWP(&worlds6TurnToShoot3);
							autonomousInfo.isFinished = worlds6TurnToShoot3.isFinished
									|| autonomousInfo.elapsedTime > globalTimeout;
							break;
			case(18):
							driveToWP(&worlds6DriveToShoot3);
							autonomousInfo.isFinished = worlds6DriveToShoot3.isFinished
									|| autonomousInfo.elapsedTime > globalTimeout;
							break;

			/*worlds6BackToClean = initDriveToWP(robotDrive, -18, 0);
			worlds6TurnToClean = initDriveToWP(robotDrive, 0, -70);
			worlds6DriveToClean = initDriveToWP(robotDrive, 8, 0);
			worlds6BackToShoot3 = initDriveToWP(robotDrive, -8, 0);
			worlds6TurnToShoot3 = initDriveToWP(robotDrive, 0, 70);
			worlds6DriveToShoot3 = initDriveToWP(robotDrive, 18, 0);*/
			default:
				isAuto = 0;
				break;
			}
		break;
		/*case(DO_NOTHING):
			isAuto = 0;
		break;*/
				default:
					isAuto = 0;
					break;


	}

	runShooter(&robotShooter);
	runBallStopper(&robotStopper);
	runIntake(&robotIntake);

	autonomousInfo.lastStep = autonomousInfo.step;

	//lcdPrint(uart1, 1, "Step: %d", autonomousInfo.step);

	if(autonomousInfo.isFinished)
	{
		autonomousInfo.step ++;
		autonomousInfo.isFinished = 0;
	}

}

void autonomous()
{
	lcdSetText(uart1, 1, "started");

	autonomousInit();

	//lcdSetText(uart1, 1, "initialized");

	while(isAuto)
	{
		autonomousPeriodic();

		if(isOnline())
		{
			if(!isAutonomous() || !isEnabled()) isAuto = 0;
		}

		delay(20);

		//puts("Autonomous");
	}
}

