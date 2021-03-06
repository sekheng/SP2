/******************************************************************************/
/*!
\file       main.cpp
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief
The main primary function that will be run.
Taken from Mr Tang's framework
*/
/******************************************************************************/

#include "Application.h"

/******************************************************************************/
/*!
\brief -
the primary functions that the program will run

\return 0
*/
/******************************************************************************/
int main(void)
{
	Application app;
	app.Init();
	app.Run();
	app.Exit();
}