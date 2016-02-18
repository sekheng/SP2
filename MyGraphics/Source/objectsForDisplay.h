#ifndef OBJECTSFORDISPLAY_H_
#define OBJECTSFORDISPLAY_H_

#include "GameObject.h"
#include "Vector3.h"

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

protected:
    Vector3 objectPos;
    float boundaryRadiusX, boundaryRadiusZ;
};

#endif