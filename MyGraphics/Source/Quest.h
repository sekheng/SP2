/******************************************************************************/
/*!
\file    NPC.h
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

class Quest
{
public:
    Quest();
    ~Quest();

    void Init(string Name_, Camera3 &camera_address,
        Vector3 Object_1_pos, float Object_1_bounds_x, float Object_1_bounds_z,
        Vector3 Object_2_pos, float Object_2_bound_x, float Object_2_bound_z
        );
    void Quest_Taken(bool taken);
    bool get_quest_taken();
    bool FirstObject();
    bool FirstObject_taken();
    float get_object1_x();
    float get_object1_z();
    bool SecondObject();
    bool SecondObject_taken();
    float get_object2_x();
    float get_object2_z();
    bool QuestinProgress();
    bool Result();
    bool pickup( float position_x,  float position_z,
        float bounds_x, float bounds_z, float cameraposition_x, float cameraposition_z);
private:
    string name;
    Camera3 *camera;
    //object 1
    float x_1, y_1, z_1;
    //object 2
    float x_2, y_2, z_2;

    float bounds_1_x;
    float bounds_1_z;

    float bounds_2_x;
    float bounds_2_z;

    bool Quest_accept;

    bool stop_change1,stop_change2;
protected:
};

#endif