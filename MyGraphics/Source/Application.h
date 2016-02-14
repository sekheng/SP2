/******************************************************************************/
/*!
\file       Application.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief
The functions that is being run in main.cpp
Taken from Mr Tang's original framework
*/
/******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "sceneSP2.h"
#include "DetectMemoryLeak.h"
#include "GameObject.h"
/******************************************************************************/
/*!
Class Application:
\brief      
Where the glfw and glew do their stuff
At the run will be where the game stuff comes in
*/
/******************************************************************************/
class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif