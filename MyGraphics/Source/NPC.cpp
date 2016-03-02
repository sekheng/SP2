#include "NPC.h"
#include "MyMath.h"
#include "Application.h"
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
NPC::NPC() : GameObject("NPC")
{
    
}
/******************************************************************************/
/*!
\brief -
Destructor
*/
/******************************************************************************/
NPC::~NPC()
{

}
/******************************************************************************/
/*!
\brief - initialised it's values through text file reader as well as some 
other variables initialised through function parameters needed for NPC class to work

\param name - name of object

\param NumberofDialogue - number of lines of dialogue the NPC has

\param pos - Coodinates of object

\param boundaryX - X axis bounds for object

\param boundaryZ - Z axis bounds for object

\param camera_address - camera object

\param fileLocation - the path name to the text file
*/
/******************************************************************************/
void NPC::Init(string name, short NumberofDialogue ,Vector3 pos, float boundaryX, float boundaryZ, Camera3 &camera_address, const char *fileLocation)
{
    //initialization of varivables
    Name_ = name;
    NPC_pos = pos;
    cam_pointer = &camera_address;
    bound_x = boundaryX;
    bound_z = boundaryZ;
    dialogue_switch = 0;
    dialogue_reset = false;
    time = 0;
    has_interacted = false;
    dialogue_finish = false;
    stage = 0;
    quest_complete_delay = false;
    quest_complete_stage = 0;

    line_of_dialogue = NumberofDialogue;
    //read dialogue from text file
    std::ifstream fileStream(fileLocation, std::ios::binary);
    if (!fileStream.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream.eof()) {
            //string tp store the dialogues for npc object
            string data = "";
            getline(fileStream, data);
            data.erase(std::remove(data.begin(), data.end(), '\r'));
            //push back all the data into vector of string
            Dialogues.push_back(data);
        }
        fileStream.close();
    }
    text_delay = 0.5f; // set the delay for text

}
/******************************************************************************/
/*!
\brief - get this object's X coordinate

\return - X coordinate of the object
*/
/******************************************************************************/
float NPC::NPC_getposition_x()
{
    return NPC_pos.x;
}
/******************************************************************************/
/*!
\brief - get this object's y coordinate

\return - y coordinate of the object
*/
/******************************************************************************/
float NPC::NPC_getposition_z()
{
    return NPC_pos.z;
}
/******************************************************************************/
/*!
\brief - get this object's y coordinate

\return - y coordinate of the object
*/
/******************************************************************************/
float NPC::NPC_getposition_y()
{
    return NPC_pos.y;
}

/******************************************************************************/
/*!
\brief - get this object's dialogue



\return - dialogue for object in the form of a string
*/
/******************************************************************************/
string NPC::getDialogue(bool reset)
{
    dialogue_reset = reset;
    
    if (dialogue_reset == true && has_interacted == false)
    {
        dialogue_switch = 0;
        return Dialogues[dialogue_switch];
    }
    else if (dialogue_reset == false && has_interacted == false) 
    {
        has_interacted = true;
        return Dialogues[dialogue_switch];
    }
    else
    {
        if (time > text_delay) 
		{
            time = 0;
            if (dialogue_reset == false) 
			{
                dialogue_switch += 1;
            }
            if (dialogue_switch == (line_of_dialogue-1))
            {
                dialogue_finish = true;
            }
            if (dialogue_switch == (line_of_dialogue))
            {
                dialogue_switch = (line_of_dialogue - 1);
            }
        }
        return Dialogues[dialogue_switch];
    }

}

bool NPC::interaction()
{
    
        if (boundschecking(cam_pointer->getCameraXcoord(), cam_pointer->getCameraZcoord()) == true)
        {
                return true;
        }
        else { 
            has_interacted = false;
            return false; 
        }
        return false;
}

bool NPC::boundschecking(const float&bounds_x, const float &bounds_z)
{
    if ((NPC_getposition_x() + bound_x) > bounds_x &&
        (NPC_getposition_x() - bound_x) < bounds_x &&
        (NPC_getposition_z() + bound_z) > bounds_z &&
        (NPC_getposition_z() - bound_z) < bounds_z)
    {
        return true;
    }
    return false;
}



void NPC::update(double dt)
{

    time += dt;

	if (Application::IsKeyPressed('R'))
	{
		dialogue_switch = 0;
		dialogue_reset = false;
		time = 0;
		has_interacted = false;
		dialogue_finish = false;
		stage = 0;
		quest_complete_delay = false;
		quest_complete_stage = 0;
	}
}

bool NPC::quest_given()
{
    return dialogue_finish;
}

string NPC::quest_complete()
{
    if (!Application::IsKeyPressed('E') && quest_complete_stage == 0)
    {
        return Dialogues[0];
    }
    if (Application::IsKeyPressed('E') && quest_complete_stage == 0)
    {
        quest_complete_stage = 1;
        return Dialogues[line_of_dialogue];
    }
    else if (quest_complete_stage == 1)
    {
        return Dialogues[line_of_dialogue];
    }
    return Dialogues[0];
}

short NPC::get_LineOfDialogue()
{
    return dialogue_switch;
}
