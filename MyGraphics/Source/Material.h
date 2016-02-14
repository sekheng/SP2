/******************************************************************************/
/*!
\file       Material.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Structs to define Material
*/
/******************************************************************************/
#ifndef MATERIAL_H_
#define MATERIAL_H_

/******************************************************************************/
/*!
struct Component:
\brief
Defines material's colour
*/
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 1.0f){ Set(r, g, b); }
	void Set(float r, float g, float b){ this->r = r; this->g = g; this->b = b; }
};

/******************************************************************************/
/*!
struct Material:
\brief
Defines the material and it's properties
*/
/******************************************************************************/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material()
	{

	}
};
#endif