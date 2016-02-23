#ifndef CHUNFEINPC_H
#define CHUNFEINPC_H

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"

using std::vector;

class ChunfeiNPC : public GameObject
{
public:
	ChunfeiNPC();
	~ChunfeiNPC();

	void Init(Camera3 &cameraDub, const Vector3 &origPos);
	bool interaction();
	/*void headanimation(double dt);

	float getheadrotating();*/

private:

	/*bool headrotate;
	float headrotating;*/

	Camera3 *camera;
	Vector3 robotpos_;
};
#endif