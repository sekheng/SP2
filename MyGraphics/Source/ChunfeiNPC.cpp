#include "ChunfeiNPC.h"
#include "MyMath.h"
#include "Application.h"
#include <fstream>
#include <iostream>
#include <map>
#include <locale>
#include <algorithm>

ChunfeiNPC::ChunfeiNPC() : GameObject("ChunfeiNPC")
{

}

ChunfeiNPC::~ChunfeiNPC()
{

}

void ChunfeiNPC::Init(Camera3 &cameraDub, const Vector3 &robotpos)
{
	/*headrotate = false;
	headrotating = 0;*/
	camera = &cameraDub;
	robotpos_ =robotpos;
}

bool ChunfeiNPC::interaction()
{
	if ((robotpos_.x + 3) > camera->getCameraXcoord() &&
		(robotpos_.x - 3) < camera->getCameraXcoord() &&
		(robotpos_.z + 4) > camera->getCameraZcoord() &&
		(robotpos_.z - 4) < camera->getCameraZcoord())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//void ChunfeiNPC::headanimation(double dt)
//{
//	if (headrotate == false)
//	{
//		headrotating += 30 * (float)(dt);
//		if (headrotating > 30)
//		{
//			headrotate = true;
//		}
//	}
//	else if (headrotate == true)
//	{
//		headrotating -= 30 * (float)(dt);
//		if (headrotating < -30)
//		{
//			headrotate = false;
//		}
//	}
//}
//
//float ChunfeiNPC::getheadrotating()
//{
//	return headrotate;
//}