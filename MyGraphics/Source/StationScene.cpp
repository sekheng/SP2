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

bool StationScene::interaction()
{
	if (cam_pointer->position.x > -293 && cam_pointer->position.x < -263 && cam_pointer->position.z > 262 && cam_pointer->position.z < 270)
	{
		return true;
	}
	else
	{
		return false;
	}
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
