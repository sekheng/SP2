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
#include <string>
#include <map>

using std::string;
using std::map;

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

    void setLocation(float x, float y, float z);

    float getCameraXcoord();
    float getCameraZcoord();
    float getCameraYcoord();
    float getCameraYrotation();
    float getCameraXrotation();

    float cursorCoordX;
    float cursorCoordY;
private:
    void rotateCamera(double dt);
    float CameraXrotation;
    float CameraYrotation, maxCameraXrotation, minCameraXrotation;
    void cameraMovement(double dt);
    float cameraSpeed;
    map<string, float> cameraCoordinates;

    //bounce check
    float boundaryX, boundaryZ;
    bool boundsCheckXaxis(const float& x, const float& posX);
    bool boundsCheckZaxis(const float& z, const float& posZ);
    //bounce check
};

#endif