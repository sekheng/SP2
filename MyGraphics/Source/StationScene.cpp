#include "StationScene.h"
#include "MyMath.h"
#include "Application.h"

StationScene::StationScene() : GameObject("Door")
{

}
StationScene::~StationScene()
{

}

void StationScene::Init(string name, Vector3 pos, Camera3 &camera_address, float boundaryX, float boundaryZ)
{
	Name_ = name;
	Door_pos = pos;
	Dialogues = { "FML", "HI", "Vote for Najib", "Dai lo" };
	cam_pointer = &camera_address;
	bound_x = boundaryX;
	bound_z = boundaryZ;
	time = 0;
	questActive = false;
	card1 = false;
	card2 = false;
	questComplete = false;
	doorOpened = false;
}

float StationScene::Door_getposition_x()
{
	return Door_pos.x;
}
float StationScene::Door_getposition_z()
{
	return Door_pos.z;
}
float StationScene::Door_getposition_y()
{
	return Door_pos.y;
}

string StationScene::getDialogue()
{
	/*if (interaction() == true && time < 3);
	{
	return Dialogues[Math::RandIntMinMax(0, Dialogues.size() - 1)];
	}*/
	return 0;
}


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

short StationScene::getQuestStage()
{
	if (questComplete == false)
	{
		if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 268 && cam_pointer->position.z < 270 && questActive == false)
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
		else if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 268 && cam_pointer->position.z < 270 && questActive == true)
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

short StationScene::openSasame()
{
	if (card1 == true && card2 == true)
	{
		questComplete = true;
		if(cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 268 && cam_pointer->position.z < 270 && doorOpened == false)
		{
			if (Application::IsKeyPressed('E'))
			{ 
				doorOpened = true;
			}
			return 1;
		}
		else if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 268 && cam_pointer->position.z < 270 && doorOpened == true)
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


bool StationScene::boundschecking(const float&bounds_x, const float &bounds_z)
{
	if ((Door_getposition_x() + bound_x) > bounds_x &&
		(Door_getposition_x() - bound_x) < bounds_x &&
		(Door_getposition_z() + bound_z) > bounds_z &&
		(Door_getposition_z() - bound_z) < bounds_z)
	{
		return true;
	}
	return false;
}

void StationScene::update(double dt)
{
	time += dt;
}
