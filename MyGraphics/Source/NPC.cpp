#include "NPC.h"
#include "MyMath.h"
#include "Application.h"
#include <fstream>
#include <iostream>
#include <map>
#include <locale>
#include <algorithm>

using std::map;

NPC::NPC() : GameObject("NPC")
{
    
}
NPC::~NPC()
{

}

void NPC::Init(string name, Vector3 pos, float boundaryX, float boundaryZ, Camera3 &camera_address, const char *fileLocation)
{
    //initialization of varivables
    Name_ = name;
    NPC_pos = pos;
    cam_pointer = &camera_address;
    bound_x = boundaryX;
    bound_z = boundaryZ;
    time = 0;
    dialogue_switch = 0;
    dialogue_reset = false;
    time = 0;
    has_interacted = false;
    dialogue_finish = false;
    stage = 0;

    //read dialogue from text file
    map<string, string> npc_data;//dialogue is stored in map
    std::ifstream fileStream(fileLocation, std::ios::binary);
    if (!fileStream.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream.eof()) {
            string data = "";
            getline(fileStream, data);
            char *next_data;
            char *read_data = strtok_s(const_cast<char*>(data.c_str()), ":", &next_data); // before ':' is key and after ':' is data for map 
            string taking_the_stuff = "";
            string values = "";
            taking_the_stuff.append(read_data);
            values.append(next_data);
            values.erase(std::remove(values.begin(), values.end(), '\r'));
            std::locale loc;
            for (size_t num = 0; num < taking_the_stuff.size(); ++num) {
                taking_the_stuff[num] = tolower(taking_the_stuff[num], loc);
            }
            npc_data.insert(std::pair<string, string>(taking_the_stuff, values));
        }
        fileStream.close();
    }
    map<string, string>::iterator it;// Map key is sequence of dialog and data is their text

    it = npc_data.find("first");
    Dialogues.push_back(it->second);

    it = npc_data.find("second");
    Dialogues.push_back(it->second);

    it = npc_data.find("third");
    Dialogues.push_back(it->second);

    it = npc_data.find("fourth");
    Dialogues.push_back(it->second);

    

    text_delay = 0.3f; // set the delay for text
}
/*********************************************************/
//get npc position
/*********************************************************/
float NPC::NPC_getposition_x()
{
    return NPC_pos.x;
}
float NPC::NPC_getposition_z()
{
    return NPC_pos.z;
}
float NPC::NPC_getposition_y()
{
    return NPC_pos.y;
}

/*********************************************************/
//return npc dialogue
/*********************************************************/
string NPC::getDialogue(bool reset)
{
    dialogue_reset = reset;
    
    if (dialogue_reset == true && has_interacted == false)
    {
        dialogue_switch = 0;
        return Dialogues[dialogue_switch];
    }
    else if (dialogue_reset == false && has_interacted == false) {
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
            if (dialogue_switch == 3)
            {
                dialogue_finish = true;
            }
            if (dialogue_switch == 4)
            {
                dialogue_switch = 1;
            }
        }
        return Dialogues[dialogue_switch];
    }

    /*if (reset && has_interacted == false)
    {
        stage = 0;
        has_interacted = true;
        return Dialogues[stage];
    }
    else if (reset && has_interacted == true)
    {
        if (time > text_delay)
        {
            time = 0;
            stage++;
            if (stage == 4)
            {
                stage = 1;
            }
        }
        return Dialogues[stage];
    }
    else if (!reset && has_interacted == false)
    {
        stage = 1;
        return Dialogues[stage];
    }
    else
    {
        return Dialogues[stage];
    }*/

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
}

bool NPC::quest_given()
{
    return dialogue_finish;
}