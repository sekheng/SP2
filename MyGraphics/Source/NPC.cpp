#include "NPC.h"
#include "MyMath.h"
#include "Application.h"

NPC::NPC() : GameObject("NPC")
{
    
}
NPC::~NPC()
{

}

void NPC::Init(string name, Vector3 pos, Camera3 &camera_address, float boundaryX, float boundaryZ)
{
    Name_ = name;
    NPC_pos = pos;
    Dialogues = {"FML","HI","Vote for Najib", "Dai lo"};
    cam_pointer = &camera_address;
    bound_x = boundaryX;
    bound_z = boundaryZ;
    time = 0;
}

float NPC::NPC_getposition_x()
{
    return NPC_pos.x;
}
float NPC::NPC_getposition_z()
{
    return NPC_pos.z;
}
float NPC::NPC_getposition_y()
{
    return NPC_pos.y;
}

string NPC::getDialogue()
{
    if (interaction() == true && time < 3)
    {
        return Dialogues[Math::RandIntMinMax(0, Dialogues.size() - 1)];
    }
    else {
        return "";
    }
}

bool NPC::interaction()
{
        if (Application::IsKeyPressed('E'))
        {
        if (boundschecking(cam_pointer->getCrossHairX(), cam_pointer->getCrossHairZ()) == false)
        {
                return true;
        }
            else return false;
        }
}

bool NPC::boundschecking(const float&bounds_x, const float &bounds_z)
{
    if ((NPC_getposition_x() + bound_x) > bounds_x &&
        (NPC_getposition_x() - bound_x) < bounds_x &&
        (NPC_getposition_z() + bound_z) > bounds_z &&
        (NPC_getposition_z() - bound_z) < bounds_z)
    {
        return false;
    }
    return true;
}

void NPC::update(double dt)
{
    time += dt;
}
