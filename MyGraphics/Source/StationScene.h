#ifndef STATIONSCENE_H
#define STATIONSCENE_H

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"

using std::vector;

class StationScene : public GameObject
{
public:
	StationScene();
	~StationScene();

	void Init(string name, Vector3 pos, Camera3 &camera_address, float boundaryX, float boundaryZ);
	void update(double dt);
	short getQuestStage();
	short getCard1();
	short getCard2();
	bool getCardText();
	short openSasame();
	bool roomLight();
	bool switchText();
	void reset();

private:
	Vector3 Door_pos;
	vector<string> Dialogues;
	Camera3 *cam_pointer;
	float bound_x, bound_z;
	float time;
	bool questActive;
	bool questComplete;
	bool card1;
	bool card2;
	short count;
	bool doorOpened;
	bool switchLightOn;
	bool switchLightOff;
	float delay;

protected:
};

#endif