/******************************************************************************/
/*!
\file       creditScene.h
\author  Lee Sek Heng
\par        email: 150629Z@mymail.nyp.edu.sg
\brief -
An attempt to create a genuine credit scene similar to other video game's credit scene
*/
/******************************************************************************/
#ifndef CREDITSCENE_H_
#define CREDITSCENE_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

/******************************************************************************/
/*!
Class creditScene:
\brief
The logic class of credit scene
*/
/******************************************************************************/
class creditScene {
public:
    creditScene();
    ~creditScene();

    void initCredit(char *fileLocation);
    void updateCredit(double& dt);
    void activateCredit();
    bool goRollCredit();

    float getRollingTitle();
    float getRollingTitleCaption();
    float getMovePositionY();

    vector<string> position;
    vector<string> names;

    void reset();

private:
    float rollingTitle;
    float rollingTitleCaption;
    bool rollCredits;
    float movePositionY;
};

#endif