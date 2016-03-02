#include "creditScene.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/******************************************************************************/
/*!
\brief - a default constructor, with all variables becoming default value
*/
/******************************************************************************/
creditScene::creditScene()
    : rollingTitle(0), rollingTitleCaption(0), rollCredits(false), movePositionY(0)
{
}

/******************************************************************************/
/*!
\brief - a destructor
*/
/******************************************************************************/
creditScene::~creditScene()
{
}

/******************************************************************************/
/*!
\brief - a Data Driven method which will load the position of the people and their names

\param fileLocation - the path name to the text file
*/
/******************************************************************************/
void creditScene::initCredit(char *fileLocation) {
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

            position.push_back(taking_the_stuff);
            names.push_back(values);
        }
        fileStream2.close();
    }
}

/******************************************************************************/
/*!
\brief - the method to update the logic of the credit scene

\param dt - frame time
*/
/******************************************************************************/
void creditScene::updateCredit(double& dt) {
        if (rollingTitle < 15) {
            rollingTitle += (2) * (float)(dt);
            rollingTitleCaption += (float)(dt);
        }
        else {
            movePositionY += 2 * (float)(dt);
        }
}

/******************************************************************************/
/*!
\brief - return whether to roll the credits or not

\return true - if rollCredits is true

\return false - if rollCredits is false
*/
/******************************************************************************/
bool creditScene::goRollCredit() {
    if (rollCredits) {
        return true;
    }
    return false;
}

/******************************************************************************/
/*!
\brief - a getter function that allows user to get the position y of the credit title in this case 
'Prologue Ended'

\return - the float values of coord Y of rolling title
*/
/******************************************************************************/
float creditScene::getRollingTitle() {
    return rollingTitle;
}

/******************************************************************************/
/*!
\brief - a getter function that allows user to get the position y of the credit title captions 
in this case 'To Be Continued' and 'Plz buy our expansion pack in the future'

\return - the float values of coord Y of rolling title captions
*/
/******************************************************************************/
float creditScene::getRollingTitleCaption() {
    return rollingTitleCaption;
}

/******************************************************************************/
/*!
\brief - a method function which will activate the credits which are the people's position 
and their names.
*/
/******************************************************************************/
void creditScene::activateCredit() {
    rollCredits = true;
}

/******************************************************************************/
/*!
\brief - a getter function that will get the credit's position y in this case the people's 
position and their names.
*/
/******************************************************************************/
float creditScene::getMovePositionY() {
    return movePositionY;
}

/******************************************************************************/
/*!
\brief - a method that all the variables inside this class to it's default values
*/
/******************************************************************************/
void creditScene::reset() {
    rollingTitle = 0;
    rollingTitleCaption = 0;
    rollCredits = false;
    movePositionY = 0;
}