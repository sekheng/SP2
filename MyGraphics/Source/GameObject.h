#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
/******************************************************************************/
/*!
\file       GameObject.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief
The base class of objects inside the game
To create and count how many GameObjects are there in the game
*/
/******************************************************************************/
#include <string>
#include "DetectMemoryLeak.h"

using std::string;

/******************************************************************************/
/*!
                Class GameObject:
\brief      Defines GameObject, get the name of the GameObject 
                and count how many gameobjects there are
*/
/******************************************************************************/
class GameObject
{
private:
	const string kName;
	static int count_;

protected:
	explicit GameObject(const string& str);

public:
	virtual ~GameObject();

	string getName(void);
	static int getCount();
};

#endif