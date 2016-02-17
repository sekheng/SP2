#include "rot_civ.h"
#include <sstream>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <locale>

using std::map;

rot_civ::rot_civ() 
    : GameObject("ROT CIV")
{
}

rot_civ::~rot_civ()
{
}

void rot_civ::Init(string& fileLocation, Camera3& camera) {
    dub_camera = &camera;
    std::stringstream ss;
    ss << fileLocation << "rot_civ_stuff.txt";
    std::stringstream dia;
    dia << fileLocation << "rot_civ_dialogues.txt";

    //streaming the rot_civ's stuff
    map<string, string> object_stuff;
    std::ifstream fileStream(ss.str(), std::ios::binary);
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
            values.erase(std::remove(values.begin(), values.end(), '\r'));
            std::locale loc;
            for (size_t num = 0; num < taking_the_stuff.size(); ++num) {
                taking_the_stuff[num] = tolower(taking_the_stuff[num], loc);
            }
            object_stuff.insert(std::pair<string, string>(taking_the_stuff, values));
        }
        fileStream.close();
        map<string,string>::iterator it = object_stuff.find("objectx");
        pos.x = static_cast<float>(strtof(it->second.c_str(), NULL));

        it = object_stuff.find("objecty");
        pos.y = static_cast<float>(strtof(it->second.c_str(), NULL));

        it = object_stuff.find("objectz");
        pos.z = static_cast<float>(strtof(it->second.c_str(), NULL));

        it = object_stuff.find("boundaryradiusx");
        boundaryX = static_cast<float>(strtof(it->second.c_str(), NULL));
        it = object_stuff.find("boundaryradiusz");
        boundaryZ = static_cast<float>(strtof(it->second.c_str(), NULL));
    }
    //streaming the rot_civ's stuff

    //streaming rot_civ's dialogue
    std::ifstream fileStream2(dia.str(), std::ios::binary);
    if (!fileStream2.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream.eof()) {
            string data = "";
            getline(fileStream, data);
            data.erase(std::remove(data.begin(), data.end(), '\r'));
            dialogues.push_back(data);
        }
        fileStream.close();
    }
    //streaming rot_civ's dialogue
}

bool rot_civ::boundaryCheck(float posX, float posZ) {
    if ((pos.x + boundaryX) > posX &&
        (pos.x - boundaryX) < posX &&
        (pos.z + boundaryZ) > posZ &&
        (pos.z - boundaryZ) < posZ)
    {
        return false;
    }
    return true;
}

void rot_civ::update(double dt) {

}