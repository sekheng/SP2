/******************************************************************************/
/*!
\file       Camera.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Creating the functions of a Camera. But not fully improvised so it is important to create another camera class and inheirit from it
*/
/******************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/******************************************************************************/
/*!
Class Camera:
\brief
basic functions of the camera
*/
/******************************************************************************/
class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset();
	void Update(double dt);
protected:
	float moveX(float phi, float theta);
	float moveY(float phi, float theta);
	float moveZ(float phi, float theta);
};

#endif