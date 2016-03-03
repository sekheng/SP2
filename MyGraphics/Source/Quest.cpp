#include "Quest.h"
#include "Application.h"
/******************************************************************************/
/*!
\brief -
Default Constructor
*/
/******************************************************************************/
Quest::Quest()
{

}
/******************************************************************************/
/*!
\brief -
Destructor
*/
/******************************************************************************/
Quest::~Quest()
{

}
/******************************************************************************/
/*!
\brief - initialised it's values through parameters

\param Name_ - Name of the quest

\param camera_address - 

\param no_of_items - number of items required to complete the quest

\param Item1_pos - position of first quest item

\param Item1_bounds - bounds of first quest item

\param Item2_pos - position of second quest item

\param Item2_bounds - bounds of second quest item
*/
/******************************************************************************/
void Quest::Init(string Name_, Camera3 &camera_address, short no_of_items,
    Vector3 Item1_pos, short Item1_bounds, Vector3 Item2_pos, short Item2_bounds)
{
    name = Name_;
    camera = &camera_address;

    //object 1
    x_1 = Item1_pos.x;
    y_1 = Item1_pos.y;
    z_1 = Item1_pos.z;
    bounds_1 = Item1_bounds;
    //object 2
    x_2 = Item2_pos.x;
    y_2 = Item2_pos.y;
    z_2 = Item2_pos.z;
    bounds_2 = Item2_bounds;
    stages = 0;
    CollectItem1 = false;
    CollectItem2 = false;
    time = 0;
    quest_complete = false;
    number_of_items = no_of_items;
}
/******************************************************************************/
/*!
\brief - check if quest has been taken or should be started

\param quest_is_taken - if true, quest is taken, if false, quest is not taken

\return true - quest is taken

\return false - quest is not taken
*/
/******************************************************************************/
bool Quest::check_quest(bool quest_is_taken)
{
    if (quest_is_taken)
    {
        stages = 1;
    }
    return quest_is_taken;
}
/******************************************************************************/
/*!
\brief - get the current progress of the quest

\return - which stage of the quest is the player currently at
*/
/******************************************************************************/
short Quest::stage()
{
    return stages;
   
}
/******************************************************************************/
/*!
\brief -  bounds check if player is within range to pick up item

\return true - player is within the bounds

\return false - player is not within the bounds
*/
/******************************************************************************/
bool Quest::boundscheck(float position_x, float position_z, float bounds_x, float bounds_z, float cameraposition_x, float cameraposition_z)
{
    if ((position_x + bounds_x) > cameraposition_x &&
        (position_x - bounds_x) < cameraposition_x &&
        (position_z + bounds_z) > cameraposition_z &&
        (position_z - bounds_z) < cameraposition_z)
    {
        return true;
    }
    return false;
}

/******************************************************************************/
/*!
\brief - get first item's x coordinate

\return x coordinate of first item
*/
/******************************************************************************/
float Quest::getObject1_X()
{
    return x_1;
}
/******************************************************************************/
/*!
\brief - get first item's z coordinate

\return z coordinate of first item
*/
/******************************************************************************/
float Quest::getObject1_Z()
{
    return z_1;
}
/******************************************************************************/
/*!
\brief - get second item's x coordinate

\return x coordinate of second item
*/
/******************************************************************************/

float Quest::getObject2_X()
{
    if (number_of_items == 1)
    {
        return 0;
    }
    return x_2;
}
/******************************************************************************/
/*!
\brief - get second item's z coordinate

\return z coordinate of second item
*/
/******************************************************************************/

float Quest::getObject2_Z()
{
    if (number_of_items == 1)
    {
        return 0;
    }
    return z_2;
}
/******************************************************************************/
/*!
\brief - get number of items the quest requires

\return the number of items required in the quest
*/
/******************************************************************************/
short Quest::get_numberof_items()
{
    return number_of_items;
}
/******************************************************************************/
/*!
\brief - update's the quest progress

\param dt - delta time 
*/
/******************************************************************************/
void Quest::Update(double dt)
{
    if (number_of_items == 1)
    {
        if (stages == 1)
        {
            if (Application::IsKeyPressed('E') && (boundscheck(x_1, z_1, bounds_1, bounds_1, 
                camera->getCameraXcoord(), camera->getCameraZcoord())) && CollectItem1 == false)
            {
                CollectItem1 = true;
                stages = 3;
            }
            if (CollectItem1 == true)
            {
                stages = 3;
            }
        }
        if (stages == 3)
        {
            quest_complete = true;
            time += dt;
        }
        if (time > 2.0f)
        {
            stages = 4;
        }
    }
    if (number_of_items == 2)
    {
        if (stages == 1)
        {
            if (Application::IsKeyPressed('E') && (boundscheck(x_1, z_1, bounds_1, bounds_1, 
                camera->getCameraXcoord(), camera->getCameraZcoord()))
                && CollectItem1 == false )
            {
                CollectItem1 = true;
                //stages = 3;
            }
            if (Application::IsKeyPressed('E') && (boundscheck(x_2, z_2, bounds_2, bounds_2, 
                camera->getCameraXcoord(), camera->getCameraZcoord()))
                && CollectItem2 == false)
            {
                CollectItem2 = true;
            }
            if (CollectItem1 == true && CollectItem2 == true)
            {
                stages = 3;
            }
        }
        if (stages == 3)
        {
            quest_complete = true;
            time += dt;
        }
        if (time > 2.0f)
        {
            stages = 4;
        }
    }
}
/******************************************************************************/
/*!
\brief - check if quest completed

\return true - quest is complete
\return false - quest is not complete
*/
/******************************************************************************/
bool Quest::questComplete()
{
    return quest_complete;
}
/******************************************************************************/
/*!
\brief - check if first item has been picked up

\return true - first item has been picked up
\return false - first item has not been picked up
*/
/******************************************************************************/
bool Quest::Item1collected()
{
    return CollectItem1;
}
/******************************************************************************/
/*!
\brief - check if second item has been picked up

\return true - second item has been picked up
\return false - second item has not been picked up
*/
/******************************************************************************/
bool Quest::Item2collected()
{
    if (number_of_items == 1)
    {
        return true;
    }
    return CollectItem2;
}
/******************************************************************************/
/*!
\brief - reset the quest
*/
/******************************************************************************/
void Quest::reset()
{
	stages = 0;
	CollectItem1 = false;
	CollectItem2 = false;
	time = 0;
	quest_complete = false;
}