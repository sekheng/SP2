#ifndef SEKHENG_H_
#define SEKHENG_H_

#include "objectsForDisplay.h"
#include "Quest.h"
#include <map>

using std::map;

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