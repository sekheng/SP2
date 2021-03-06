/******************************************************************************/
/*!
\file    NPC.h
\author  Lim Guan Hui
\par     email: 150623L@mymail.nyp.edu.sg
\brief -
The npc class 
*/
/******************************************************************************/
#ifndef NPC_H_
#define NPC_H_

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"
/******************************************************************************/
/*!
Class NPC:
\brief -
Inheirited from GameObject
It has a text reader file to input it's dialogue
*/
/******************************************************************************/
class NPC : public GameObject
{
public:
    NPC();
    ~NPC();

    void Init(string name, short NumberofDialogue, Vector3 pos, float boundaryX, float boundaryZ, Camera3 &camera_address, const char *fileLocation);
    float NPC_getposition_x();
    float NPC_getposition_z();
    float NPC_getposition_y();
    bool boundschecking(const float&bounds_x, const float &bounds_z);
    void update(double dt);
    string getDialogue(bool reset);
    bool interaction();
    bool quest_given();
    string quest_complete();
    short get_LineOfDialogue();
	void reset();
private:
    Vector3 NPC_pos;
    vector<string> Dialogues;
    Camera3 *cam_pointer;
    float bound_x, bound_z;
    int dialogue_switch;
    bool dialogue_reset;
    double time;
    bool has_interacted;
    float text_delay;
    bool dialogue_finish;
    int stage;
    bool quest_complete_stage;
    bool quest_complete_delay;
    short line_of_dialogue;
protected:
};

#endif