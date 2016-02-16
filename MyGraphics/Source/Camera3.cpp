#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

#include "MyPhysics.h"
#include "MyMath.h"
#include <fstream>
#include <locale>
#include <map>
#include <sstream>

using std::map;
/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
    : boundaryX(0), boundaryZ(0)
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
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
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
Initialize camera

\param fileLocation - path name to the file
*/
/******************************************************************************/
void Camera3::Init(const char *fileLocation)
{
    map<string, float> cameraCoordinates;
    std::ifstream fileStream(fileLocation, std::ios::binary);
    if (!fileStream.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream.eof()) {
            string data = "";
            getline(fileStream, data);
            char *nextStuff;
            char *stringtoken = strtok_s(const_cast<char*>(data.c_str()), ",", &nextStuff);
            string taking_the_stuff = "";
            string values = "";
            taking_the_stuff.append(stringtoken);
            values.append(nextStuff);
            std::locale loc;
            for (size_t num = 0; num < taking_the_stuff.size(); ++num) {
                taking_the_stuff[num] = tolower(taking_the_stuff[num], loc);
            }
            cameraCoordinates.insert(std::pair<string, float>(taking_the_stuff, static_cast<float>(stoi(values))));
        }
        fileStream.close();
    }
    map<string, float>::iterator it = cameraCoordinates.find("positionx");
    this->position.x = defaultPosition.x = it->second;
    it = cameraCoordinates.find("positiony");
    this->position.y = defaultPosition.y = it->second;
    it = cameraCoordinates.find("positionz");
    this->position.z = defaultPosition.z = it->second;

    it = cameraCoordinates.find("targetx");
    this->target.x = defaultTarget.x = it->second;
    it = cameraCoordinates.find("targety");
    this->target.y = defaultTarget.y = it->second;
    it = cameraCoordinates.find("targetz");
    this->target.z = defaultTarget.z = it->second;

    Vector3 decoyUp;
    it = cameraCoordinates.find("upx");
    decoyUp.x = it->second;
    it = cameraCoordinates.find("upy");
    decoyUp.y = it->second;
    it = cameraCoordinates.find("upz");
    decoyUp.z = it->second;

    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(decoyUp);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();

    camType = FIRST_PERSON;

    it = cameraCoordinates.find("camerarotationx");
    CameraXrotation = defaultCameraXrotation = it->second;
    it = cameraCoordinates.find("camerarotationy");
    CameraYrotation = defaultCameraYrotation = it->second;

    maxCameraXrotation = 80;
    minCameraXrotation = -80;

    it = cameraCoordinates.find("cameraspeed");
    float cameraSpeed = it->second;

    it = cameraCoordinates.find("boundscheckx");
    boundaryX = it->second;
    
    it = cameraCoordinates.find("boundscheckz");
    boundaryZ = it->second;

    it = cameraCoordinates.find("numberofobjects");
    num_of_objects = static_cast<size_t>(it->second);
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
    if (boundaryX != 0 && boundsCheckXaxis(boundaryX, position.x + walkingX))
        position.x += walkingX;
    if (boundaryZ != 0 && boundsCheckZaxis(boundaryZ, position.z + walkingZ))
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

bool Camera3::boundsCheckXaxis(const float& x, const float& posX) {
    if (posX < x && posX > -x)
    {
        return true;
    }
    return false;
}

bool Camera3::boundsCheckZaxis(const float& z, const float& posZ) {
    if (posZ < z && posZ > -z)
    {
        return true;
    }
    return false;
}

void Camera3::InitObjects(const char *fileLocation) {
    if (num_of_objects > 0) {
        for (size_t num = 1; num <= num_of_objects; ++num) {
            std::stringstream ss;
            ss << fileLocation << "object" << num << ".txt";
            string filename = ss.str();
            objectsForDisplay object;
            object.init(filename.c_str());
            storage_of_objects.push_back(object);
        }
    }
}