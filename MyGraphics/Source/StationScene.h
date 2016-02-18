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
	float Door_getposition_x();
	float Door_getposition_z();
	float Door_getposition_y();
	bool boundschecking(const float&bounds_x, const float &bounds_z);
	void update(double dt);
	string getDialogue();
	short getQuest();
	//bool keyCard();

private:
	Vector3 Door_pos;
	vector<string> Dialogues;
	Camera3 *cam_pointer;
	float bound_x, bound_z;
	double time;
	bool questActive;

protected:
};

#endif