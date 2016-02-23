/******************************************************************************/
/*!
\file       objectsForDisplay.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief - 
creates object of static game object
*/
/******************************************************************************/
#ifndef OBJECTSFORDISPLAY_H_
#define OBJECTSFORDISPLAY_H_

#include "GameObject.h"
#include "Vector3.h"

/******************************************************************************/
/*!
Class objectsForDisplay:
\brief - 
Inheirited from GameObject
It has it's own text reader file to input it's values, position, and boundary.
*/
/******************************************************************************/
class objectsForDisplay : public GameObject {
public:
    objectsForDisplay();
    ~objectsForDisplay();

    void init(const char *fileLocation);
    void init(Vector3 pos, float boundaryX, float boundaryZ, string name);
    bool boundaryCheck(const float& playerPosX, const float& playerPosZ);

    float getObjectposX();
    float getObjectposY();
    float getObjectposZ();
	Vector3 objectPos;

    float getBoundaryRadiusX();
    float getBoundaryRadiusZ();

protected:
    float boundaryRadiusX, boundaryRadiusZ;
};

#endif