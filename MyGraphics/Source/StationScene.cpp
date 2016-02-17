#include "StationScene.h"

StationScene::StationScene(Camera3& original)
{
	count = 0;
	questTaken = false;
	dubCamera = &original;
}

StationScene::~StationScene()
{
}

void StationScene::getQuest()
{
	for (auto it : dubCamera->storage_of_objects)
	{
		if (it.getName() == "door")
		{
			if (it.boundaryCheck(dubCamera->getCrossHairX(), dubCamera->getCrossHairZ()) && Application::IsKeyPressed('E'))
			{
				questTaken = true;
			}
			break;
		}
	}
}

bool StationScene::getItem()
{
	return false;
}

bool StationScene::openDoor(int& keyCount)
{
	if (keyCount == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}