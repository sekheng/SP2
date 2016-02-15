#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

#include "MyPhysics.h"
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera3::~Camera3()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
\param mass - mass of the camera which is default to 0
*/
/******************************************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up, int mass)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
    camType = COMMON;
    CameraXrotation = 0;
    CameraYrotation = 180;
    maxCameraXrotation = 80;
    minCameraXrotation = -80;
    defaultCameraYrotation = CameraYrotation;
    defaultCameraXrotation = CameraXrotation;
    float cameraSpeed = 1;
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera3::Update(double dt)
{
    static const float CAMERA_SPEED = 50.f;
    switch (camType)
    {
    case COMMON:
        if (Application::IsKeyPressed('Q'))
        {
        }
        if (Application::IsKeyPressed('E'))
        {
        }
        if (Application::IsKeyPressed('W'))
        {

        }
        if (Application::IsKeyPressed(VK_LEFT))
        {
            float yaw = -(float)(CAMERA_SPEED * dt);
            Mtx44 rotation;
            rotation.SetToRotation(yaw, 0, 1, 0);
            position = rotation * position;
            up = rotation * up;
        }
        if (Application::IsKeyPressed(VK_RIGHT))
        {
            float yaw = (float)(CAMERA_SPEED * dt);
            Mtx44 rotation;
            rotation.SetToRotation(yaw, 0, 1, 0);
            position = rotation * position;
            up = rotation * up;
        }
        if (Application::IsKeyPressed(VK_UP))
        {
            float pitch = (float)(-CAMERA_SPEED * dt);
            Vector3 view = (target - position).Normalized();
            Vector3 right = view.Cross(up);
            right.y = 0;
            right.Normalize();
            up = right.Cross(view).Normalized();
            Mtx44 rotation;
            rotation.SetToRotation(pitch, right.x, right.y, right.z);
            position = rotation * position;
        }
        if (Application::IsKeyPressed(VK_DOWN))
        {
            float pitch = (float)(CAMERA_SPEED * dt);
            Vector3 view = (target - position).Normalized();
            Vector3 right = view.Cross(up);
            right.y = 0;
            right.Normalize();
            up = right.Cross(view).Normalized();
            Mtx44 rotation;
            rotation.SetToRotation(pitch, right.x, right.y, right.z);
            position = rotation * position;
        }
        if (Application::IsKeyPressed('N'))
        {
            Vector3 direction = target - position;
            if (direction.Length() > 5)
            {
                Vector3 view = (target - position).Normalized();
                position += view * (float)(100.f * dt);
            }
        }
        if (Application::IsKeyPressed('M'))
        {
            Vector3 view = (target - position).Normalized();
            position -= view * (float)(100.f * dt);
        }
        if (Application::IsKeyPressed('R'))
        {
            Reset();
        }
        break;
    case FIRST_PERSON:
        if (Application::IsKeyPressed('R'))
        {
            Reset();
        }
        cameraMovement(dt);
        if (Application::IsKeyPressed(VK_SPACE))
        {
            position.y += 10 * (float)(dt);
        }
        if (Application::IsKeyPressed(VK_LCONTROL))
        {
            position.y -= 10 * (float)(dt);
        }
        rotateCamera(3 * dt);
        break;
    }
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera3::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
    CameraXrotation = defaultCameraXrotation;
    CameraYrotation = defaultCameraYrotation;
}

/******************************************************************************/
/*!
\brief
rotation of the camera based on the mouse movement

\param dt - frame time
*/
/******************************************************************************/
void Camera3::rotateCamera(double dt)
{
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    SetCursorPos(static_cast<int>(cursorCoordX), static_cast<int>(cursorCoordY));
    CameraYrotation -= ((mousePosition.x - cursorCoordX) * (float)(dt));
    CameraXrotation += ((mousePosition.y - cursorCoordY) * (float)(dt));
    CameraXrotation = Math::Clamp(CameraXrotation, minCameraXrotation, maxCameraXrotation);

   target = Vector3(sin(Math::DegreeToRadian(CameraYrotation)) * cos(Math::DegreeToRadian(CameraXrotation)) + position.x, -sin(Math::DegreeToRadian(CameraXrotation)) + position.y, cos(Math::DegreeToRadian(CameraYrotation)) * cos(Math::DegreeToRadian(CameraXrotation)) + position.z );
   Vector3 view = (target - position).Normalized();
   Vector3 right = view.Cross(defaultUp);
    up = right.Cross(view);
}

/******************************************************************************/
/*!
\brief
An improved camera movement based on first person

\param dt - frame time
*/
/******************************************************************************/
void Camera3::cameraMovement(double dt)
{
    float walkingX = 0;
    float walkingZ = 0;
    if (Application::IsKeyPressed('W'))
     //got a bug on the turning and walking
    {
        walkingX += (float)(sin(Math::DegreeToRadian(CameraYrotation)) * dt);
        walkingZ += (float)(cos(Math::DegreeToRadian(CameraYrotation)) * dt);
    }
    if (Application::IsKeyPressed('A'))
    {
        walkingX += (float)(sin(Math::DegreeToRadian(CameraYrotation + 90)) * dt);
        walkingZ += (float)(cos(Math::DegreeToRadian(CameraYrotation + 90)) * dt);
    }
    if (Application::IsKeyPressed('S'))
    {
        walkingX += (float)(sin(Math::DegreeToRadian(CameraYrotation + 180)) * dt);
        walkingZ += (float)(cos(Math::DegreeToRadian(CameraYrotation + 180)) * dt);
    }
    if (Application::IsKeyPressed('D'))
    {
        walkingX += (float)(sin(Math::DegreeToRadian(CameraYrotation + 270)) * dt);
        walkingZ += (float)(cos(Math::DegreeToRadian(CameraYrotation + 270)) * dt);
    }
    if (Application::IsKeyPressed(VK_LSHIFT))
    {
        walkingX *= 50;
        walkingZ *= 50;
    }
    position.x += walkingX;
    position.z += walkingZ;
}

/******************************************************************************/
/*!
\brief
getting camera's position of x coordinate

\return - x coordinate of camera's position
*/
/******************************************************************************/
float Camera3::getCameraXcoord()
{
    return position.x;
}

/******************************************************************************/
/*!
\brief
getting camera's position of z coordinate

\return - z coordinate of camera's position
*/
/******************************************************************************/
float Camera3::getCameraZcoord()
{
    return position.z;
}


/******************************************************************************/
/*!
\brief
getting camera's position of y coordinate

\return - y coordinate of camera's position
*/
/******************************************************************************/
float Camera3::getCameraYcoord()
{
    return position.y;
}


/******************************************************************************/
/*!
\brief
getting camera's rotation based on the x axis

\return - camera's rotational angle based on the x axis
*/
/******************************************************************************/
float Camera3::getCameraXrotation() {
    return CameraXrotation;
}

/******************************************************************************/
/*!
\brief
getting camera's rotation based on the y axis

\return - camera's rotational angle based on the y axis
*/
/******************************************************************************/
float Camera3::getCameraYrotation() {
    return CameraYrotation;
}

/******************************************************************************/
/*!
\brief
Setting the coordinates of the camera's position

\param x - coordinate x of the camera's position
\param y - coordinate y of the camera's position
\param z - coordinate z of the camera's position
*/
/******************************************************************************/
void Camera3::setLocation(float x, float y, float z) {
    position.x = x;
    defaultPosition.x = x;
    position.y = y;
    defaultPosition.y = y;
    position.z = z;
    defaultPosition.z = z;
}