/******************************************************************************/
/*!
\file       rot_civ.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
A unique NPC which differs from others in scenario 3
There is only dialogues and interacting boundary as the rest are re-used from objectsForDisplay class
*/
/******************************************************************************/
#ifndef ROT_CIV_H_
#define ROT_CIV_H_

#include "objectsForDisplay.h"
#include "Camera3.h"

/******************************************************************************/
/*!
Class rot_civ:
\brief
Inheirited from objectsForDisplay to reduce the amount of codes need to be written
It can initialise Dialogues from a text file and speak from there
It has it's own interaction boundary where the player must be located at to interact with him
*/
/******************************************************************************/
class rot_civ : public objectsForDisplay {
public:
    rot_civ();
    ~rot_civ();

    void InitDialogues(const char* fileLocation, Camera3& camera);
    vector<string> dialogues;

    void update(double dt);
    string returnDialogue();
    bool interaction();
    void preventSpamming();

private:
    Camera3 *dub_camera;
    float interatingRadius;
    double time;
    size_t order_of_text;
};

#endif