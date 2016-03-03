/******************************************************************************/
/*!
\file       Light.h
\author  SEETOO WEI JIE VICTOR
\par        email: 150452J@mymail.nyp.edu.sg
\brief -
Creating light for the scene
*/
/******************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"

/******************************************************************************/
/*!
Light:
\brief
set the Light, position, color, light type, and light properties
*/
/******************************************************************************/

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light()
	{
		position.Set(0, 0, 0);
		color.Set(1, 1, 1);
		power = 0.1f;
		kC = kL = kQ = 1;
	}

	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
};

#endif