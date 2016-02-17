#ifndef STATIONSCENE_H
#define STATIONSCENE_H
#include "Camera3.h"
#include "objectsForDisplay.h"
#include "Application.h"

class StationScene
{
public:
	StationScene(Camera3& original);
	~StationScene();
	void getQuest();
	bool getItem();
	bool openDoor();


private:
	int count;
	bool questTaken;
	bool card1Taken;
	bool card2Taken;
	Camera3 *dubCamera;
};


#endif