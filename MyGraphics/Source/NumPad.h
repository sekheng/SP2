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

	void Init();
	void NumPadUpdate();

};

#endif