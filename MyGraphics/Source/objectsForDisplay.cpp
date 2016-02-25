#include "objectsForDisplay.h"
#include <fstream>
#include <iostream>
#include <map>
#include <locale>
#include <algorithm>

using std::map;

/******************************************************************************/
/*!
\brief - 
Default Constructor
*/
/******************************************************************************/
objectsForDisplay::objectsForDisplay()
    : GameObject("nothing")
{
}

/******************************************************************************/
/*!
\brief - 
Destructor
*/
/******************************************************************************/
objectsForDisplay::~objectsForDisplay()
{
}

/******************************************************************************/
/*!
\brief - initialised it's values through text file reader

\param fileLocation - the path name to the text file
*/
/******************************************************************************/
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
            if (data == "" || data == "\r") {
                continue;
            }
            //the next sentence after the delimiter. The delimiter in this case is a comma.
            char *nextStuff;
            //the next sentence after the delimiter
            //stringtoken gets the whole statement
            char *stringtoken = strtok_s(const_cast<char*>(data.c_str()), ",", &nextStuff);
            //stringtoken gets the whole statement
            //I wish to use string instead of C-style string to prevent rubbish inside the string
            string taking_the_stuff = "";
            string values = "";
            //taking_the_stuff gets the first statement just before the delimiter
            taking_the_stuff.append(stringtoken);
            //taking_the_stuff gets the first statement just before the delimiter
            //values get the nextStuff's string
            values.append(nextStuff);
            //values get the nextStuff's string
            //erasing the '\r' inside values as the string taken from the text file always end with '\r'
            values.erase(std::remove(values.begin(), values.end(), '\r'));
            //erasing the '\r' inside values as the string taken from the text file always end with '\r'
            //just putting locale for fun. Don't do it.
            std::locale loc;
            for (size_t num = 0; num < taking_the_stuff.size(); ++num) {
                taking_the_stuff[num] = tolower(taking_the_stuff[num], loc);
            }
            //just putting locale for fun. Don't do it.
            object_stuff.insert(std::pair<string, string>(taking_the_stuff, values));
        }
        fileStream.close();
    }
    //the rest of the statements are EZ stuff. If you find it difficult, read up on map.
    map<string, string>::iterator it = object_stuff.find("name");
    Name_ = it->second;

    it = object_stuff.find("objectx");
    objectPos.x = strtof(it->second.c_str(), NULL);

    it = object_stuff.find("objecty");
    objectPos.y = strtof(it->second.c_str(), NULL);

    it = object_stuff.find("objectz");
    objectPos.z = strtof(it->second.c_str(), NULL);

    it = object_stuff.find("boundaryradiusx");
    boundaryRadiusX = strtof(it->second.c_str(), NULL);
    it = object_stuff.find("boundaryradiusz");
    boundaryRadiusZ = strtof(it->second.c_str(), NULL);

    originalPos = objectPos;
}

/******************************************************************************/
/*!
\brief - the boundary check with the camera's position

\param playerPosX - X coordinate of the camera

\param playerPosZ - Z coordinate of the camera

\return true - if the player is not within it's box boundary

\return false - if the player is within it's box boundary
*/
/******************************************************************************/
bool objectsForDisplay::boundaryCheck(const float& playerPosX, const float& playerPosZ) {
    if ((objectPos.x + boundaryRadiusX) > playerPosX &&
        (objectPos.x - boundaryRadiusX) < playerPosX &&
        (objectPos.z + boundaryRadiusZ) > playerPosZ &&
        (objectPos.z - boundaryRadiusZ) < playerPosZ)
    {
        return false;
    }
    return true;
}

/******************************************************************************/
/*!
\brief - get this object's X coordinate

\return - X coordinate of the object
*/
/******************************************************************************/
float objectsForDisplay::getObjectposX() {
    return objectPos.x;
}

/******************************************************************************/
/*!
\brief - get this object's Y coordinate

\return - Y coordinate of the object
*/
/******************************************************************************/
float objectsForDisplay::getObjectposY() {
    return objectPos.y;
}

/******************************************************************************/
/*!
\brief - get this object's Z coordinate

\return - Z coordinate of the object
*/
/******************************************************************************/
float objectsForDisplay::getObjectposZ() {
    return objectPos.z;
}

/******************************************************************************/
/*!
\brief - initialised it's variables by passing in parameter

\param pos - Coordinates of the object

\param boundaryX - boundary of the object based on the X Axis

\param boundaryZ - boundary of the object based on the Z Axis

\param name - Name of the object
*/
/******************************************************************************/
void objectsForDisplay::init(Vector3 pos, float boundaryX, float boundaryZ, string name) {
    Name_ = name;
    objectPos = pos;
    boundaryRadiusX = boundaryX;
    boundaryRadiusZ = boundaryZ;
}

/******************************************************************************/
/*!
\brief - get this object's X boundary range

\return - X boundary range of the object
*/
/******************************************************************************/
float objectsForDisplay::getBoundaryRadiusX() {
    return boundaryRadiusX;
}

/******************************************************************************/
/*!
\brief - get this object's Z boundary range

\return - Z boundary range of the object
*/
/******************************************************************************/
float objectsForDisplay::getBoundaryRadiusZ() {
    return boundaryRadiusZ;
}
