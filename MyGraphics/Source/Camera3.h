#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"

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
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up, int mass = 0);
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
};

#endif