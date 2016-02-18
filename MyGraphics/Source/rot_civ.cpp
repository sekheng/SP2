#include "rot_civ.h"
#include <sstream>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>

using std::map;

rot_civ::rot_civ() 
    : interatingRadius(4), time(0)
{
}

rot_civ::~rot_civ()
{
}

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


void rot_civ::update(double dt) {
    time += dt;
}

string rot_civ::returnDialogue(size_t order) {
    return dialogues[order];
}

bool rot_civ::interaction() {
    if ((objectPos.x + boundaryRadiusX + interatingRadius) > dub_camera->getCameraXcoord() &&
        (objectPos.x - boundaryRadiusX - interatingRadius) < dub_camera->getCameraXcoord() &&
        (objectPos.z + boundaryRadiusZ + interatingRadius) > dub_camera->getCameraZcoord() &&
        (objectPos.z - boundaryRadiusZ - interatingRadius) < dub_camera->getCameraZcoord())
    {
        return false;
    }
    return true;
}