/******************************************************************************/
/*!
\file       Light.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Struct to Define Light
*/
/******************************************************************************/
#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vertex.h"

/******************************************************************************/
/*!
struct Light:
\brief
Defines the Light, position, it's color, light type, and light properties
*/
/******************************************************************************/
struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
    enum LIGHT_TYPE
    {
        LIGHT_POINT = 0,
        LIGHT_DIRECTIONAL,
        LIGHT_SPOT,
        TOTAL_LIGHT,
    };
    LIGHT_TYPE type;
    Vector3 spotDirection;
    float cosCutoff, cosInner, exponent;

    Light()
	{
		position.Set(0, 0, 0);
		color.Set(1, 1, 1);
		power = 1.f;
		kC = kL = kQ = 1;
	}

};

#endif