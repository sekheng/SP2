#include "Camera.h"
#include "Application.h"
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	if (Application::IsKeyPressed('W'))
	{
		position.y += moveY(10.f * static_cast<float>(dt), 10.f * static_cast<float>(dt));
		position.x += moveX(10.f * static_cast<float>(dt), 10.f * static_cast<float>(dt));
		position.z += moveZ(10.f * static_cast<float>(dt), 10.f * static_cast<float>(dt));
	}
	else if (Application::IsKeyPressed('S'))
	{
		position.y -= moveY(10.f * static_cast<float>(dt), 10.f * static_cast<float>(dt));
		position.x -= moveX(10.f * static_cast<float>(dt), 10.f * static_cast<float>(dt));
		position.z -= moveZ(10.f * static_cast<float>(dt), 10.f * static_cast<float>(dt));
	}
	else if (Application::IsKeyPressed('A'))
	{
		position.z += 10.f * static_cast<float>(dt);
	}
	else if (Application::IsKeyPressed('D'))
	{
		position.z -= 10.f * static_cast<float>(dt);
	};
}

float Camera::moveX(float phi, float theta)
{
	return (cos(Math::DegreeToRadian(phi))) * (cos(Math::DegreeToRadian(theta)));
}

float Camera::moveY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}

float Camera::moveZ(float phi, float theta)
{
	return (cos(Math::DegreeToRadian(phi))) * (sin(Math::DegreeToRadian(theta)));
}
