#ifndef NUMPAD_H
#define NUMPAD_H

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"

using std::vector;

class NumPad : public GameObject
{
public:
	NumPad();
	~NumPad();

	void Init(Camera3 &cameraDub, const Vector3 &origPos);
	void Update(double dt);
	void NumpadProgram();
	bool NumpadVerify();
	bool interactiontext();
	bool interaction();
	bool displayerror();


	bool text;
	bool screentext;
	bool firstroll;
	bool secondroll;
	bool thirdroll;
	bool fourthroll;
	bool check;
	bool rendererror;
	bool open;
	bool close;
	float wheelturning;
	float stickpushing;
	float dooropening;
	int firstrotate;
	int secondrotate;
	int thirdrotate;
	int fourthrotate;
	float time_delay;
	float changearrow;
	float arrow;

	int digit1;
	int digit2;
	int digit3;
	int digit4;
	double time;

	bool wheelturn;
	bool stickpush;
	bool dooropen;

	int getfirstrotate();
	int getsecondrotate();
	int getthirdrotate();
	int getfourthrotate();
	float getarrowposition();
	int getdigit1();
	int getdigit2();
	int getdigit3();
	int getdigit4();
private:
	
	
	

	Camera3 *camera;
	Vector3 pos;
};

#endif