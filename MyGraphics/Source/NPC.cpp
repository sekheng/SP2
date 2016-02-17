#include "NPC.h"
#include "MyMath.h"


NPC::NPC() : GameObject("NPC")
{

}
NPC::~NPC()
{

}

void NPC::Init(string name, Vector3 pos)
{
    Name_ = name;
    NPC_pos = pos;
    Dialogues = {"FML","HI","Vote for Najib", "Dai lo"};
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
    return Dialogues[Math::RandIntMinMax(0, Dialogues.size() - 1)];
}

