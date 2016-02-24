/******************************************************************************/
/*!
\file       Camera3.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
An improvised camera inheirited from Camera Class
*/
/******************************************************************************/
#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "objectsForDisplay.h"
#include <vector>

using std::vector;
/******************************************************************************/
/*!
Class Camera3:
\brief
First Person Camera included
Extremely Complex functions of the camera which incorporates mouse control
*/
/******************************************************************************/
class Camera3 : public Camera
{
public:
    enum CameraType
    {
        COMMON,
        FIRST_PERSON,
        TOTAL_CAMERAS_TYPE,
    } camType;

    Vector3 defaultPosition;
    Vector3 defaultTarget;
    Vector3 defaultUp;
    float defaultCameraYrotation, defaultCameraXrotation;

    Camera3();
    ~Camera3();
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Init(const char *fileLocation);
    virtual void Update(double dt);
    virtual void Reset();

    void InitObjects(const char *fileLocation);

    void setLocation(float x, float y, float z);
    void setRotation(float rotateX, float rotateY);

    float getCameraXcoord();
    float getCameraZcoord();
    float getCameraYcoord();
    float getCameraYrotation();
    float getCameraXrotation();

    //CrossHair Stuff
    float getCrossHairX();
    float getCrossHairY();
    float getCrossHairZ();
    void setRadiusBetcrosshair_cam(float radius);
    //CrossHair Stuff

    float cursorCoordX;
    float cursorCoordY;
    vector<objectsForDisplay> storage_of_objects;

private:
    void rotateCamera(double dt);
    float CameraXrotation;
    float CameraYrotation, maxCameraXrotation, minCameraXrotation;
    void cameraMovement(double dt);
    float cameraSpeed;

    //bounce check
    float boundaryX, boundaryZ;
    bool boundsCheckXaxis(const float& x, const float& posX);
    bool boundsCheckZaxis(const float& z, const float& posZ);
    //bounce check

    //Crosshair stuff
    Vector3 invisibleCrossHair;
    float crossHairRadius;
    //Crosshair stuff
};

#endif