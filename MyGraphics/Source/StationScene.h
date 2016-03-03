/******************************************************************************/
/*!
\file       StationScene.h
\author  SEETOO WEI JIE VICTOR
\par        email: 150452J@mymail.nyp.edu.sg
\brief -
Creating room interaction
*/
/******************************************************************************/
#ifndef STATIONSCENE_H
#define STATIONSCENE_H

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"
using std::vector;

/******************************************************************************/
/*!
\author  SEETOO WEI JIE VICTOR
\par        email: 150452J@mymail.nyp.edu.sg
\brief -
Inheirited from GameObject
It will have the collisiont check and position.
And it's own dialogues and interactions boundary
*/
/******************************************************************************/

class StationScene : public GameObject
{
public:
	StationScene();
	~StationScene();

	void Init(Camera3 &camera_address);
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

	Camera3 *cam_pointer;
	float time;
	bool questActive;
	bool questComplete;
	bool card1;
	bool card2;
	short count;
	bool doorOpened;
	bool switchLightOn;
	float delay;

protected:
};

#endif