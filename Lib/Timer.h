/*
 * Timer.h
 *
 *  Created on: 23 févr. 2021
 *      Author: pierr
 */

#ifndef LIB_TIMER_H_
#define LIB_TIMER_H_

#include <msp430.h>

class Timer
{
public:
    Timer();
    void Run(void);
    void Stop(void);
    unsigned int getValue(void);
    bool isRun(void);
private:
    bool mIsRun;
};

#endif /* LIB_TIMER_H_ */
