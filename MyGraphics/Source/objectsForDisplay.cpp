#include "objectsForDisplay.h"
#include <fstream>
#include <iostream>
#include <map>
#include <locale>

using std::map;

objectsForDisplay::objectsForDisplay()
    : GameObject("nothing")
{
}

objectsForDisplay::~objectsForDisplay()
{
}

void objectsForDisplay::init(const char *fileLocation) {
    map<string, string> object_stuff;
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
            object_stuff.insert(std::pair<string, string>(taking_the_stuff, values));
        }
        fileStream.close();
    }
    map<string, string>::iterator it = object_stuff.find("name");
    Name_ = it->second;

    it = object_stuff.find("objectx");
    objectPos.x = static_cast<float>(stoi(it->second));

    it = object_stuff.find("objecty");
    objectPos.y = static_cast<float>(stoi(it->second));

    it = object_stuff.find("objectz");
    objectPos.z = static_cast<float>(stoi(it->second));

    it = object_stuff.find("boundaryradius");
    boundaryRadius = static_cast<float>(stoi(it->second));
}

bool objectsForDisplay::boundaryCheck(const Vector3& playerPos) {

    return true;
}

float objectsForDisplay::getObjectposX() {
    return objectPos.x;
}

float objectsForDisplay::getObjectposY() {
    return objectPos.y;
}

float objectsForDisplay::getObjectposZ() {
    return objectPos.z;
}