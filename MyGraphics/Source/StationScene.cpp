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

short StationScene::getQuest()
{
	if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 262 && cam_pointer->position.z < 267 && questActive == false)
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
	else if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 262 && cam_pointer->position.z < 267 && questActive == true)
	{
		return 2;
	}
	else if (questActive == true)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

//bool StationScene::keyCard()
//{
//	bool checkQuest[2];
//	checkQuest[0] = true;
//	checkQuest[1] = true;
//
//	if (cam_pointer->position.x > -258 && cam_pointer->position.x < -255 && cam_pointer->position.z > 303 && cam_pointer->position.z < 306 && questActive == true)
//	{
//		if (Application::IsKeyPressed('E'))
//		{
//			checkQuest[0] = false;
//		}
//	}
//	else if (cam_pointer->position.x > -296 && cam_pointer->position.x < -294 && cam_pointer->position.z > 290 && cam_pointer->position.z < 293 && questActive == true)
//	{
//		if (Application::IsKeyPressed('E'))
//		{
//			checkQuest[1] = false;
//		}
//	}
//
//	return checkQuest;
//}

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
