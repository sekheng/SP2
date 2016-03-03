#include "StationScene.h"
#include "MyMath.h"
#include "Application.h"
/******************************************************************************/
/*!
\brief - a default constructor, with all variables becoming default value
*/
/******************************************************************************/
StationScene::StationScene() : GameObject("Door")
{

}
StationScene::~StationScene()
{

}

/******************************************************************************/
/*!
\brief - init the variable that are needed 
*/
/******************************************************************************/
void StationScene::Init(Camera3 &camera_address)
{
	cam_pointer = &camera_address;
	time = 0;
	questActive = false;
	card1 = false;
	card2 = false;
	questComplete = false;
	doorOpened = false;
	switchLightOn = true;
	delay = 0.5f;
}

/******************************************************************************/
/*!
\brief - enable to collect card if is within the boundary

\return - 1 when is taken

\return - 0 if is not taken
*/
/******************************************************************************/

short StationScene::getCard1()
{
	if (cam_pointer->position.x > -259 && cam_pointer->position.x < -258 && cam_pointer->position.z > 303 && cam_pointer->position.z < 308 && questActive == true && card1 == false)
	{
		if (Application::IsKeyPressed('E'))
		{
			card1 = true;
			count++;
		}
	}
	else if (card1 == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}


/******************************************************************************/
/*!
\brief - enable to collect card if is within the boundary

\return - 1 when is taken

\return - 0 if is not taken
*/
/******************************************************************************/
short StationScene::getCard2()
{
	if (cam_pointer->position.x > -294 && cam_pointer->position.x < -293 && cam_pointer->position.z > 290 && cam_pointer->position.z < 293 && questActive == true && card2 == false)
	{
		if (Application::IsKeyPressed('E'))
		{
			card2 = true;
			count++;
		}
	}
	else if (card2 == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}


/******************************************************************************/
/*!
\brief - show text only with the interacting boundary

\return - true if the player is inside it's interacting boundary

\return - false if the player is outside it's interacting boundary
*/
/******************************************************************************/
bool StationScene::getCardText()
{
	if (cam_pointer->position.x > -259 && cam_pointer->position.x < -258 && cam_pointer->position.z > 303 && cam_pointer->position.z < 308 && questActive == true && card1 == false)
	{
		return true;
	}
	else if (cam_pointer->position.x > -294 && cam_pointer->position.x < -293 && cam_pointer->position.z > 290 && cam_pointer->position.z < 293 && questActive == true && card2 == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************/
/*!
\brief - to check to check whether what stage his in to open door 

\return - 1 to tell player press E to open the door

\return - 2 to tell player that 2  keycard is needed to open

\return - 3 to spawn the card into the world 
*/
/******************************************************************************/

short StationScene::getQuestStage()
{
	if (questComplete == false)
	{
		if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 250 && cam_pointer->position.z < 270 && questActive == false)
		{
			if (Application::IsKeyPressed('E'))
			{
				questActive = true;
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 250 && cam_pointer->position.z < 270 && questActive == true)
		{
			return 2;
		}
		else if (questActive == true)
		{
			return 3;
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

/******************************************************************************/
/*!
\brief - to check whether the player taken 2 card and if 2 card is taken door can now be open after you press E

\return - 1 if the player has not open the door

\return - 2 if the player has open the door
*/
/******************************************************************************/
short StationScene::openSasame()
{
	if (card1 == true && card2 == true)
	{
		questComplete = true;
		if(cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 250 && cam_pointer->position.z < 270 && doorOpened == false)
		{
			if (Application::IsKeyPressed('E'))
			{ 
				doorOpened = true;
			}
			return 1;
		}
		else if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 250 && cam_pointer->position.z < 270 && doorOpened == true)
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

/******************************************************************************/
/*!
\brief - to check whether the player in within it's interacting boundary to toggle the light

\return - true if the player is inside it's interacting boundary and whether E is press switch ON the light 

\return - false if the player is inside it's interacting boundary and whether E is press switch off the light 
*/
/******************************************************************************/
bool StationScene::roomLight()
{
	if (cam_pointer->position.x > -266 && cam_pointer->position.x < -263 && cam_pointer->position.z > 312 && cam_pointer->position.z < 316 && Application::IsKeyPressed('E') && switchLightOn == true && time > delay)
	{
		time = 0;
		switchLightOn = false;
	}
	else if (cam_pointer->position.x > -266 && cam_pointer->position.x < -263 && cam_pointer->position.z > 312 && cam_pointer->position.z < 316 && Application::IsKeyPressed('E') && switchLightOn == false && time > delay)
	{
		time = 0;
		switchLightOn = true;
	}
	return switchLightOn;
}

/******************************************************************************/
/*!
\brief - show text only with the interacting boundary

\return - true if the player is inside it's interacting boundary

\return - false if the player is outside it's interacting boundary
*/
/******************************************************************************/

bool StationScene::switchText()
{
	if (cam_pointer->position.x > -266 && cam_pointer->position.x < -263 && cam_pointer->position.z > 312 && cam_pointer->position.z < 316 && switchLightOn == true)
	{
		return true;
	}
	else if (cam_pointer->position.x > -266 && cam_pointer->position.x < -263 && cam_pointer->position.z > 312 && cam_pointer->position.z < 316 && switchLightOn == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************/
/*!
\brief - updating the time

\param dt - frame time
*/
/******************************************************************************/

void StationScene::update(double dt)
{
	time += (float)(dt);
}

/******************************************************************************/
/*!
\brief - reset the entire room interaction
*/
/******************************************************************************/

void StationScene::reset()
{
	questActive = false;
	card1 = false;
	card2 = false;
	questComplete = false;
	doorOpened = false;
	switchLightOn = true;
}