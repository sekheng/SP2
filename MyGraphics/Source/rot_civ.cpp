#include "rot_civ.h"
#include <sstream>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>
#include "Application.h"

using std::map;

/******************************************************************************/
/*!
\brief - 
Default Constructor with some of it's values being initialised
*/
/******************************************************************************/
rot_civ::rot_civ()
    : interatingRadius(4), time(0), order_of_text(0)
{
}

/******************************************************************************/
/*!
\brief - 
Destructor to delete the camera when it is destroyed
*/
/******************************************************************************/
rot_civ::~rot_civ()
{
    delete dub_camera;
}

/******************************************************************************/
/*!
\brief - Initialise dialogue and the scene's camera

\param fileLocation - To locate the text file for its dialogues

\param camera - a reference of the scene's camera
*/
/******************************************************************************/
void rot_civ::InitDialogues(const char* fileLocation, Camera3& camera) {
    dub_camera = &camera;

    //streaming rot_civ's dialogue
    std::ifstream fileStream2(fileLocation, std::ios::binary);
    if (!fileStream2.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream2.eof()) {
            string data = "";
            getline(fileStream2, data);
            data.erase(std::remove(data.begin(), data.end(), '\r'));
            dialogues.push_back(data);
        }
        fileStream2.close();
    }
    //streaming rot_civ's dialogue
}


/******************************************************************************/
/*!
\brief - update the interaction logic

\param dt - frame time
*/
/******************************************************************************/
void rot_civ::update(double dt) {
    time += dt;
    preventSpamming();
}

/******************************************************************************/
/*!
\brief - get one of it's dialogues which is decided by a size_t variable

\return - One of it's dialogues
*/
/******************************************************************************/
string rot_civ::returnDialogue() {
    return dialogues[order_of_text];
}

/******************************************************************************/
/*!
\brief - The interaction boundary of rot civ

\return false - if player is within its interacting boundary

\return true - if player is not within its interacting boundary
*/
/******************************************************************************/
bool rot_civ::interaction() {
    if ((objectPos.x + boundaryRadiusX + interatingRadius) > dub_camera->getCameraXcoord() &&
        (objectPos.x - boundaryRadiusX - interatingRadius) < dub_camera->getCameraXcoord() &&
        (objectPos.z + boundaryRadiusZ + interatingRadius) > dub_camera->getCameraZcoord() &&
        (objectPos.z - boundaryRadiusZ - interatingRadius) < dub_camera->getCameraZcoord())
    {
        return false;
    }
    order_of_text = 0;
    return true;
}

/******************************************************************************/
/*!
\brief - Prevention of the dialogue from running to fast if player is holding 'E'
*/
/******************************************************************************/
void rot_civ::preventSpamming() {
    if (Application::IsKeyPressed('E')) {
        if (time > 1) {
            order_of_text += 1;
            time = 0;
            if (order_of_text == dialogues.size()) {
                order_of_text = 0;
            }
        }
    }
}