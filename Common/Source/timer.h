/******************************************************************************/
/*!
\file       timer.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Taken from Mr Tang's framework
This is creating a class for real time
*/
/******************************************************************************/
#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

/******************************************************************************/
/*!
Class StopWatch:
\brief
Creating a real time based timer
*/
/******************************************************************************/
class StopWatch
{
 
 private:
     
    LARGE_INTEGER frequency;
    LARGE_INTEGER prevTime, currTime;
    double LIToSecs( LARGE_INTEGER & L) ;
    UINT     wTimerRes;

 public:
     StopWatch() ;
     ~StopWatch();
     void startTimer();
     double getElapsedTime(); // get time in seconds since the last call to this function
     void waitUntil(long long time);  // wait until this time in milliseconds has passed
 };


#endif // _TIMER_H