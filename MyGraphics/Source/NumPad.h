/******************************************************************************/
/*!
\file    NumPad.h
\author  Lee Chun Fei
\par        email: 150678G@mymail.nyp.edu.sg
\brief -
Numpad's interaction
*/
/******************************************************************************/
#ifndef NUMPAD_H
#define NUMPAD_H

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"

using std::vector;

/****************************************************************************/
/*!
Class NumPad:
\brief 
inheirited from GameObject
*/
/****************************************************************************/

class NumPad : public GameObject
{
public:
	NumPad();
	~NumPad();

	void Init(Camera3 &cameraDub, const Vector3 &origPos);
	void Update(double dt);
	void NumpadProgram(double dt);
	void Reset();

	bool NumpadVerify();
	bool interactiontext();
	bool interaction();
	bool displayerror();
	bool NumpadRenderOnScreen();

	float getfirstrotate();
	float getsecondrotate();
	float getthirdrotate();
	float getfourthrotate();
	float getarrowposition();

	int getdigit1();
	int getdigit2();
	int getdigit3();
	int getdigit4();

private:

	bool check;
	bool open;
	bool close;
	bool render;

	float firstrotate;
	float secondrotate;
	float thirdrotate;
	float fourthrotate;
	float time_delay;
	float changearrow;
	float arrow;

	int digit1;
	int digit2;
	int digit3;
	int digit4;
	int hahaha;

	double time;
	
	Camera3 *camera;
	Vector3 pos;
};

#endif