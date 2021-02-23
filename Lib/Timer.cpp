/*
 * Timer.cpp
 *
 *  Created on: 23 févr. 2021
 *      Author: pierr
 */

#include <Lib/Timer.h>

Timer::Timer()
{
   // timer initiation
   TACTL |= TASSEL_2; // use SMCLK not diviser and not run
   // memorize timer isn't run
   mIsRun = false;
}

void Timer::Run(void)
{
    // clear the timer
    TACTL |= TACLR;
    // run the timer on count mode
    TACTL |= MC_2;
    // memorize timer is run
    mIsRun = true;
}

void Timer::Stop(void)
{
    // clear the timer
    TACTL |= TACLR;
    // stop the timer
    TACTL |= MC_0;
    // memorize timer is run
    mIsRun = false;
}

unsigned int Timer::getValue(void)
{
    return TAR;
}

bool Timer::isRun(void)
{
    return mIsRun;
}


