#ifndef NPC_H_
#define NPC_H_

#include "GameObject.h"
#include "Vector3.h"
#include <vector>


using std::vector;

class NPC : public GameObject
{
public:
    NPC();
    ~NPC();

    void Init(string name, Vector3 pos);
    float NPC_getposition_x();
    float NPC_getposition_z();
    float NPC_getposition_y();

    string getDialogue();

private:
    Vector3 NPC_pos;
    vector<string> Dialogues;
protected:
};

#endif