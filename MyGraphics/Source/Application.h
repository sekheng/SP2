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
#include "DetectMemoryLeak.h"
#include "GameObject.h"
#include "scene2_SP2.h"
#include "sceneSP2.h"
#include "scene3_SP2.h"
#include "BGMDriven.h"
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

    static void changeIntoScenario3();
    static void changeIntoScenario1();
    static void changeIntoScenario2();

    BGMDriven *musics;
private:
    static Scene *scene;
    static Scene * scenario1;
    static Scene *scenario3;
    static Scene *scenario2;
	//Declare a window object
	StopWatch m_timer;
};

#endif