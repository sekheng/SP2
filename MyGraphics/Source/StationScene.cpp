#include "StationScene.h"

StationScene::StationScene(Camera3& original)
{
	count = 0;
	questTaken = false;
	card1Taken = false;
	card2Taken = false;
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
	if (questTaken == true)
	{
		for (auto it : dubCamera->storage_of_objects)
		{
			if (it.getName() == "keycard1")
			{
				if (it.boundaryCheck(dubCamera->getCrossHairX(), dubCamera->getCrossHairZ()) && Application::IsKeyPressed('E'))
				{
					card1Taken = true;
					count++;
				}
				break;
			}
			else if (it.getName() == "keycard2")
			{
				if (it.boundaryCheck(dubCamera->getCrossHairX(), dubCamera->getCrossHairZ()) && Application::IsKeyPressed('E'))
				{
					card2Taken = true;
					count++;
				}
				break;
			}
		}
	}
	if (card1Taken == true && card2Taken == true)
	{
		return true;
	}
	return false;
}

bool StationScene::openDoor()
{
	if (count == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
