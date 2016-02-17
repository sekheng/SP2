#ifndef NPC_H_
#define NPC_H_

#include "GameObject.h"
#include "Vector3.h"
#include <vector>
#include "Camera3.h"

using std::vector;

class NPC : public GameObject
{
public:
    NPC();
    ~NPC();

    void Init(string name, Vector3 pos, Camera3 &camera_address, float boundaryX, float boundaryZ);
    float NPC_getposition_x();
    float NPC_getposition_z();
    float NPC_getposition_y();
    bool boundschecking(const float&bounds_x, const float &bounds_z);
    void update(double dt);
    string getDialogue();
    bool interaction();
private:
    Vector3 NPC_pos;
    vector<string> Dialogues;
    Camera3 *cam_pointer;
    float bound_x, bound_z;
    double time;
protected:
};

#endif