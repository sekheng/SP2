/******************************************************************************/
/*!
\file       SekHeng.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
To create a unique Data Driven Sek Heng NPC
*/
/******************************************************************************/
#ifndef SEKHENG_H_
#define SEKHENG_H_

#include "objectsForDisplay.h"
#include "Quest.h"
#include <map>

using std::map;

/******************************************************************************/
/*!
\file       creditScene.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
Inheirited from objectsForDisplay
It will have the collisiont check and position.
And it's own dialogues and interactions boundary
*/
/******************************************************************************/
class SekHeng : public objectsForDisplay
{
public:
    SekHeng();
    ~SekHeng();

    void initDialogues(const char *fileLocation, Camera3 &camera);
    void Update(double dt);

    string returnDialogue();
    bool interaction();
    void preventSpamming();

    void activateQuest();
    bool SekHengSayIsOk();
    void FinishedQuest();

    objectsForDisplay hammer;
    bool gottenHammer();
    short getStage();

    void reset();

private:
    Camera3 *dub_camera;
    float interatingRadius;
    double time;
    short stage;
    short order_of_text;
    
    map<short, vector<string>> dialogues;

    bool isOkay;
    bool interactingWithItem();
    bool hammerInHand;
};

#endif