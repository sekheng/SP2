/******************************************************************************/
/*!
\file    Quest.h
\author  Lim Guan Hui
\par     email: 150623L@mymail.nyp.edu.sg
\brief -
The quest class
*/
/******************************************************************************/
#ifndef QUEST_H_
#define QUEST_H_

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"

using std::vector;
/******************************************************************************/
/*!
Class Quest
\brief - Quest system used to help create a flow of quests easily in the game
*/
/******************************************************************************/
class Quest
{
public:
    Quest();
    ~Quest();
    void Init(string Name_, Camera3 &camera_address, short no_of_items, 
        Vector3 Item1_pos, short Item1_bounds, Vector3 Item2_pos, short Item2_bounds);
    bool check_quest(bool quest_is_taken);
    short stage();
    bool boundscheck(float position_x, float position_z, float bounds_x, float bounds_z, float cameraposition_x, float cameraposition_z);
    float getObject1_X();
    float getObject1_Z();
    float getObject2_X();
    float getObject2_Z();
    void Update(double dt);
    bool questComplete();
    short get_numberof_items();
    bool Item1collected();
    bool Item2collected();
	void reset();
private:
    string name;
    Camera3 *camera;
    short stages;
    float x_1, y_1, z_1;
    float bounds_1, bounds_2;
    float x_2, y_2, z_2;
    bool CollectItem1, CollectItem2;
    double time;
    bool quest_complete;
    short number_of_items;
protected:
};


#endif