#include "SekHeng.h"
#include <fstream>
#include <algorithm>
#include "Application.h"

/******************************************************************************/
/*!
\brief - a default constructor, with all variables becoming default value
*/
/******************************************************************************/
SekHeng::SekHeng()
    : order_of_text(0), stage(0), interatingRadius(6), time(0), isOkay(false), hammerInHand(true)
{
    hammer.init(Vector3(92, 0, -78), 3, 3, "hammer");
}

/******************************************************************************/
/*!
\brief - a destructor
*/
/******************************************************************************/
SekHeng::~SekHeng()
{
}

/******************************************************************************/
/*!
\brief - a Data Driven function that will initialised it's dialogue

\param fileLocation - the path name to the file's location

\param camera - a reference pointer to the scene's camera
*/
/******************************************************************************/
void SekHeng::initDialogues(const char *fileLocation, Camera3& camera) {
    dub_camera = &camera;
    
    //streaming SekHeng's dialogue
    std::ifstream fileStream2(fileLocation, std::ios::binary);
    if (!fileStream2.is_open()) {
        std::cout << "Impossible to open " << fileLocation << ". Are you in the right directory ?\n";
    }
    else {
        while (!fileStream2.eof()) {
            string data = "";
            getline(fileStream2, data);
            if (data == "" || data == "\r") {
                continue;
            }
            char *nextStuff;
            char *stringtoken = strtok_s(const_cast<char*>(data.c_str()), ",", &nextStuff);
            string taking_the_stuff = "";
            string values = "";
            taking_the_stuff.append(stringtoken);
            values.append(nextStuff);
            values.erase(std::remove(values.begin(), values.end(), '\r'));
            //If you did Data Struct Assignment 2 carefully, you will understand the following lines.
            size_t the_stage = static_cast<short>(stoi(taking_the_stuff));
            map<short, vector<string>>::iterator it;
            if (dialogues.count(the_stage) == 1) {
                it = dialogues.find(the_stage);
                it->second.push_back(values);
                continue;
            }
            else {
                dialogues.insert(std::pair<short, vector<string>>(the_stage, { values }));
            }
        }
        fileStream2.close();
    }
    //streaming SekHeng's dialogue
}

/******************************************************************************/
/*!
\brief - a method function which will update the logic behind the interaction with Sek Heng

\param dt - frame time
*/
/******************************************************************************/
void SekHeng::Update(double dt) {
    time += dt;
    preventSpamming();
    //when the quest is activated, checking whether the player has the hammer
    if (Application::IsKeyPressed('E') && stage == 1 &&
        interaction() == false && hammerInHand == true) {
        FinishedQuest();
    }
    //when the quest is activated, checking whether the player has the hammer
    
    //Checking whether is this an active quest and the hammer is not collected,
    //If the hammer is within it's interacting boundary, the hammer is collected
    else if (hammerInHand == false && Application::IsKeyPressed('E') &&
        interactingWithItem() == false && stage == 1) {
        hammerInHand = true;
    }
}

/******************************************************************************/
/*!
\brief - a getter function which user can get the dialogue from Sek Heng

\return - a string of the dialogue
*/
/******************************************************************************/
string SekHeng::returnDialogue() {
    return dialogues[stage][order_of_text];
}

/******************************************************************************/
/*!
\brief - a method function which will activate the Sek Heng's quest
*/
/******************************************************************************/
void SekHeng::activateQuest() {
    if (stage == 0 && hammerInHand == true) {
        hammerInHand = false;
    }
    stage = 1;
}

/******************************************************************************/
/*!
\brief - to check whether the player in within it's interacting boundary

\return - true if the player is outside it's interacting boundary

\return - false if the player is inside it's interacting boundary
*/
/******************************************************************************/
bool SekHeng::interaction() {
    if ((objectPos.x + boundaryRadiusX + interatingRadius) > dub_camera->getCameraXcoord() &&
        (objectPos.x - boundaryRadiusX - interatingRadius) < dub_camera->getCameraXcoord() &&
        (objectPos.z + boundaryRadiusZ + interatingRadius) > dub_camera->getCameraZcoord() &&
        (objectPos.z - boundaryRadiusZ - interatingRadius) < dub_camera->getCameraZcoord())
    {
        return false;
    }
    order_of_text = 0;
    return true;
}

/******************************************************************************/
/*!
\brief - Prevention of the dialogue from running to fast if player is holding 'E'
*/
/******************************************************************************/
void SekHeng::preventSpamming() {
    if (Application::IsKeyPressed('E')) {
        if (time > 1) {
            order_of_text += 1;
            time = 0;
            if (order_of_text == dialogues[stage].size()) {
                order_of_text = 0;
            }
        }
    }
}

/******************************************************************************/
/*!
\brief - check whether Sek Heng's quest is completed

\return - true if Sek Heng's quest is completed

\return - false if Sek Heng's quest is incomplete
*/
/******************************************************************************/
bool SekHeng::SekHengSayIsOk() {
    if (isOkay) {
        return true;
    }
    else {
        return false;
    }
}

/******************************************************************************/
/*!
\brief - a method function which will allows teleportation and new dialogue upon finishing 
Sek Heng's quest
*/
/******************************************************************************/
void SekHeng::FinishedQuest() {
    stage = 2;
    isOkay = true;
}

/******************************************************************************/
/*!
\brief - to check whether the player in within Sek Heng's hammer interacting boundary

\return - true if the player is outside Sek Heng's hammer interacting boundary

\return - false if the player is inside Sek Heng's hammer interacting boundary
*/
/******************************************************************************/
bool SekHeng::interactingWithItem() {
    if ((hammer.getObjectposX() + hammer.getBoundaryRadiusX()) > dub_camera->position.x &&
        (hammer.getObjectposX() - hammer.getBoundaryRadiusX()) < dub_camera->position.x &&
        (hammer.getObjectposZ() + hammer.getBoundaryRadiusZ()) > dub_camera->position.z &&
        (hammer.getObjectposZ() - hammer.getBoundaryRadiusZ()) < dub_camera->position.z)
    {
        return false;
    }
    return true;
}

/******************************************************************************/
/*!
\brief - check whether player has gotten the hammer

\return - true if player has interacted with the hammer

\return - false if the player has not interacted with the hammer
*/
/******************************************************************************/
bool SekHeng::gottenHammer() {
    if (hammerInHand) {
        return true;
    }
    return false;
}

/******************************************************************************/
/*!
\brief - a getter function that returns the dialogue which Sek Heng will say in 3 different 
state which are when Sek Heng is waiting for other quests to be completed, Sek Heng is 
waiting for the player to finish his quest, and Sek Heng's quest is completed

\return - the order of dialogues
*/
/******************************************************************************/
short SekHeng::getStage() {
    return stage;
}

/******************************************************************************/
/*!
\brief - a method to completely reset the Sek Heng's variable to it's default state
*/
/******************************************************************************/
void SekHeng::reset()
{
    stage = 0;
    order_of_text = 0;
    time = 0;
    isOkay = false;
    hammerInHand = true;
    hammer.objectPos = hammer.originalPos;
	hammer.init(Vector3(92, 0, -78), 3, 3, "hammer");
}