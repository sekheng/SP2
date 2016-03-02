#include "Quest.h"
#include "Application.h"
Quest::Quest()
{

}
Quest::~Quest()
{

}
//
//void Quest::Init(string Name_, Camera3 &camera_address,short no_of_objects,
//    Vector3 Object_1_pos, float Object_1_bounds_x, float Object_1_bounds_z,
//    Vector3 Object_2_pos, float Object_2_bound_x, float Object_2_bound_z)
//{
//    name = Name_;
//    camera = &camera_address;
//    //object 1
//    x_1 = Object_1_pos.x;
//    y_1 = Object_1_pos.y;
//    z_1 = Object_1_pos.z;
//    bounds_1_x = Object_1_bounds_x;
//    bounds_1_z = Object_1_bounds_z;
//    //object 2
//    x_2 = Object_2_pos.x;
//    y_2 = Object_2_pos.y;
//    z_2 = Object_2_pos.z;
//    bounds_2_x = Object_2_bound_x;
//    bounds_2_z = Object_2_bound_z;
//
//    Quest_accept = false;
//
//    stop_change1 = false;
//    stop_change2 = false;
//
//    number_of_objects = no_of_objects;
//}
//
//void Quest::Quest_Taken(bool taken)
//{
//    Quest_accept = true;
//}
//
//bool Quest::get_quest_taken()
//{
//    return Quest_accept;
//}
//
//bool Quest::FirstObject()
//{
//    return pickup(x_1,z_1,bounds_1_x,bounds_1_z, camera->getCameraXcoord(), camera->getCameraZcoord());
//}
//float Quest::get_object1_x()
//{
//    return x_1;
//}
//float Quest::get_object1_z()
//{
//    return z_1;
//}
//bool Quest::FirstObject_taken()
//{
//    if (Application::IsKeyPressed('E') == true && FirstObject() == true && stop_change1 == false)
//    {
//        stop_change1 = true;
//        return true;
//    }
//    else
//    {
//        if ( stop_change1 == false)
//        return false;
//    }
//    return false;
//}
//
//bool Quest::SecondObject()
//{
//    return pickup(x_2, z_2, bounds_2_x, bounds_2_z, camera->getCameraXcoord(), camera->getCameraZcoord());
//}
//bool Quest::SecondObject_taken()
//{
//    if (number_of_objects == 1) return true;
//    if (Application::IsKeyPressed('E') && SecondObject() && stop_change2 == false )
//    {
//        stop_change2 = true;
//        return true;
//    }
//    else
//    {
//        if (stop_change2 == false)
//        return false;
//    }
//    return false;
//}
//float Quest::get_object2_x()
//{
//    return x_2;
//}
//float Quest::get_object2_z()
//{
//    return z_2;
//}
//bool Quest::QuestinProgress()
//{
//    if (FirstObject_taken() && SecondObject_taken())
//        return false;
//    else
//        return true;
//}
///**************************************************************************/
////put this in update of scene to check if quest is complete
///**************************************************************************/
//bool Quest::Result()
//{
//    if (get_quest_taken())
//    {
//        if (QuestinProgress() == false)
//            return true;
//        else
//            return false;
//    }
//    else return false;
//}
///********************************************************************************/
////basically bounds check and to check if object has been picked up or not
///********************************************************************************/
//bool Quest::pickup( float position_x,  float position_z, float bounds_x, float bounds_z, float cameraposition_x, float cameraposition_z)
//{
//    if ((position_x + bounds_x) > cameraposition_x &&
//        (position_x - bounds_x) < cameraposition_x &&
//        (position_z + bounds_z) > cameraposition_z &&
//        (position_z - bounds_z) < cameraposition_z)
//    {
//        return true;
//    }
//    return false;
//}
//
//short Quest::no_of_objects()
//{
//    return number_of_objects;
//}
//
//

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

bool Quest::check_quest(bool quest_is_taken)
{
    if (quest_is_taken)
    {
        stages = 1;
    }
    return quest_is_taken;
}

short Quest::stage()
{
    return stages;
   
}

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

//bool Quest::renderObject1()
//{
//    if (stages == 1)  return true;
//    else return false;
//}
//
//bool Quest::renderObject2()
//{
//    return false;
//}

float Quest::getObject1_X()
{
    return x_1;
}

float Quest::getObject1_Z()
{
    return z_1;
}

float Quest::getObject2_X()
{
    if (number_of_items == 1)
    {
        return 0;
    }
    return x_2;
}

float Quest::getObject2_Z()
{
    if (number_of_items == 1)
    {
        return 0;
    }
    return z_2;
}

short Quest::get_numberof_items()
{
    return number_of_items;
}

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

	if (Application::IsKeyPressed('R'))
	{
		stages = 0;
		CollectItem1 = false;
		CollectItem2 = false;
		time = 0;
		quest_complete = false;
	}
}

bool Quest::questComplete()
{
    return quest_complete;
}


bool Quest::Item1collected()
{
    return CollectItem1;
}


bool Quest::Item2collected()
{
    if (number_of_items == 1)
    {
        return true;
    }
    return CollectItem2;
}